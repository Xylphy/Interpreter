#include "Headers/Parser.hpp"

#include <algorithm>

#include "Headers/Stmt.hpp"
#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens) {}

Parser::Parser(std::vector<Token> &&tokens) : tokens(std::move(tokens)) {}

auto Parser::expression() -> Expr * { return assignment(); }

auto Parser::equality() -> Expr * {
  Expr *expr = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
    Token operatorToken = previous();
    Expr *right = comparison();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::match(std::initializer_list<TokenType> types) -> bool {
  if (std::ranges::any_of(
          types, [this](TokenType type) -> bool { return check(type); })) {
    advance();
    return true;
  }
  return false;
}

auto Parser::check(TokenType type) -> bool {
  if (isAtEnd()) {
    return false;
  }
  return peek().type == type;
}

auto Parser::advance() -> Token {
  if (!isAtEnd()) {
    current++;
  }
  return previous();
}

auto Parser::isAtEnd() -> bool {
  return peek().type == TokenType::END_OF_FILE || peek().type == TokenType::END;
}

auto Parser::peek() -> Token { return tokens[current]; }

auto Parser::previous() -> Token { return tokens[current - 1]; }

auto Parser::comparison() -> Expr * {
  Expr *expr = term();

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
                TokenType::LESS_EQUAL})) {
    Token operatorToken = previous();
    Expr *right = term();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::term() -> Expr * {
  Expr *expr = factor();

  while (match({TokenType::MINUS, TokenType::PLUS})) {
    Token operatorToken = previous();
    Expr *right = factor();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::factor() -> Expr * {
  Expr *expr = unary();

  while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULO})) {
    Token operatorToken = previous();
    Expr *right = unary();
    expr = new Binary(expr, operatorToken, right);
  }

  return expr;
}

auto Parser::unary() -> Expr * {
  if (match({TokenType::BANG, TokenType::MINUS})) {
    Token operatorToken = previous();
    Expr *right = unary();
    return new Unary(operatorToken, right);
  }

  return primary();
}

auto Parser::primary() -> Expr * {
  if (match({TokenType::BOOL_FALSE})) {
    return new Literal(false, TokenType::BOOL_FALSE);
  }
  if (match({TokenType::BOOL_TRUE})) {
    return new Literal(true, TokenType::BOOL_TRUE);
  }
  if (match({TokenType::NUMBER, TokenType::STRING_LITERAL,
             TokenType::CHARACTER_LITERAL, TokenType::DECIMAL_NUMBER})) {
    return new Literal(previous().literal, previous().type);
  }
  if (match({TokenType::NEW_LINE})) {
    return new Literal('\n', TokenType::CHARACTER_LITERAL);
  }

  if (match({TokenType::IDENTIFIER})) {
    return new Variable(previous());
  }

  if (match({TokenType::LEFT_PAREN})) {
    Expr *expr = expression();
    if (!match({TokenType::RIGHT_PAREN})) {
      throw std::runtime_error("Expect ')' after expression.");
    }
    return new Grouping(expr);
  }

  throw ParseError(previous(), "Expect expression.");
}

auto Parser::consume(TokenType type, const std::string &message) -> Token {
  if (check(type)) {
    return advance();
  }

  throw ParseError(peek(), message);
}

auto Parser::error(const Token &token, const std::string &message)
    -> ParseError {
  BisayaPP::error(token, message);

  return {token, message};
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().type == TokenType::SEMICOLON) {
      return;
    }

    switch (peek().type) {
      case TokenType::VAR:
      case TokenType::FOR:
      case TokenType::IF:
      case TokenType::WHILE:
        return;
      default:;
    }

    advance();
  }
}

auto Parser::varDeclaration(TokenType type) -> Stmt * {
  Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
  name.type = type;

  Expr *initializer = nullptr;
  if (match({TokenType::EQUAL})) {
    initializer = expression();
  }

  if (check(TokenType::SEMICOLON) || check(TokenType::COMMA)) {
    advance();
  } else {
    throw ParseError(previous(), "Expect newline after variable declaration.");
  }

  return new Var(name, initializer);
}

auto Parser::declaration() -> std::vector<Stmt *> {
  try {
    if (match({TokenType::VAR}) &&
        (peek().type == TokenType::INTEGER ||
         peek().type == TokenType::DECIMAL || peek().type == TokenType::CHAR ||
         peek().type == TokenType::BOOL)) {
      advance();

      std::vector<Stmt *> declarations;
      do {
        declarations.push_back(varDeclaration(previous().type));
      } while (check(TokenType::IDENTIFIER));

      return declarations;
    }

    return {statement()};
  } catch (const ParseError &error) {
    synchronize();
    return {};
  }
}

auto Parser::parse() -> std::vector<Stmt *> {
  try {
    if (tokens[0].type != TokenType::START) {
      BisayaPP::error(tokens[0],
                      "Expect 'SUGOD' at the beginning of the file.");
    }
    advance();
    advance();

    std::vector<Stmt *> statements;
    while (!isAtEnd()) {
      std::vector<Stmt *> decs = declaration();
      statements.reserve(statements.size() + decs.size());
      statements.insert(statements.end(), std::make_move_iterator(decs.begin()),
                        std::make_move_iterator(decs.end()));
    }

    if (tokens[current].type != TokenType::END) {
      BisayaPP::error(tokens[current],
                      "Expect 'KATAPUSAN' at the end of the file.");
    }

    return statements;
  } catch (const ParseError &error) {
    BisayaPP::error(previous(), error.what());
    return {};
  } catch (const SyntaxError &error) {
    BisayaPP::error(previous(), error.what());
    return {};
  }
}

auto Parser::expressionStatement() -> Stmt * {
  Expr *value = expression();
  consume(TokenType::SEMICOLON, "Expect newline after expression.");
  return new Expression(value);
}

auto Parser::printStatement() -> Stmt * {
  Expr *value = expression();

  consume(TokenType::SEMICOLON, "Expect newline after value.");
  return new Print(value);
}

auto Parser::statement() -> Stmt * {
  if (match({TokenType::IF})) {
    if (tokens[current - 2].type == TokenType::ELSE) {
      BisayaPP::error(previous(), "Invalid syntax after WALA");
    } else {
      return ifStatement();
    }
  }
  if (match({TokenType::PRINT})) {
    return printStatement();
  }
  if (match({TokenType::WHILE})) {
    if (match({TokenType::FOR})) {
      return forStatement();
    }
    return whileStatement();
  }

  if (match({TokenType::BLOCK})) {
    return new Block(block());
  }

  if (match({TokenType::LEFT_BRACE})) {
    throw SyntaxError(previous(), "Expected 'PUNDOK' before '{'.");
  }

  return expressionStatement();
}

auto Parser::assignment() -> Expr * {
  Expr *expr = orExpression();

  if (match({TokenType::EQUAL})) {
    Token equals = previous();
    Expr *value = assignment();

    if (dynamic_cast<Variable *>(expr) != nullptr) {
      Token name = static_cast<Variable *>(expr)->name;
      return new Assign(name, value);
    }

    error(equals, "Invalid assignment target.");
  }

  return expr;
}

auto Parser::block() -> std::vector<Stmt *> {
  std::vector<Stmt *> statements;

  consume(TokenType::LEFT_BRACE, "Expect '{' before block.");

  if (check(TokenType::SEMICOLON)) {
    advance();
  }

  while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
    std::vector<Stmt *> decs = declaration();
    statements.reserve(statements.size() + decs.size());
    statements.insert(statements.end(), std::make_move_iterator(decs.begin()),
                      std::make_move_iterator(decs.end()));
  }

  consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
  if (check(TokenType::SEMICOLON)) {
    advance();
  }

  return statements;
}

auto Parser::ifStatement() -> Stmt * {
  consume(TokenType::LEFT_PAREN, "Expect '(' after 'KUNG'.");
  Expr *condition = expression();
  consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");

  Stmt *thenBranch = statement();
  Stmt *elseBranch = nullptr;

  if (match({TokenType::IF})) {
    if (match({TokenType::ELSE_IF})) {
      elseBranch = ifStatement();
    } else if (match({TokenType::ELSE})) {
      elseBranch = statement();
    } else {
      BisayaPP::error(previous(), "Expect 'KUNG' or 'DILI' after 'KUNG'.");
    }
  }

  return new If(condition, thenBranch, elseBranch);
}

auto Parser::orExpression() -> Expr * {
  Expr *expr = andExpression();

  while (match({TokenType::OR})) {
    Token operatorToken = previous();
    Expr *right = andExpression();
    expr = new Logical(expr, operatorToken, right);
  }
  return expr;
}

auto Parser::andExpression() -> Expr * {
  Expr *expr = equality();

  while (match({TokenType::AND})) {
    Token operatorToken = previous();
    Expr *right = equality();
    expr = new Logical(expr, operatorToken, right);
  }
  return expr;
}

auto Parser::whileStatement() -> Stmt * {
  consume(TokenType::LEFT_PAREN, "Expect '(' after 'SAMTANG'.");
  Expr *condition = expression();
  consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");

  Stmt *body = statement();

  return new While(condition, body);
}

auto Parser::forStatement() -> Stmt * {
  consume(TokenType::LEFT_PAREN, "Expect 'c' after 'ALANG SA',");

  Stmt *initializer;
  if (match({TokenType::SEMICOLON})) {
    initializer = nullptr;
  } else if (match({TokenType::VAR})) {
    if (match({TokenType::INTEGER, TokenType::DECIMAL, TokenType::CHAR,
               TokenType::BOOL})) {
      initializer = varDeclaration(previous().type);
    } else {
      BisayaPP::error(previous(), "Expect data type after 'VAR'.");
    }
  } else {
    initializer = expressionStatement();
  }

  Expr *condition = nullptr;
  if (!check(TokenType::SEMICOLON)) {
    condition = expression();
  }

  consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");

  Expr *increment = nullptr;
  if (!check(TokenType::RIGHT_PAREN)) {
    increment = expression();
  }

  consume(TokenType::RIGHT_PAREN, "Expect ')' after for clauses.");

  Stmt *body = statement();

  std::vector<Stmt *> whileBody;
  whileBody.push_back(body);
  if (increment != nullptr) {
    whileBody.push_back(new Expression(increment));
  }

  if (condition == nullptr) {
    condition = new Literal(true, TokenType::BOOL_TRUE);
  }

  Stmt *whileBodyBlock = new Block(whileBody);
  Stmt *whileLoop = new While(condition, whileBodyBlock);

  std::vector<Stmt *> forStmt;
  if (initializer != nullptr) {
    forStmt.push_back(initializer);
  }

  forStmt.push_back(whileLoop);

  return new Block(forStmt);
}
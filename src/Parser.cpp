#include "Headers/Parser.hpp"

#include <algorithm>
#include <iostream>
#include <print>

#include "Headers/Lib/utility.hpp"
#include "Headers/Scanner.hpp"
#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens) {}

Parser::Parser(std::vector<Token> &&tokens) : tokens(std::move(tokens)) {}

auto Parser::expression() -> std::unique_ptr<Expr> { return assignment(); }

auto Parser::equality() -> std::unique_ptr<Expr> {
  std::unique_ptr<Expr> expr = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL,
                TokenType::CONCATENATOR})) {
    Token previousToken = previous();
    expr =
        std::make_unique<Binary>(std::move(expr), previousToken, comparison());
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

auto Parser::previous() -> Token & { return tokens[current - 1]; }

auto Parser::comparison() -> std::unique_ptr<Expr> {
  std::unique_ptr<Expr> expr = term();

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
                TokenType::LESS_EQUAL})) {
    Token previousToken = previous();
    expr = std::make_unique<Binary>(std::move(expr), previousToken, term());
  }
  return expr;
}

auto Parser::term() -> std::unique_ptr<Expr> {
  std::unique_ptr<Expr> expr = factor();

  while (match({TokenType::MINUS, TokenType::PLUS})) {
    Token previousToken = previous();
    expr = std::make_unique<Binary>(std::move(expr), previousToken, factor());
  }

  return expr;
}

auto Parser::factor() -> std::unique_ptr<Expr> {
  std::unique_ptr<Expr> expr = unary();

  while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULO})) {
    Token previousToken = previous();
    expr = std::make_unique<Binary>(std::move(expr), previousToken, unary());
  }

  return expr;
}

auto Parser::unary() -> std::unique_ptr<Expr> {
  if (match({TokenType::BANG, TokenType::MINUS})) {
    Token previousToken = previous();
    return std::make_unique<Unary>(previousToken, unary());
  }

  return primary();
}

auto Parser::primary() -> std::unique_ptr<Expr> {
  if (match({TokenType::BOOL_FALSE})) {
    return std::make_unique<Literal>(false, TokenType::BOOL_FALSE);
  }
  if (match({TokenType::BOOL_TRUE})) {
    return std::make_unique<Literal>(true, TokenType::BOOL_TRUE);
  }

  if (match({TokenType::NUMBER, TokenType::STRING_LITERAL,
             TokenType::CHARACTER_LITERAL, TokenType::DECIMAL_NUMBER})) {
    Token previousToken = previous();
    return std::make_unique<Literal>(previousToken.literal, previousToken.type);
  }

  if (match({TokenType::NEW_LINE})) {
    return std::make_unique<Literal>("\n", TokenType::STRING_LITERAL);
  }

  if (match({TokenType::IDENTIFIER})) {
    return std::make_unique<Variable>(previous());
  }

  if (match({TokenType::LEFT_PAREN})) {
    std::unique_ptr<Expr> expr = expression();
    if (!match({TokenType::RIGHT_PAREN})) {
      throw std::runtime_error("Expect ')' after expression.");
    }
    return std::make_unique<Grouping>(std::move(expr));
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
      case TokenType::INPUT:
      case TokenType::WHILE:
        return;
      default:;
    }

    advance();
  }
}

auto Parser::varDeclaration(TokenType &type) -> std::unique_ptr<Stmt> {
  if (!check(TokenType::IDENTIFIER)) {
    BisayaPP::error(peek(), "Expect variable name.");
  }
  Token name = advance();
  name.type = type;

  std::unique_ptr<Expr> initializer = nullptr;
  if (match({TokenType::EQUAL})) {
    initializer = expression();
  }

  if (check(TokenType::SEMICOLON) || check(TokenType::COMMA)) {
    if (check(TokenType::SEMICOLON)) {
      type = TokenType::UNITIALIZED;  // Reset the data type. Refer to
                                      // Environment.cpp
    }
    advance();
  } else {
    throw ParseError(previous(), "Expect newline after variable declaration.");
  }

  return std::make_unique<Var>(name, std::move(initializer));
}

auto Parser::declaration() -> std::vector<std::unique_ptr<Stmt>> {
  try {
    if (match({TokenType::VAR}) &&
        (peek().type == TokenType::INTEGER ||
         peek().type == TokenType::DECIMAL || peek().type == TokenType::CHAR ||
         peek().type == TokenType::BOOL)) {
      advance();

      TokenType dataType = previous().type;
      std::vector<std::unique_ptr<Stmt>> declarations;
      do {
        declarations.emplace_back(varDeclaration(dataType));
      } while (check(TokenType::IDENTIFIER));

      return declarations;
    }

    std::vector<std::unique_ptr<Stmt>> stmts;
    stmts.emplace_back(statement());
    return stmts;
  } catch (const ParseError &error) {
    synchronize();
    return {};
  }
}

auto Parser::parse() -> std::vector<std::unique_ptr<Stmt>> {
  try {
    if (tokens[0].type != TokenType::START) {
      BisayaPP::error(tokens[0],
                      "Expect 'SUGOD' at the beginning of the file.");
    }
    advance();
    advance();

    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd()) {
      std::vector<std::unique_ptr<Stmt>> decs = declaration();
      statements.reserve(statements.size() + decs.size());
      statements.insert(statements.end(), std::make_move_iterator(decs.begin()),
                        std::make_move_iterator(decs.end()));
    }

    if (tokens[current].type != TokenType::END) {
      BisayaPP::error(tokens[current],
                      "Expect 'KATAPUSAN' at the end of the file.");
    }
    return statements;
  } catch (const SyntaxError &error) {
    BisayaPP::error(previous(), error.what());
    return {};
  }
}

auto Parser::expressionStatement() -> std::unique_ptr<Stmt> {
  std::unique_ptr<Expr> value = expression();
  consume(TokenType::SEMICOLON, "Expect newline after expression.");
  return std::make_unique<Expression>(std::move(value));
}

auto Parser::printStatement() -> std::unique_ptr<Stmt> {
  std::unique_ptr<Expr> value = expression();

  if(!check(TokenType::SEMICOLON)) {
    BisayaPP::error(peek(), "Expect newline after value.");
  }
  return std::make_unique<Print>(std::move(value));
}

auto Parser::inputStatement() -> std::unique_ptr<Stmt> {
  std::string input;
  std::getline(std::cin, input);

  std::vector<Token> inputTokens =
      std::make_unique<Scanner>(input)->scanTokens();
  std::vector<Token> identifiers;
  std::vector<Token> inputs;

  const size_t inputSize = inputTokens.size() - 1;

  for (size_t i = 0; i < inputSize; i++, current++) {
    if ((tokens[current].type == TokenType::IDENTIFIER) !=
        utility::isLiterals(inputTokens[i].type)) {
      throw SyntaxError(tokens[current], "Incorrect format for Input");
    }

    if (tokens[current].type == TokenType::IDENTIFIER) {
      identifiers.emplace_back(tokens[current]);
      inputs.emplace_back(inputTokens[i]);
    }
  }

  consume(TokenType::SEMICOLON, "Expect newline after value.");

  return std::make_unique<Input>(identifiers, inputs);
}

auto Parser::statement() -> std::unique_ptr<Stmt> {
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

  if (match({TokenType::INPUT})) {
    return inputStatement();
  }

  if (match({TokenType::WHILE})) {
    if (match({TokenType::FOR})) {
      return forStatement();
    }
    return whileStatement();
  }

  if (match({TokenType::BLOCK})) {
    return std::make_unique<Block>(block());
  }

  if (match({TokenType::LEFT_BRACE})) {
    throw SyntaxError(previous(), "Expected 'PUNDOK' before '{'.");
  }

  return expressionStatement();
}

auto Parser::assignment() -> std::unique_ptr<Expr> {
  std::unique_ptr<Expr> expr = orExpression();

  if (match({TokenType::EQUAL})) {
    Token equals = previous();

    if (dynamic_cast<Variable *>(expr.get()) != nullptr) {
      return std::make_unique<Assign>(static_cast<Variable *>(expr.get())->name,
                                      assignment());
    }

    error(equals, "Invalid assignment target.");
  }

  return expr;
}

auto Parser::block() -> std::vector<std::unique_ptr<Stmt>> {
  std::vector<std::unique_ptr<Stmt>> statements;

  consume(TokenType::LEFT_BRACE, "Expect '{' before block.");

  if (check(TokenType::SEMICOLON)) {
    advance();
  }

  while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
    std::vector<std::unique_ptr<Stmt>> decs = declaration();
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

auto Parser::ifStatement() -> std::unique_ptr<Stmt> {
  consume(TokenType::LEFT_PAREN, "Expect '(' after 'KUNG'.");
  std::unique_ptr<Expr> condition = expression();
  consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");

  if (check(TokenType::SEMICOLON)) {
    advance();
  }

  std::unique_ptr<Stmt> thenBranch = statement();
  std::unique_ptr<Stmt> elseBranch = nullptr;

  if (match({TokenType::IF})) {
    if (match({TokenType::BANG})) {
      elseBranch = ifStatement();
    } else if (match({TokenType::ELSE})) {
      elseBranch = statement();
    } else {
      BisayaPP::error(previous(), "Expect 'KUNG' or 'DILI' after 'KUNG'.");
    }
  }

  return std::make_unique<If>(std::move(condition), std::move(thenBranch),
                              std::move(elseBranch));
}

auto Parser::orExpression() -> std::unique_ptr<Expr> {
  std::unique_ptr<Expr> expr = andExpression();

  while (match({TokenType::OR})) {
    Token previousToken = previous();
    expr = std::make_unique<Logical>(std::move(expr), previousToken,
                                     andExpression());
  }
  return expr;
}

auto Parser::andExpression() -> std::unique_ptr<Expr> {
  std::unique_ptr<Expr> expr = equality();

  while (match({TokenType::AND})) {
    Token previousToken = previous();
    expr =
        std::make_unique<Logical>(std::move(expr), previousToken, equality());
  }
  return expr;
}

auto Parser::whileStatement() -> std::unique_ptr<Stmt> {
  consume(TokenType::LEFT_PAREN, "Expect '(' after 'SAMTANG'.");
  std::unique_ptr<Expr> condition = expression();
  consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");

  return std::make_unique<While>(std::move(condition), statement());
}

auto Parser::forStatement() -> std::unique_ptr<Stmt> {
  consume(TokenType::LEFT_PAREN, "Expect 'c' after 'ALANG SA',");

  std::unique_ptr<Stmt> initializer = nullptr;
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

  std::unique_ptr<Expr> condition = nullptr;
  if (!check(TokenType::SEMICOLON)) {
    condition = expression();
  }

  consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");

  std::unique_ptr<Expr> increment = nullptr;
  if (!check(TokenType::RIGHT_PAREN)) {
    increment = expression();
  }

  consume(TokenType::RIGHT_PAREN, "Expect ')' after for clauses.");

  if (check(TokenType::SEMICOLON)) {
    advance();
  }

  std::vector<std::unique_ptr<Stmt>> whileBody;
  whileBody.emplace_back(statement());

  if (increment != nullptr) {
    whileBody.emplace_back(std::make_unique<Expression>(std::move(increment)));
  }

  if (condition == nullptr) {
    condition = std::make_unique<Literal>(true, TokenType::BOOL_TRUE);
  }

  std::vector<std::unique_ptr<Stmt>> forStmt;
  if (initializer != nullptr) {
    forStmt.emplace_back(std::move(initializer));
  }

  forStmt.emplace_back(std::make_unique<While>(
      std::move(condition), std::make_unique<Block>(std::move(whileBody))));

  return std::make_unique<Block>(std::move(forStmt));
}
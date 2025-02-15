#include "Headers/Parser.hpp"
#include "Headers/Expr.hpp"

Parser::Parser(std::vector<Token>& tokens) :
    tokens(tokens) {}

Parser::Parser(std::vector<Token>&& tokens) :
    tokens(std::move(tokens)) {}

Expr* Parser::expression() { return equality(); }

Expr* Parser::equality() {
    Expr* expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL}))
    {
        Token op    = previous();
        Expr* right = comparison();
        expr        = new Binary(expr, op, right);
    }

    return expr;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types)
    {
        if (check(type))
        {
            advance();
            return true;
        }
    }

    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd())
        return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd())
        current++;
    return previous();
}

bool Parser::isAtEnd() { return peek().type == TokenType::END_OF_FILE; }

Token Parser::peek() { return tokens[current]; }

Token Parser::previous() { return tokens[current - 1]; }

Expr* Parser::comparison() {
    Expr* expr = term();

    while (
      match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL}))
    {
        Token op    = previous();
        Expr* right = term();
        expr        = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::term() {
    Expr* expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS}))
    {
        Token op    = previous();
        Expr* right = factor();
        expr        = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::factor() {
    Expr* expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR}))
    {
        Token op    = previous();
        Expr* right = unary();
        expr        = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS}))
    {
        Token op    = previous();
        Expr* right = unary();
        return new Unary(op, right);
    }

    return primary();
}

Expr* Parser::primary() {
    if (match({TokenType::FALSE}))
        return new Literal(false);
    if (match({TokenType::TRUE}))
        return new Literal(true);
    /*     if (match({TokenType::NIL}))
        return new Literal(nullptr); */
    if (match({TokenType::NUMBER, TokenType::STRING}))
        return new Literal(previous().literal);

    if (match({TokenType::LEFT_PAREN}))
    {
        Expr* expr = expression();
        if (!match({TokenType::RIGHT_PAREN}))
            throw std::runtime_error("Expect ')' after expression.");
        return new Grouping(expr);
    }

    throw std::runtime_error("Expect expression.");
}
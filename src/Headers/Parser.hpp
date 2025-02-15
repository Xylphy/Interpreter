#include "Expr.hpp"
#include "Token.hpp"

#include <initializer_list>
#include <vector>

class Parser {
   public:
    Parser(std::vector<Token>& tokens);
    Parser(std::vector<Token>&& tokens);

   private:
    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();
    bool  match(std::initializer_list<TokenType> types);
    bool  check(TokenType type);
    bool  isAtEnd();
    Token advance();
    Token peek();
    Token previous();

    std::vector<Token> tokens;
    int                current = 0;
};

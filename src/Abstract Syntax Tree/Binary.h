#include "Expr.h"
#include "../Token.h"

class Binary : public Expr {
    public:
    Binary(Expr *left, Token op, Expr *right) : left(left), op(op), right(right) {}

    private:
    Expr *left, *right;
    Token op;
};
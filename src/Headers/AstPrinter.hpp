#include "Expr.hpp"

class AstPrinter : public ExprVisitor {
 public:
  auto visitBinaryExpr(const Binary& Expr) -> std::string override;
  auto visitGroupingExpr(const Grouping& Expr) -> std::string override;
  auto visitLiteralExpr(const Literal& Expr) -> std::string override;
  auto visitUnaryExpr(const Unary& Expr) -> std::string override;
  auto parenthesize(const std::string& name, std::initializer_list<Expr*> exprs)
      -> std::string;
  auto print(Expr* expr) -> std::string;

 private:
};
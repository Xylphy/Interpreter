#include "Expr.hpp"

class AstPrinter : public ExprVisitor {
 public:
  auto setPrintResult(Expr* expr) -> void;

  auto visitBinaryExpr(const Binary& Expr) -> void override;
  auto visitGroupingExpr(const Grouping& Expr) -> void override;
  auto visitLiteralExpr(const Literal& Expr) -> void override;
  auto visitUnaryExpr(const Unary& Expr) -> void override;
  auto parenthesize(const std::string& name, std::initializer_list<Expr*> exprs)
      -> void;
  [[nodiscard]] auto get() const -> const std::string&;

 private:
  std::string result;
};
#include "Headers/AstPrinter.hpp"

#include "Headers/Expr.hpp"
#include "Headers/Lib/utility.hpp"
#include "Headers/Token.hpp"

auto AstPrinter::visitBinaryExpr(const Binary& Expr) -> void {
  parenthesize(Expr.op.lexeme, {Expr.left, Expr.right});
}

auto AstPrinter::visitGroupingExpr(const Grouping& Expr) -> void {
  parenthesize("group", {Expr.expression});
}

auto AstPrinter::visitLiteralExpr(const Literal& Expr) -> void {
  if (Expr.value.has_value()) {
    result.append(utility::anyToString(Expr.value));
    return;
  }
  result.append("nil");
}

auto AstPrinter::visitUnaryExpr(const Unary& Expr) -> void {
  parenthesize(Expr.op.lexeme, {Expr.right});
}

auto AstPrinter::setPrintResult(Expr* expr) -> void { expr->accept(*this); }

auto AstPrinter::parenthesize(const std::string& name,
                              std::initializer_list<Expr*> exprs) -> void {
  result.append("( ").append(name);
  for (Expr* expr : exprs) {
    result.append(" ");
    setPrintResult(expr);
  }
  result.append(" )");
}

[[nodiscard]] auto AstPrinter::get() const -> const std::string& {
  return result;
}
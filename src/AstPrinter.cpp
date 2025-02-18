#include "Headers/AstPrinter.hpp"

#include <functional>
#include <typeindex>
#include <unordered_map>

#include "Headers/Expr.hpp"
#include "Headers/Token.hpp"

auto AstPrinter::visitBinaryExpr(const Binary& Expr) -> void {
  parenthesize(Expr.op.lexeme, {Expr.left, Expr.right});
}

auto AstPrinter::visitGroupingExpr(const Grouping& Expr) -> void {
  parenthesize("group", {Expr.expression});
}

auto AstPrinter::visitLiteralExpr(const Literal& Expr) -> void {
  static const std::unordered_map<std::type_index,
                                  std::function<std::string(const std::any&)>>
      typeToString{{typeid(int),
                    [](const std::any& value) -> std::string {
                      return std::to_string(std::any_cast<int>(value));
                    }},
                   {typeid(double),
                    [](const std::any& value) -> std::string {
                      return std::to_string(std::any_cast<double>(value));
                    }},
                   {typeid(std::string),
                    [](const std::any& value) -> std::string {
                      return std::any_cast<std::string>(value);
                    }},
                   {typeid(char), [](const std::any& value) -> std::string {
                      return {1, std::any_cast<char>(value)};
                    }}};

  if (Expr.value.has_value()) {
    auto iterator = typeToString.find(Expr.value.type());
    if (iterator != typeToString.end()) {
      result.append(iterator->second(Expr.value));
      return;
    }
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

[[nodiscard]] auto AstPrinter::get() const -> const std::string& { return result; }
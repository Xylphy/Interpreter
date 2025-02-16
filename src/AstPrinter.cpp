#include "Headers/AstPrinter.hpp"

#include <functional>
#include <typeindex>
#include <unordered_map>

#include "Headers/Expr.hpp"
#include "Headers/Token.hpp"

auto AstPrinter::visitBinaryExpr(const Binary& Expr) -> std::string {
  return parenthesize(Expr.op.lexeme, {Expr.left, Expr.right});
}

auto AstPrinter::visitGroupingExpr(const Grouping& Expr) -> std::string {
  return parenthesize("group", {Expr.expression});
}

auto AstPrinter::visitLiteralExpr(const Literal& Expr) -> std::string {
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
      return iterator->second(Expr.value);
    }
  }
  return "nil";
}

auto AstPrinter::visitUnaryExpr(const Unary& Expr) -> std::string {
  return parenthesize(Expr.op.lexeme, {Expr.right});
}

auto AstPrinter::print(Expr* expr) -> std::string {
  return expr->accept(*this);
}

auto AstPrinter::parenthesize(const std::string& name,
                              std::initializer_list<Expr*> exprs)
    -> std::string {
  std::string res;
  for (Expr* expr : exprs) {
    res += " ";
    res += expr->accept(*this);
  }

  return "(" + name + res + ")";
}
#include "Headers/AstPrinter.hpp"

#include <functional>
#include <typeindex>
#include <unordered_map>

#include "Headers/Expr.hpp"
#include "Headers/Token.hpp"

std::string AstPrinter::visitBinaryExpr(const Binary &Expr) {
  return parenthesize(Expr.op.lexeme, {Expr.left, Expr.right});
}

std::string AstPrinter::visitGroupingExpr(const Grouping &Expr) {
  return parenthesize("group", {Expr.expression});
}

std::string AstPrinter::visitLiteralExpr(const Literal &Expr) {
  static const std::unordered_map<std::type_index,
                                  std::function<std::string(const std::any &)>>
      typeToString{{typeid(int),
                    [](const std::any &value) -> std::string {
                      return std::to_string(std::any_cast<int>(value));
                    }},
                   {typeid(double),
                    [](const std::any &value) -> std::string {
                      return std::to_string(std::any_cast<double>(value));
                    }},
                   {typeid(std::string),
                    [](const std::any &value) -> std::string {
                      return std::any_cast<std::string>(value);
                    }},
                   {typeid(char), [](const std::any &value) -> std::string {
                      return std::string(1, std::any_cast<char>(value));
                    }}};

  if (Expr.value.has_value()) {
    std::unordered_map<
        std::type_index,
        std::function<std::string(const std::any &)>>::const_iterator it =
        typeToString.find(Expr.value.type());
    if (it != typeToString.end())
      return it->second(Expr.value);
  }
  return "nil";
}

std::string AstPrinter::visitUnaryExpr(const Unary &Expr) {
  return parenthesize(Expr.op.lexeme, {Expr.right});
}

std::string AstPrinter::print(Expr *expr) { return expr->accept(*this); }

std::string AstPrinter::parenthesize(std::string name,
                                     std::initializer_list<Expr *> exprs) {
  std::string res;
  for (Expr *expr : exprs) {
    res += " ";
    res += expr->accept(*this);
  }

  return "(" + name + res + ")";
}
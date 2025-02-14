#include "Expr.hpp"

class AstPrinter : public ExprVisitor {
   public:
	std::string visitBinaryExpr(const Binary &Expr) override;
	std::string visitGroupingExpr(const Grouping &Expr) override;
	std::string visitLiteralExpr(const Literal &Expr) override;
	std::string visitUnaryExpr(const Unary &Expr) override;
	std::string parenthesize(std::string name,
							 std::initializer_list<Expr *> exprs);
	std::string print(Expr *expr);

   private:
};
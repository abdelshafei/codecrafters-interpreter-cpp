#include "AstPrinter.hpp"

#include <sstream>

string AstPrinter::print(Expr* expression) const {
    return expression->accept(*this);
}

string AstPrinter::visitBinaryExpr(const Binary& expr) const {
    return parenthesize(expr.oprator->lexeme, expr.left, expr.right);
}

string AstPrinter::visitGroupingExpr(const Grouping& expr) const {
    return parenthesize("group", expr.expression);
}

string AstPrinter::visitLiteralExpr(const Literal& expr) const {
    return visit([](const auto& val) -> string {
        if constexpr (is_same_v<decay_t<decltype(val)>, string>) {
            return val; 
        } else if constexpr (is_same_v<decay_t<decltype(val)>, bool>) {
            return to_string(val);
        } else if constexpr (is_same_v<decay_t<decltype(val)>, nullptr_t>) {
            return "nil";
        } else {
            return to_string(val); 
        }
    }, expr.value);
}

string AstPrinter::visitUnaryExpr(const Unary& expr) const {
    return parenthesize(expr.oprator->lexeme, expr.right);
}

template<typename... Expr>
string AstPrinter::parenthesize(const string& name, Expr*... exprs) const {
    string strBuilder;

    strBuilder += "(";
    strBuilder += name;

    ((strBuilder += " " + exprs->accept(*this)), ...);

    strBuilder += ")";

    return strBuilder;
}
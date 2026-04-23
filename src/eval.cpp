#include <ast.hpp>
#include <stdexcept>
#include <string>
using namespace std;


double NumberExpr::eval() {
    return value;
}

double BinExpr::eval() {
    double leftVal = left->eval();
    double rightVal = right->eval();

    if (op == TokenType::Plus) return leftVal + rightVal;
    else if (op == TokenType::Minus) return leftVal - rightVal;
    else if (op == TokenType::Slash) {
        if (rightVal == 0) throw runtime_error("You cannot divide by zero");
        return leftVal / rightVal;
    }
    else if (op == TokenType::Star) return leftVal * rightVal;

    return 0;
}

double UnaryExpr::eval() {
    double val = -right->eval();

    if (op == TokenType::Minus) return -val;
    return val; 
}
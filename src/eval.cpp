#include <ast.hpp>

using namespace std;


LunaType NumberExpr::eval() {
    return (double)value;
}

LunaType BinExpr::eval() {
    double leftVal = get<double>(left->eval());
    double rightVal = get<double>(right->eval());

    if (op == TokenType::Plus) return leftVal + rightVal;
    else if (op == TokenType::Minus) return leftVal - rightVal;
    else if (op == TokenType::Slash) {
        if (rightVal == 0) throw runtime_error("You cannot divide by zero");
        return leftVal / rightVal;
    }
    else if (op == TokenType::Star) return leftVal * rightVal;
    else if (op == TokenType::EqualEqual) return leftVal == rightVal;
    return 0.0;
}

LunaType UnaryExpr::eval() {
    double val = get<double>(right->eval());

    if (op == TokenType::Minus) return -val;
    return val; 
}

LunaType VarExpr::eval() {
    return memory[name];
}

LunaType AssignExpr::eval() {
    double val = get<double>(value->eval());
    memory[name] = val;
    return val;
}

void IfStmt::eval() {
    LunaType res = condition->eval();

    bool isTrue = false;
    if (holds_alternative<bool>(res)) {
        isTrue = get<bool>(res);
    } else if (holds_alternative<double>(res)) {
        isTrue = get<double>(res) != 0;
    }

    if (isTrue) {
        thenBranch->eval();
    } else if (elseBranch) {
        elseBranch->eval();
    }
}
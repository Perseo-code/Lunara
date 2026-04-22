#pragma once

#include <memory>


// Base expression class
class Expr {
public:
    virtual ~Expr() = default;
};

// A number
class NumberExpr : public Expr {
    int value;
public:
    NumberExpr(int v): value(v) {}
};


// Node for operators
class BinExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
public:
    BinExpr(TokenType o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), left(move(l)), right(move(r)) {} 
};

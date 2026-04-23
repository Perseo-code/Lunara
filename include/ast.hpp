#pragma once

#include <memory>
#include <lexer.hpp>

// Base expression class
class Expr {
public:
    virtual ~Expr() = default;
    virtual double eval() = 0;
};

// A number
class NumberExpr : public Expr {
    int value;
public:
    NumberExpr(int v): value(v) {}
    double eval() override;
};


// Node for operators
class BinExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
public:
    BinExpr(TokenType o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), left(move(l)), right(move(r)) {} 
    double eval() override;
};

class UnaryExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> right;
public:
    UnaryExpr(TokenType o, std::unique_ptr<Expr> r)
        : op(o), right(move(r)) {}
    double eval() override;
};
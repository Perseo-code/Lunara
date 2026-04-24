#pragma once

#include <lunara.hpp>
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
        : op(o), left(std::move(l)), right(std::move(r)) {} 
    double eval() override;
};

class UnaryExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> right;
public:
    UnaryExpr(TokenType o, std::unique_ptr<Expr> r)
        : op(o), right(std::move(r)) {}
    double eval() override;
};

class VarExpr : public Expr {
    std::string name;
public:
    VarExpr(std::string n) : name(std::move(n)) {}
    double eval() override; // Here you'll find in the variable map
};

class AssignExpr : public Expr {
    std::string name;
    std::unique_ptr<Expr> value;
public:
    AssignExpr(std::string n, std::unique_ptr<Expr> v) 
        : name(std::move(n)), value(std::move(v)) {}
    double eval() override; // Here you'll save the data in memory
};
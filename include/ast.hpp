#pragma once

#include <lunara.hpp>
#include <lexer.hpp>
using LunaType = std::variant<double, std::string, bool, std::monostate>;
// Base expression class
class Expr {
public:
    virtual ~Expr() = default;
    virtual LunaType eval() = 0;
};

class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void eval() = 0;
};

// A number
class NumberExpr : public Expr {
    int value;
public:
    NumberExpr(int v): value(v) {}
    LunaType eval() override;
};


// Node for operators
class BinExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
public:
    BinExpr(TokenType o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), left(std::move(l)), right(std::move(r)) {} 
    LunaType eval() override;
};

class UnaryExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> right;
public:
    UnaryExpr(TokenType o, std::unique_ptr<Expr> r)
        : op(o), right(std::move(r)) {}
    LunaType eval() override;
};

class VarExpr : public Expr {
    std::string name;
public:
    VarExpr(std::string n) : name(std::move(n)) {}
    LunaType eval() override; // Here you'll find in the variable map
};

class AssignExpr : public Expr {
    std::string name;
    std::unique_ptr<Expr> value;
public:
    AssignExpr(std::string n, std::unique_ptr<Expr> v) 
        : name(std::move(n)), value(std::move(v)) {}
    LunaType eval() override; // Here you'll save the data in memory
};

class BoolExpr : public Expr {
public:
    LunaType eval() override {
        
    }
};

class ExitExpr : public Expr {
    int exit_code = 0;
public:
    LunaType eval() override {
        std::cout << "Exiting lunara..." << std::endl;
        std::exit(exit_code);
        return 0.0;
    }
};

class IfStmt : public Stmt {
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> thenBranch;
    std::unique_ptr<Stmt> elseBranch;
public:
    void eval() override;
};
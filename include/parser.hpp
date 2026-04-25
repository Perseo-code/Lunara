#pragma once
#include <lunara.hpp>
#include <lexer.hpp>
#include <ast.hpp>

using StmtPtr = std::unique_ptr<Stmt>;
using ExprPtr = std::unique_ptr<Expr>;

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos = 0;
    bool isAtEnd();
    ExprPtr parseFactor();
    ExprPtr parseTerm();
    ExprPtr parseExpression();
    ExprPtr parseUnary();
    ExprPtr parseKeywords();
    StmtPtr ifStatement();
    // Auxiliary functions
    const Token& peek();
    const Token& next();
    const Token& previous();
    Token advance();
    Token consume(TokenType type, std::string message);
    bool check(TokenType token_type);
    bool match(TokenType token_type);
    void Parser::error(Token token, std::string message);
public:
    Parser(std::vector<Token> t) : tokens(move(t)) {}
    ExprPtr parse();  
};
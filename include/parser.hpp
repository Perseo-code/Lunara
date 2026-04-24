#pragma once
#include <lunara.hpp>
#include <lexer.hpp>
#include <ast.hpp>
class Parser {
private:
    std::vector<Token> tokens;
    size_t pos = 0;
    bool isAtEnd();
    std::unique_ptr<Expr> parseFactor();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseAssignment();
    // Auxiliary functions
    const Token& peek();
    const Token& next();
    const Token& previous();
    Token advance();
    bool match(TokenType token_type);
public:
    Parser(std::vector<Token> t) : tokens(move(t)) {}
    std::unique_ptr<Expr> parse();  
};
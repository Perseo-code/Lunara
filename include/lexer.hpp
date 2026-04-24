#pragma once
#include <lunara.hpp>

// Define what's a token
enum class TokenType {
    Number,
    Plus,
    Minus,
    Star,       // Multiplication
    Slash,      // Division
    LeftParen,
    RightParen,
    Var,
    Identifier,
    Equal,
    Exit,
    Eof         // End of file
};

struct Token {
    TokenType type;
    std::string value;
};

static const std::map<std::string, TokenType> keywords {
    {"exit", TokenType::Exit},
    {"assign", TokenType::Var}
};
// The function that separates text in pieces
std::vector<Token> lexer(const std::string& code);
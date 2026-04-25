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
    Null,
    If,
    Elif,
    Else,
    Public,
    Private,
    Class,
    This,
    New,
    Function,
    Return,
    Var,
    Identifier,
    Equal,
    EqualEqual,
    Exit,
    Eof         // End of file
};

struct Token {
    TokenType type;
    std::string value;
};

inline std::map<std::string, TokenType> keywords {
    {"exit", TokenType::Exit},
    {"assign", TokenType::Var},
    {"null", TokenType::Null},
    {"if", TokenType::If},
    {"elif", TokenType::Elif},
    {"else", TokenType::Else},
    {"func", TokenType::Function},
    {"return", TokenType::Return},
    {"public", TokenType::Public},
    {"private", TokenType::Private},
    {"class", TokenType::Class},
    {"this", TokenType::This},
    {"new", TokenType::New}
};
// The function that separates text in pieces
std::vector<Token> lexer(const std::string& code);
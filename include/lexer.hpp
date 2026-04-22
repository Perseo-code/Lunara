#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cctype> // To use isdigit() or isspace()

// Define what's a token
enum class TokenType {
    Number,
    Plus,
    Minus,
    Star,       // Multiplication
    Slash,      // Division
    LeftParen,
    RightParen,
    Eof         // End of file
};

struct Token {
    TokenType type;
    string value;
};

// The function that separates text in pieces
std::vector<Token> lexer(const string& code);
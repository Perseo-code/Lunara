#include <parser.hpp>
#include <stdexcept>
using namespace std;

// Aux functions
const Token& Parser::peek() {
    return tokens.at(pos);
}

const Token& Parser::next() {
    if (isAtEnd()) return {TokenType::Eof, ""};

    return tokens.at(pos++);
}

const Token& Parser::previous() {
    return tokens.at(pos - 1);
}
Token Parser::advance() {
    Token actualToken = peek();
    pos++;
    return actualToken;
}

bool Parser::match(TokenType token_type) {
    if (isAtEnd()) return false;

    if (peek().type == token_type) {
        advance();
        return true;
    }

    return false;
}

bool Parser::isAtEnd() {
    return pos >= tokens.size();
}

// Important functions
unique_ptr<Expr> Parser::parseFactor() {
    if (match(TokenType::Number)) {
        return make_unique<NumberExpr>(stoi(previous().value));
    } else if (match(TokenType::LeftParen)) {
        auto expr = parseExpression();
        if (!match(TokenType::RightParen)) {
            throw runtime_error("Sintax error: ')' Expected.");
        }
        return expr;
    } else if (match(TokenType::Minus) || match(TokenType::Plus)) {
        TokenType op = previous().type;
        auto rgt = parseFactor();
        return make_unique<UnaryExpr>(op, move(rgt));
    }

    throw runtime_error("Expected number or expression on position " + to_string(pos));
}

unique_ptr<Expr> Parser::parseTerm() {
    auto lft = parseFactor();

    while (match(TokenType::Slash) || match(TokenType::Star)) {
        TokenType op = previous().type;
        auto rgt = parseFactor();
        lft = make_unique<BinExpr>(op, move(lft), move(rgt));
    }

    return lft;
}

unique_ptr<Expr> Parser::parseExpression() {
    auto lft = parseTerm();
    while (match(TokenType::Plus) || match(TokenType::Minus)) {
        TokenType op = previous().type;
        auto rgt = parseTerm();
        lft = make_unique<BinExpr>(op, move(lft), move(rgt));
    }

    return lft;
}

unique_ptr<Expr> Parser::parse() {
    // We start parsing from the highest level (+ or -)
    auto root = parseExpression();

    // 2. Did anything remain?
    // If the expression finished but there are still tokens (that are not EOF),
    // Means the user wrote something like "5 + 3 abc"
    if (!isAtEnd() && peek().type != TokenType::Eof) {
        throw runtime_error("Unexpected token after expression: " + peek().value);
    }

    return root;
}
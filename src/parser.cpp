#include <parser.hpp>
#include <stdexcept>
using namespace std;

// Aux functions
const Token& Parser::previous() {
    return tokens.at(pos - 1);
}

const Token& Parser::peek() {
    if (isAtEnd()) {
        return tokens.back(); 
    }
    return tokens.at(pos);
}

Token Parser::advance() {
    if (!isAtEnd()) pos++;
    return previous();
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

unique_ptr<Expr> Parser::parseAssignment() {
    if (match(TokenType::Var)) {
        if (!match(TokenType::Identifier)) throw runtime_error("Expected a variable name after keyword assign");

        string name = previous().value;
        
        if (match(TokenType::Equal)) {
            auto value = parseAssignment();
            return make_unique<AssignExpr>(name, move(value));
        }
        throw runtime_error("Expected '=' on the declaration of " + name);
    }

    return parseExpression();
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
    } else if (match(TokenType::Identifier)) {
        return make_unique<VarExpr>(previous().value); 
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
    auto root = parseAssignment();

    // 2. Did anything remain?
    // If the expression finished but there are still tokens (that are not EOF),
    // Means the user wrote something like "5 + 3 abc"
    if (!isAtEnd() && peek().type != TokenType::Eof) {
        throw runtime_error("Unexpected token after expression: " + peek().value);
    }

    return root;
}
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

    if (check(token_type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType token_type) {
    if (isAtEnd()) return false;

    return peek().type == token_type;
}

Token Parser::consume(TokenType type, string message) {
    if (check(type)) {
        return advance();
    }

    string ErrMsg = "Error in '" + peek().value + "': " + message;

    throw runtime_error(ErrMsg);
}
bool Parser::isAtEnd() {
    return pos >= tokens.size();
}



ExprPtr Parser::parseKeywords() {
    if (match(TokenType::Var)) {
        if (!match(TokenType::Identifier)) throw runtime_error("Expected a variable name after keyword assign");

        string name = previous().value;
        
        if (match(TokenType::Equal)) {
            auto value = parseKeywords();
            return make_unique<AssignExpr>(name, move(value));
        }
        throw runtime_error("Expected '=' on the declaration of " + name);
    }

    else if (match(TokenType::Exit)) {
        int exit_code = 0;
        
        if (match(TokenType::Number)) {
            exit_code = stoi(previous().value);
        }

        return make_unique<ExitExpr>();
    }
    return parseExpression();
}



ExprPtr Parser::parseUnary() {
    if (match(TokenType::Minus) || match(TokenType::Plus)) {
        TokenType op = previous().type;
        auto right = parseUnary();
        return make_unique<UnaryExpr>(op, move(right));
    }

    return parseFactor();
}

ExprPtr Parser::parseFactor() {
    if (match(TokenType::Number)) {
        return make_unique<NumberExpr>(stoi(previous().value));
    } else if (match(TokenType::LeftParen)) {
        auto expr = parseExpression();
        if (!match(TokenType::RightParen)) {
            throw runtime_error("Sintax error: ')' Expected.");
        }
        return expr;
    } else if (match(TokenType::Identifier)) {
        return make_unique<VarExpr>(previous().value); 
    }

    throw runtime_error("Expected number or expression on position " + to_string(pos));
}

ExprPtr Parser::parseTerm() {
    auto lft = parseUnary();

    while (match(TokenType::Slash) || match(TokenType::Star)) {
        TokenType op = previous().type;
        auto rgt = parseUnary();
        lft = make_unique<BinExpr>(op, move(lft), move(rgt));
    }

    return lft;
}

ExprPtr Parser::parseExpression() {
    auto lft = parseTerm();
    while (match(TokenType::Plus) || match(TokenType::Minus)) {
        TokenType op = previous().type;
        auto rgt = parseTerm();
        lft = make_unique<BinExpr>(op, move(lft), move(rgt));
    }

    return lft;
}

ExprPtr Parser::parse() {
    // We start parsing from the highest level (+ or -)
    auto root = parseKeywords();

    // 2. Did anything remain?
    // If the expression finished but there are still tokens (that are not EOF),
    // Means the user wrote something like "5 + 3 abc"
    if (!isAtEnd() && peek().type != TokenType::Eof) {
        throw runtime_error("Unexpected token after expression: " + peek().value);
    }

    return root;
}

StmtPtr Parser::ifStatement() {
    consume(TokenType::LeftParen, "Expected '(' after keyword if");
    auto condition = 
}
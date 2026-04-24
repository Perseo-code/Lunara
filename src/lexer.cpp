#include <lexer.hpp>
using namespace std;


vector<Token> lexer(const string& code) {
    vector<Token> tokens;
    
    for (size_t i = 0; i < code.length(); i++) {
        char c = code[i];

        if (isspace(c)) continue; // Ignore spaces

        if (isdigit(c)) {
            string number;
            while (i < code.length() && isdigit(code[i])) {
                number += code[i++];
            }
            i--; // Adjust index
            tokens.push_back({TokenType::Number, number});
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
            string op(1, c);
            TokenType OpType;

            switch (c)
            {
            case '+':
                OpType = TokenType::Plus;
                break;
            case '-':
                OpType = TokenType::Minus;
                break;
            case '*':
                OpType = TokenType::Star;
                break;
            case '/':
                OpType = TokenType::Slash;
                break;
            case '=':
                OpType = TokenType::Equal;
            default:
                break;
            }

            tokens.push_back({OpType, op});
        }
        else if ( c == '(' || c == ')' ) {
            string paren(1, c);
            TokenType ParenType;
            if ( c == '(' ) ParenType = TokenType::LeftParen;
            else ParenType = TokenType::RightParen;

            tokens.push_back({ParenType, paren});
        } else if (isalpha(code[i])) {
            string name = "";
            while (i < code.length() && isalnum(code[i])) { // Letters or numbers
                name += code[i];
                i++;
            }
            i--; // Readjust

            if (keywords.count(name)) {
                tokens.push_back({keywords.at(name), name});
            } else {
                tokens.push_back({TokenType::Identifier, name});
            }
        }
    }
    return tokens;
}
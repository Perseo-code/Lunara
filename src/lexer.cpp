#include <lexer.hpp>
using namespace std;


vector<Token> lexer(const string& code) {
    vector<Token> tokens;
    
    for (int i = 0; i < code.length(); i++) {
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
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            string op(1, c);
            TokenType OpType;

            if ( c == '+' ) OpType = TokenType::Plus;
            else if ( c == '-' ) OpType = TokenType::Minus;
            else if ( c == '*' ) OpType = TokenType::Star;
            else OpType = TokenType::Slash;

            tokens.push_back({OpType, op});
        }
    }
    return tokens;
}
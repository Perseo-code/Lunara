#include <parser.hpp>
#include <lexer.hpp>
#include <ast.hpp>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "Lunara REPL C++ Version.0.1" << endl;
    while (true) {
        cout << ">>> ";
        string code;
        getline(cin, code);
        if (code == "exit") {
            break;
        }
        
        vector<Token> tokens = lexer(code);
        Parser* parser = new Parser(tokens);
        parser->parse();
    }
    return 0;
}
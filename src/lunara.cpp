#include <parser.hpp>
#include <lexer.hpp>
#include <ast.hpp>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "Lunara REPL C++ Version.0.1" << endl;
    memory["pi"] = 3.1415;
    while (true) {
        cout << ">>> ";
        string code;
        getline(cin, code);
        if (code == "exit") {
            break;
        }
        
        try {
            vector<Token> tokens = lexer(code);
            Parser Lparser(tokens);

            unique_ptr<Expr> root = Lparser.parse();
            if (root) {
                double result = root->eval();
                cout << result << endl;
            }
        } catch (const exception& e) {
            cerr << "Lunara error: " << e.what() << endl;
        }
    }
    return 0;
}
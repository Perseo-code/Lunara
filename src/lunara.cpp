#include <parser.hpp>
#include <lexer.hpp>
#include <ast.hpp>
using namespace std;

int main() {
    cout << "Lunara REPL C++ Version." << endl;
    while (true) {
        cout << ">>> ";
        string code;
        getline(cin, code);
        if (code == "exit") {
            break;
        }
        
    }
    return 0;
}
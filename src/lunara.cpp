#include <parser.hpp>
#include <lexer.hpp>
#include <ast.hpp>
using namespace std;

void runFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Couldn't open file " << path << endl;
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    // Aquí decides: ¿Quieres procesar línea a línea o todo el bloque?
    // Para empezar, procesemos línea a línea:
    stringstream ss(content);
    string line;
    while (getline(ss, line)) {
        if (line.empty()) continue;
        
        try {
            vector<Token> tokens = lexer(line);
            Parser Lparser(tokens);

            unique_ptr<Expr> root = Lparser.parse();
            if (root) {
                double result = get<double>(root->eval());
                cout << result << endl;
            }
        } catch (const exception& e) {
            cerr << "Error in file [" << path << "]: " << e.what() << endl;
        }
    }
}

void runREPL() {
    string code;
    while (true) {
        cout << ">>> ";
        getline(cin, code);
        
        try {
            vector<Token> tokens = lexer(code);
            Parser Lparser(tokens);

            unique_ptr<Expr> root = Lparser.parse();
            if (root) {
                double result = get<double>(root->eval());
                cout << result << endl;
            }
        } catch (const exception& e) {
            cerr << "Lunara error: " << e.what() << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "Lunara REPL C++ Version.0.1" << endl;
    memory["pi"] = 3.1415;
    if (argc > 1) {
        runFile(argv[1]);
    } else {
        runREPL();
    }
    return 0;
}
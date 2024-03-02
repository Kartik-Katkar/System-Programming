#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cctype>
#include <iomanip>

enum TokenType {
    KEYWORD, IDENTIFIER, SYMBOL, LITERAL
};

struct Token {
    TokenType type;
    std::string value;
};

struct Variable {
    std::string name;
    std::string dataType;
};

std::map<std::string, int> typeSizes = {
    {"int", 4},
    {"double", 8},
    {"float", 4},
    {"bool", 1},
    {"char", 2}
};

std::vector<Token> tokenize(const std::string& code) {
    std::vector<Token> tokens;
    std::string currentToken;

    for (char c : code) {
        if (std::isspace(c)) {
            if (!currentToken.empty()) {
                Token token;
                if (typeSizes.find(currentToken) != typeSizes.end()) {
                    token.type = KEYWORD;
                    token.value = currentToken;
                } else {
                    token.type = IDENTIFIER;
                    token.value = currentToken;
                }
                tokens.push_back(token);
                currentToken.clear();
            }
        } else if (std::isalnum(c) || c == '_') {
            currentToken += c;
        } else {
            if (!currentToken.empty()) {
                Token token;
                if (typeSizes.find(currentToken) != typeSizes.end()) {
                    token.type = KEYWORD;
                    token.value = currentToken;
                } else {
                    token.type = IDENTIFIER;
                    token.value = currentToken;
                }
                tokens.push_back(token);
                currentToken.clear();
            }

            if (std::ispunct(c)) {
                Token token;
                token.type = SYMBOL;
                token.value = c;
                tokens.push_back(token);
            }
        }
    }

    return tokens;
}

void printSymbolTable(const std::vector<Token>& tokens) {
    int address = 1000;
    std::vector<Variable> variables;

    std::cout << std::left << std::setw(20) << "Symbol" << std::setw(15) << "Type"
              << std::setw(10) << "Size" << std::setw(10) << "Address" << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type == KEYWORD) {
            Variable variable;
            variable.dataType = tokens[i].value;

            // Assuming the next token is an identifier (variable name)
            if (i + 1 < tokens.size() && tokens[i + 1].type == IDENTIFIER) {
                variable.name = tokens[i + 1].value;
                std::cout << std::left << std::setw(20) << variable.name
                          << std::setw(15) << variable.dataType
                          << std::setw(10) << typeSizes[variable.dataType]
                          << std::setw(10) << address << std::endl;

                variables.push_back(variable);
                address += typeSizes[variable.dataType];
                ++i;  // Skip the identifier
            }
        }
    }
}

int main() {
    std::ifstream inputFile("input.c");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string code((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::vector<Token> tokens = tokenize(code);
    printSymbolTable(tokens);

    return 0;
}

// a.c size 149 bytes 
// b.c size 157 bytes 

// 149 + 157 = 306 bytes

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct Variable {
    string name;
    string type;
    int size;
    int address;
};

// struct externvar
// {   string name;
//     string type;
// };


struct SymbolTable {
    vector<Variable> variables;
    
};

void readFileSizeAndContent(string filename, int& size, string& content) {
    ifstream file(filename, ios::binary | ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        // gives the size of file in bytes
        file.seekg(0, ios::beg);
        content.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        // stores the characters in the content variable 
    }
}

void parseVariables(const string& content, SymbolTable& symbolTable, int startAddress) {
    istringstream iss(content);
    string line;

    while (getline(iss, line)) {
        istringstream lineStream(line);
        string type, name;

        if (lineStream >> type >> name) {
            int size;
            if (type == "int") size = sizeof(int);
            else if (type == "char") size = sizeof(char);
            else if (type == "float") size = sizeof(float);
            else if (type == "double") size = sizeof(double);
            else continue; // Skip unsupported types

            symbolTable.variables.push_back({name, type, size, startAddress});
            startAddress += size;
        }
    }
}

void parseExtVariables(const string& content, SymbolTable& symbolTable) {
    istringstream iss(content);
    string line;

    while (getline(iss, line)) {
        istringstream lineStream(line);
        string externKeyword, type, name;

        if (lineStream >> externKeyword >> type >> name) {
            // Check if the line represents an external variable declaration
            if (externKeyword == "extern") {
                // Add the external variable to the symbol table
                symbolTable.variables.push_back({name, type, 0, -1}); // External variables have size 0 and address -1
            }
        }
    }
}


void printSymbolTable(const SymbolTable& symbolTable, int startAddress) {
    cout << "Variable\tType\tSize\tAddress" << endl;
    for (const auto& variable : symbolTable.variables) {
        cout << variable.name << "\t\t" << variable.type << "\t" << variable.size << "\t" << variable.address << endl;
    }
    cout << endl;
}
void printSymbolTablet(const SymbolTable& symbolTable) {
    cout << "Variable\tType" << endl;
    for (const auto& variable : symbolTable.variables) {
        cout << variable.name << "\t\t" << variable.type << endl;
    }
    cout << endl;
}

void printSymbolTables(const SymbolTable& symbolTable1, const SymbolTable& symbolTable2, int startAddress) {
    cout << "Variable\tType\tSize\tAddress" << endl;

    for (const auto& variable : symbolTable1.variables) {
        cout << variable.name << "\t\t" << variable.type << "\t" << variable.size << "\t" << variable.address << endl;
    }

    for (const auto& variable : symbolTable2.variables) {
        cout << variable.name << "\t\t" << variable.type << "\t" << variable.size << "\t" << variable.address << endl;
    }

    cout << endl;
}

int main() {
    int memorySize;
    cout << "Enter the size of memory: ";
    cin >> memorySize;

    int sizeA, sizeB;
    string contentA, contentB;
    readFileSizeAndContent("a.c", sizeA, contentA);
    readFileSizeAndContent("b.c", sizeB, contentB);

    int totalSize = sizeA + sizeB;

    if (totalSize > memorySize) {
        cout << "Insufficient memory." << endl;
        return 1;
    }

    SymbolTable symbolTableA, symbolTableB, symbolTableC, symbolTableD;

    // Parse variables and populate symbol tables
    parseVariables(contentA, symbolTableA, 1000);
    parseVariables(contentB, symbolTableB, 5000);

    parseExtVariables(contentA, symbolTableC);
    parseExtVariables(contentB, symbolTableD);

    cout << "Symbol Table for a.c" << endl;
    printSymbolTable(symbolTableA, 1000);

    cout << "Symbol Table for extern a.c" << endl;
    printSymbolTablet(symbolTableC);

    cout << "Symbol Table for b.c" << endl;
    printSymbolTable(symbolTableB, 5000);

    cout << "Symbol Table for extern b.c" << endl;
    printSymbolTablet(symbolTableD);

    cout << "Global variable Table" << endl;
    printSymbolTables(symbolTableA, symbolTableB, 5000);

    return 0;
}

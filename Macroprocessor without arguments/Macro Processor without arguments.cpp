#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Function prototypes
void processMacroDefinition(map<int, pair<string, int>>& MNT, map<int, string>& MDT, int& imnt, int& imdt, const string& line);
void processCodeExpansion(const map<int, pair<string, int>>& MNT, const map<int, string>& MDT, int& imnt, int& imdt, const string& word1, bool secondPass);

void printHorizontalLine(int length) {
    cout << "+";
    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << "+" << endl;
}

void printTableHeader(const string& title, int length) {
    printHorizontalLine(length);
    cout << "| " << title;
    for (int i = title.length() + 1; i < length; i++) {
        cout << " ";
    }
    cout << "|" << endl;
    printHorizontalLine(length);
}

int main() {

    int imdt = 11;
    int imnt = 1;

    map<int, pair<string, int>> MNT;
    map<int, string> MDT;

    fstream myfile;
    myfile.open("input.txt", ios::in);

    if (myfile.is_open()) {
        string line;
        int variablecheck = 2;
        bool secondPassActive = false; // Flag to track the second pass

        while (getline(myfile, line)) {
            istringstream iss(line);
            string word1, word2;

            if (!(iss >> word1 >> word2)) {
                // there is only 1 word
                word1 = line;
            }

            if (word1 == "MACRO") {
                processMacroDefinition(MNT, MDT, imnt, imdt, line);
                variablecheck = 2;
            } else if (word1 == ".Code") {
                variablecheck = 4;
                secondPassActive = true; // Activate second pass
            } else if (word1 == "Endp") {
                variablecheck = 2;
                secondPassActive = false; // Deactivate second pass
            }

            if (variablecheck == 2) {
                MDT[imdt] = line;
                imdt++;
            } else if (variablecheck == 4) {
                processCodeExpansion(MNT, MDT, imnt, imdt, word1, secondPassActive);
            }
        }

        myfile.close();

        // Print MNT
        printTableHeader("Macro Name Table (MNT)", 40);
        cout << "| Macro Name\t MDT index" << endl;
        for (const auto& entry : MNT) {
            cout << "| " << entry.second.first << "\t\t " << entry.second.second << endl;
        }
        printHorizontalLine(40);
        cout << "\n\n\n";

        // Print MDT
        printTableHeader("Macro Definition Table (MDT)", 40);
        cout << "| MDT Index\t Data Card" << endl;
        for (const auto& entry : MDT) {
            cout << "| " << entry.first << "\t\t " << entry.second << endl;
        }
        printHorizontalLine(40);
    } else {
        cout << "No file " << endl;
    }

    return 0;
}

void processMacroDefinition(map<int, pair<string, int>>& MNT, map<int, string>& MDT, int& imnt, int& imdt, const string& line) {
    MNT[imnt] = make_pair(line, imdt);
    imnt++;
}

void processCodeExpansion(const map<int, pair<string, int>>& MNT, const map<int, string>& MDT, int& imnt, int& imdt, const string& word1, bool secondPass) {
    int mntindex = 1;
    bool flag = false;

    for (const auto& entry : MNT) {
        if (entry.second.first == word1) {
            flag = true;
            imdt = entry.second.second;
            break;
        }
        mntindex++;
    }

    if (flag && secondPass) {
        cout << "Expanded code for macro '" << word1 << "':" << endl;
        while (MDT.find(imdt) != MDT.end()) {
            string wrd = MDT.at(imdt);
            if (wrd != "Mend" && wrd != "Endp") {
                cout << wrd << endl;
                imdt++;
            } else {
                break;
            }
        }
    }
}

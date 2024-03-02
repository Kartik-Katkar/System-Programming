#include "Object_Code.h"
#include "Mnemonic.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
Object_Code::Object_Code()
{
    //ctor
}

Object_Code::~Object_Code()
{
    //dtor
}

vector <std::array<string, 3>> symbolTable;
vector <pair<string, string>> base_addresses;
Mnemonic mnemonic;
bool base = false;

int Object_Code :: operation (int a, int b, string operatoor)
{
    if (operatoor == "+")
    {
        return a+b;
    }
    else if (operatoor == "-")
    {
        return a-b;
    }
    else if (operatoor == "/")
    {
        return a/b;
    }
    else if (operatoor == "*")
    {
        return a*b;
    }
}
bool Object_Code :: checkAandR (string exprssion1, string operation, string exprssion2)
{
    if (exprssion1 == "Absolute" && exprssion2 == "Relocatable" && operation == "-")
    {
        return false;
    }
    else if (exprssion1 == "Relocatable" && exprssion2 == "Absolute" && operation == "/")
    {
        return false;
    }
    else if (exprssion1 == "Relocatable" && exprssion2 == "Absolute" && operation == "*")
    {
        return false;
    }
    else if (exprssion1 == "Absolute" && exprssion2 == "Relocatable" && operation == "/")
    {
        return false;
    }
    else if (exprssion1 == "Absolute" && exprssion2 == "Relocatable" && operation == "*")
    {
        return false;
    }
    else if (exprssion1 == "Relocatable" && exprssion2 == "Relocatable" && operation == "+")
    {
        return false;
    }
    else if (exprssion1 == "Relocatable" && exprssion2 == "Relocatable" && operation == "*")
    {
        return false;
    }
    else if (exprssion1 == "Relocatable" && exprssion2 == "Relocatable" && operation == "/")
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Object_Code :: checkIfExp(string attribute) {
    regex expr("^([0-9|A-Z]+)([*|+|/|/|\-])([0-9|A-Z]+)$");
    smatch matcher;
    return std::regex_search(attribute, matcher, expr);
}

std::string Object_Code :: getRegisterNum(string registerN) {
    if (registerN == "A") {
        return "0";
    } else if (registerN == "X") {
        return "1";
    } else if (registerN == "L") {
        return "2";
    } else if (registerN == "b") {
        return "3";
    } else if (registerN == "S") {
        return "4";
    } else if (registerN == "T") {
        return "5";
    } else if (registerN == "F") {
        return "6";
    }
}
std::vector<std::string> Object_Code :: split(string line) {
    std::string text = line;

    std::istringstream iss(text);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    return results;
}

string Object_Code :: calcDisplacement(string address, string nextaddress, string attribute, bool isPlus) {
    base = false;
    stringstream str;
    str<<nextaddress;
    signed pcAddr;
    signed baseAddr;
    signed tAddr;
    signed disp;
    bool found = false;
    bool isNumber = true;
    str>>std::hex>>pcAddr;
    if (isPlus) {
        pcAddr = 0x0;
    }
    string tempAttr = "";
    if (attribute[0] == '#') {
        for (int i = 1; i < attribute.length(); i++) {
            tempAttr += attribute[i];
            if (!isdigit(attribute[i])) {
                isNumber = false;
            }
        }
    } else if (attribute == "*") {
        stringstream str;
        str<<address;
        str>>hex>>pcAddr;
        cout<<to_string(pcAddr)<<endl;
        return to_string(pcAddr);
    } else {
        tempAttr = attribute;
        isNumber = false;
    }

    if (isNumber) {
        return tempAttr;
    }

    // checks if it's an expression and get the 2 operands & operator
    string operand1 = "";
    string operand2 = "";
    string operatoor = "";
    bool isOperand1 = false;
    bool isOperand2 = false;
    int a;
    int b;
    bool operand1Flag = true;
    bool isExp = false;
    if (checkIfExp(attribute)) {
        isExp = true;
        for (int i = 0; i < attribute.length(); i++) {
            if (attribute[i] == ' ') {
                continue;
                operand1Flag = false;
            } else if (attribute[i] == '+') {
                operatoor = "+";
                operand1Flag = false;
            } else if (attribute[i] == '-') {
                operatoor = "-";
                operand1Flag = false;
            } else if (attribute[i] == '*') {
                operatoor = "*";
                operand1Flag = false;
            } else if (attribute[i] == '/') {
                operatoor = "/";
                operand1Flag = false;
            } else {
                if (operand1Flag) {
                    operand1 += attribute[i];
                } else {
                    operand2 += attribute[i];
                }
            }
        }

        for (int i=0 ; i < symbolTable.size(); i++) {
            std::array<string,3> temp=symbolTable[i];
            if (temp[0] == operand1) {
                a = stoi(temp[1]);
                isOperand1 = true;
                continue;
            }

            if (temp[0] == operand2) {
                b = stoi(temp[1]);
                isOperand2 = true;
                continue;
            }

            if (isOperand1 && isOperand2) {
                break;
            }
        }

        if (!isOperand1) {
            a = stoi(operand1);
        }

        if (!isOperand2) {
            b = stoi(operand2);
        }

        tAddr = operation(a, b, operatoor);

    }

    if (!isExp) {
        // searches for the target symbol in the symbol table
        for (int i=0 ; i < symbolTable.size(); i++) {
            std::array<string,3> temp=symbolTable[i];
            if (temp[0] == tempAttr) {
                int tempTarget = stoi(temp[1]);
                stringstream str3;
                str3<<to_string(tempTarget);
                str3>>dec>>tAddr;
                found = true;
                break;
            }
        }

        // checks if the symbol table doesn't have the target symbol
        if (!found && attribute[0] != '#') {
            return "error the target address is wrong as no such target exists";
        }

        if (!found) {
            tAddr = 0x0;
        }
        if (attribute[0] == '#') {
            pcAddr = 0x0;
        }
    }

    disp = tAddr - pcAddr;

    // checks if the displacement is less than 2047 or of format 4
    if (disp <= 2047 || isPlus) {
        return to_string(disp);
    } else {
        if (base_addresses.empty()) {
            return "error base relative can't happen";
        } else {
            attribute = base_addresses[base_addresses.size() - 1].second;
            signed tempBase;
            for (int i=0 ; i < symbolTable.size(); i++) {
                std::array<string,3> temp=symbolTable[i];
                if (temp[0] == attribute) {
                    int tempTarget = stoi(temp[1]);
                    stringstream str3;
                    str3<<to_string(tempTarget);
                    str3>>dec>>tempBase;
                    found = true;
                    break;
                }
            }
            disp = tAddr - tempBase;
            base = true;
            return to_string(disp);
        }
    }
}

std::set<std::string> Object_Code :: fillExceptionsIndex() {
    std::set<std::string> exceptionsIndex;
    exceptionsIndex.insert("ADDR");
    exceptionsIndex.insert("COMPR");
    exceptionsIndex.insert("RMO");
    return exceptionsIndex;
}

void Object_Code :: setSymbolTable(vector <std::array<string, 3>> s) {
    symbolTable = s;
}

std::vector<std::string> Object_Code :: getErrorMes() {
    vector<string> errorsMes;
    errorsMes.push_back("error base relative can't happen");
    errorsMes.push_back("error the target address is wrong as no such target exists");
    return errorsMes;
}

string Object_Code :: evaluateLine(string line, string nextline) {
    std::vector<std::string> results = split(line);
    std::vector<std::string> nextresults;
    if (nextline != "") {
        nextresults = split(nextline);
    }
    std::set<std::string> exceptionsIndex;
    std::vector<std::string> errorsMes;
    exceptionsIndex = fillExceptionsIndex();
    errorsMes = getErrorMes();
    bool extensions[6] = {false};
    int resultsSize = results.size();
    string mnemonicName;
    string operand;
    string disp;

    if (resultsSize == 5) { // if the length of the line words is 5
        mnemonicName = results[3];

        // checks for format 4 "e"
        if (mnemonicName[0] == '+') {
            extensions[5] = true;
            string temp = "";
            for (int j = 1; j < mnemonicName.length(); j++) {
                temp += mnemonicName[j];
            }
            mnemonicName = temp;
        }

        // checks if the mnemonic is BASE and add the operand to the base vector
        if (mnemonicName == "BASE") {
            pair<string, string> p;
            p.first = results[1];
            p.second = results[4];
            base_addresses.push_back(p);

            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            spaces = "";
            for (int j = 0; j < 10; j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;

            return "";
        }

        if ((results[4][0] == 'X' || results[4][0] == 'C') && results[4][1] == '\'') {
            string tempWord = "";
            if (results[4][0] == 'X') {
                for (int i = 2; i < results[4].length() - 1; i++) {
                    tempWord += results[4][i];
                }
                cout<<"X : "<<tempWord<<endl;
            } else if (results[4][0] == 'C') {
                for (int i = 2; i < results[4].length() - 1; i++) {
                    int ascii = results[4][i];
                    stringstream str9;
                    str9<<hex<<ascii;
                    tempWord += str9.str();
                }
                cout<<"C : "<<tempWord<<endl;
            }

            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;
            printing += tempWord;
            spaces = "";
            for (int j = 0; j < 10 - tempWord.length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;

            return tempWord;

        }

        // checks if the mnemonic is WORD or BYTE and make its op code
        if (mnemonicName == "WORD" || mnemonicName == "BYTE") {
            int tempWord;
            tempWord = stoi(results[4]);
            string res;
            stringstream ss;
            ss<<setfill('0')<<setw(6)<<hex<<tempWord;
            res = ss.str();

            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            printing += res;
            spaces = "";
            for (int j = 0; j < 10 - res.length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;

            return res;
        }

        // checks if the mnemonic doesn't have op code
        if (!mnemonic.isFound(mnemonicName) || mnemonicName[0] == '.' || results[0][0] == '*') {
            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            spaces = "";
            for (int j = 0; j < 10; j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;
            return "";
        }

        if (mnemonic.getLength(results[3]) == 2) {
            string register1 = "";
            string register2 = "";
            register1 += results[4][0];
            register2 += results[4][2];
            string res = "";
            res = mnemonic.getOpCode(results[3]) + getRegisterNum(register1) + getRegisterNum(register2);

            string printing = "";
            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            printing += res;
            spaces = "";
            for (int j = 0; j < 10 - res.length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;
            return res;
        } else { // checks for indexed "x"
            operand = results[4];
            if (operand[operand.length() - 1] == 'X' && operand[operand.length() - 2] == ',') {
                extensions[2] = true;
                string temp = "";
                for (int j = 0; j < operand.length() - 2; j++) {
                    temp += operand[j];
                }
                operand = temp;
            }
        }

        // checks for indirect and immediate "n, i"
        if (results[4][0] == '#') {
            extensions[0] = false;
            extensions[1] = true;
        } else if (results[4][0] == '@') {
            extensions[0] = true;
            extensions[1] = false;
        } else {
            extensions[0] = true;
            extensions[1] = true;
        }

    } else if (resultsSize == 4) { // if the length of the line words is 4
        mnemonicName = results[2];

        // checks for format 4 "e"
        if (mnemonicName[0] == '+') {
            extensions[5] = true;
            string temp = "";
            for (int j = 1; j < mnemonicName.length(); j++) {
                temp += mnemonicName[j];
            }
            mnemonicName = temp;
        }

        // checks if the mnemonic is BASE and add the operand to the base vector
        if (mnemonicName == "BASE") {
            pair<string, string> p;
            p.first = results[1];
            p.second = results[3];
            base_addresses.push_back(p);
            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            spaces = "";
            for (int j = 0; j < 10; j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;
            return "";
        }


        if ((results[3][0] == 'X' || results[3][0] == 'C') && results[3][1] == '\'') {
            string tempWord = "";
            if (results[3][0] == 'X') {
                for (int i = 2; i < results[3].length() - 1; i++) {
                    tempWord += results[4][i];
                }
                cout<<"X : "<<tempWord<<endl;
            } else if (results[3][0] == 'C') {
                for (int i = 2; i < results[3].length() - 1; i++) {
                    int ascii = results[3][i];
                    stringstream str9;
                    str9<<hex<<ascii;
                    tempWord += str9.str();
                }
                cout<<"C : "<<tempWord<<endl;
            }

            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;
            printing += tempWord;
            spaces = "";
            for (int j = 0; j < 10 - tempWord.length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;

            return tempWord;

        }

        // checks if the mnemonic is WORD or BYTE and make its op code
        if (mnemonicName == "WORD" || mnemonicName == "BYTE") {
            int tempWord;
            tempWord = stoi(results[3]);
            string res;
            stringstream ss;
            ss<<setfill('0')<<setw(6)<<hex<<tempWord;
            res = ss.str();

            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            printing += res;
            spaces = "";
            for (int j = 0; j < 10 - res.length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;
            return res;
        }

        // checks if the mnemonic doesn't have op code
        if (!mnemonic.isFound(mnemonicName) || mnemonicName[0] == '.' || results[0][0] == '*') {
            string printing = "";

            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            spaces = "";
            for (int j = 0; j < 10; j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;
            return "";
        }

        if (mnemonic.getLength(results[2]) == 2) {
            string register1 = "";
            string register2 = "";
            register1 += results[3][0];
            register2 += results[3][2];
            string res = "";
            res = mnemonic.getOpCode(results[2]) + getRegisterNum(register1) + getRegisterNum(register2);

            string printing = "";
            printing += results[1];
            string spaces = "";
            for (int j = 0; j < 13 - results[1].length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            printing += res;
            spaces = "";
            for (int j = 0; j < 10 - res.length(); j++) {
                spaces += " ";
            }
            printing += spaces;

            for (int i = 2; i < results.size(); i++) {
                printing += results[i];
                string spaces = "   ";
                printing += spaces;
            }

            cout<<printing<<endl<<endl;
            return res;

        } else { // checks for indexed "x"
            operand = results[3];
            if (operand[operand.length() - 1] == 'X' && operand[operand.length() - 2] == ',') {
                extensions[2] = true;
                string temp = "";
                for (int j = 0; j < operand.length() - 2; j++) {
                    temp += operand[j];
                }
                operand = temp;
            }
        }

        // checks for indirect and immediate "n, i"
        if (results[3][0] == '#') {
            extensions[0] = false;
            extensions[1] = true;
        } else if (results[3][0] == '@') {
            extensions[0] = true;
            extensions[1] = false;
        } else {
            extensions[0] = true;
            extensions[1] = true;
        }
    } else {
        return "";
    }

    // calculating the displacement and checks for PC or Base relative
    if (nextline != "") {
        disp = calcDisplacement(results[1], nextresults[1], operand, extensions[5]);
        if (extensions[5]) {
            extensions[3] = false;
            extensions[4] = false;
        } else if (operand[0] == '#') {
            extensions[3] = false;
            extensions[4] = false;
        } else if (base) {
            extensions[3] = true;
            extensions[4] = false;
        } else {
            extensions[3] = false;
            extensions[4] = true;
        }
    }

    // printing out the extension of the line
    string tempExten;
    for (int i = 0; i < 6; i++) {
        if (extensions[i]) {
            tempExten += "1";
        } else {
            tempExten += "0";
        }
    }

    // checks for error calculating the displacement
    if ((find(errorsMes.begin(), errorsMes.end(), disp) != errorsMes.end()) || disp == "") {
        return disp;
    }

    // converting the displacement into hex and cut it according to format 3 or 4
    int hexDisp = stoi(disp);
    stringstream str;
    str<<setfill('0') << setw(8)<<std::hex<<hexDisp;
    string res = str.str();
    string ans;
    if (extensions[5]) {
        ans = res.substr(3, 7);
    } else {
        ans = res.substr(5, 7);
    }

    // converts the opcode into binary and removes the last 2 bits
    stringstream ss;
    ss << hex << mnemonic.getOpCode(mnemonicName);
    unsigned n;
    ss >> n;
    bitset<8> b(n);
    // shifting the op code by 2 bits
    n = n / (4);
    bitset<6> b3(n);
    stringstream ss3;
    ss3 << hex << uppercase << b3.to_ulong();

    // making the opcode concatenation
    bitset<12> b4;
    // adding the op code
    for (int i = 6; i < 12; i++) {
        if (b3[i - 6]) {
            b4.set(i);
        } else {
            b4.reset(i - 6);
        }

    }

    // adding the extension
    for (int i = 0; i < 6; i++) {
        if (tempExten[5 - i] == '0') {
            b4.reset(i);
        } else {
            b4.set(i);
        }
    }

    stringstream ss4;
    ss4 << hex << uppercase << b4.to_ulong();

    // concatenates all results into one string and converts it into hex
    string finOpCode = b3.to_string();
    string finExten = tempExten;
    string finDisp = ans;
    string finRes = ss4.str() + finDisp;
    string printing = "";

    printing += results[1];
    string spaces = "";
    for (int j = 0; j < 13 - results[1].length(); j++) {
        spaces += " ";
    }
    printing += spaces;

    printing += finRes;
    spaces = "";
    for (int j = 0; j < 10 - finRes.length(); j++) {
        spaces += " ";
    }
    printing += spaces;

    for (int i = 2; i < results.size(); i++) {
        printing += results[i];
        string spaces = "   ";
        printing += spaces;
    }

    cout<<"\t\tn="<<tempExten[0]<<"  i="<<tempExten[1]<<"  x="<<tempExten[2]<<"  b="<<tempExten[3]<<"  p="<<tempExten[4]<<"  e="<<tempExten[5]<<endl;
    cout<<printing<<endl<<endl;

    return finRes;
}

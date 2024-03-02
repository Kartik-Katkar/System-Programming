#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include "Mnemonic.h"
#include "Object_Code.h"
using namespace std;

int operation (int a, int b, string operatoor)
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
int hexadecimalToDecimal(char hexVal[]){
    int len = strlen(hexVal);
    // Initializing base value to 1, i.e 16^0
    int base = 1;
    int dec_val = 0;
    // Extracting characters as digits from last character
    for (int i=len-1; i>=0; i--){
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (hexVal[i]>='0' && hexVal[i]<='9'){
            dec_val += (hexVal[i] - 48)*base;
            // incrementing base by power
            base = base * 16;
        }
        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i]>='A' && hexVal[i]<='F'){
            dec_val += (hexVal[i] - 55)*base;
            // incrementing base by power
            base = base*16;
        } else if (hexVal[i]>='a' && hexVal[i]<='f'){
            dec_val += (hexVal[i] - 87)*base;
            // incrementing base by power
            base = base*16;
        }
    }
    return dec_val;
}

string decimalToHexadecimal(int n){
    stringstream ss;
    ss<<setfill('0') << setw(8)<<std::hex<<n;
    string s = ss.str();
    return s;
}

bool checkAandR (string exprssion1, string operation, string exprssion2)
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
void  errorsM(int &counter, stringstream &ss,vector<string> &code, int &lineNumber, string &start, string &line, bool &check, string &error)
{
    string state ;
    string spacesLine = "";
    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
    {
        spacesLine+=" ";
    }
    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
    lineNumber++;
    code.push_back(state);
    check=true;
    code.push_back(error);
}
bool checkLableSymbol(  vector <std::array<string, 3>> &symbolTable, string first, int &valuF, string &absF)
{
    for (int i = 0 ; i < symbolTable.size() ; i++)
    {
        if (symbolTable[i][0] == first)
        {
            absF =  symbolTable[i][2];
            stringstream geek(symbolTable[i][1]);
            valuF = 0;
            geek >> valuF;
            return true;
        }
    }
    return false;
}
void exeprssionForReserving(string &first,string &second, string &op, vector <std::array<string, 3>> &symbolTable, int &counter,vector<string> &code, int &lineNumber, string &start, string &line, bool &check, bool wordture)
{
    regex staRegex("^[0-9]{0,4}$");
    smatch match2;
    string absF;
    string absS;
    bool cF = false;
    bool cS = false;
    int valuF;
    int valuS;

    if (regex_search(first, match2, staRegex) == true )
    {
        absF = "Absolute";
        stringstream geek(first);
        valuF = 0;
        geek >> valuF;
        cF = true;
    }
    else
    {
        cF = checkLableSymbol(  symbolTable,  first, valuF,  absF);

    }
    if (regex_search(second, match2, staRegex) == true )
    {
        absS = "Absolute";
        stringstream geek(second);
        valuS = 0;
        geek >> valuS;
        cS= true;
    }
    else
    {
        cS = checkLableSymbol(  symbolTable,  second, valuS,  absS);
    }
    if (!cF && !cS)
    {
        stringstream ss;
        ss<<setfill('0') << setw(8)<<std::hex<<counter;
        start=ss.str();
        string error="****** there is not label";
        errorsM (counter, ss,code, lineNumber, start,line, check, error);

    }
    else
    {

        if ( checkAandR(absF, op,absS) )
        {
            stringstream ss;
            ss<<setfill('0') << setw(8)<<std::hex<<counter;
            if (wordture)
            {
                counter += operation (valuF, valuS, op) * 3 ;
            }
            else
            {
                counter += operation (valuF, valuS, op);
            }

            start=ss.str();
            string state ;
            string spacesLine = "" ;
            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
            {
                spacesLine+=" ";
            }
            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
            lineNumber++;
            code.push_back(state);
        }
        else
        {
            stringstream ss;
            ss << setfill('0') << setw(8)<<std::hex << counter;
            start=ss.str();
            string error="****** the expression is not relative or absolute";
            errorsM (counter, ss,code, lineNumber, start,line, check, error);

        }
    }

}
int CheckLast(string  Attribute, string last)
{

    if (Attribute == "m")
    {
        regex regex1("^(([_|'|#|@])?(\\s)*(([A-Z|0-9|*|+|/|\-]+)))(\\s)*[,](\\s)*([X])$");
        regex regex2("^([_|'|#|@])?(\\s)*([A-Z|0-9|*|+|/|\-]+)$");
        regex regex3("^[=](\\s)*[X|C](\\s)*[']([A-Z0-9])*[']$");
        smatch match;
        if (regex_search(last, match, regex1) == true)
        {
            regex regex11("^(([_|'|#|@])?(\\s)*(([X|A|T|B|F|S])))(\\s)*[,](\\s)*([X])$");
            if(regex_search(last, match, regex11) == true)
            {
                return 0;
            }
            return 1;
        }
        else if (regex_search(last, match, regex2) == true)
        {
            return 1;
        }
        else if (regex_search(last, match, regex3) == true)
        {
            return 1;
        }
        else if (last == "*")
        {
            return 1;
        }
        else if(last == "#*")
        {

            return 2;
        }

        return 0;


    }
    else if (Attribute == "r1,r2")
    {
        regex regex1("^([A|X|S|T|L|F])(\\s)*[,](\\s)*([A|X|S|T|L|F])$");
        smatch match;
        if (regex_search(last, match, regex1) == true)
        {
            return 1;
        }
        return 0;

    }
    else if (  Attribute ==  "r1")
    {
        regex regex1("^([A|X|S|T|L|F])$");
        smatch match;
        if (regex_search(last, match, regex1) == true)
        {
            return 1;
        }
        return 0;


    }
    else  if ( Attribute ==  "r1,n")
    {
        regex regex1 ("^([A|X|S|T|L|F])(\\s)*[,](\\s)*([0-9]+)$");
        smatch match;
        if (regex_search(last, match, regex1) == true)
        {
            return 1;
        }


    }
    else  if ( Attribute ==  "n")
    {

        regex regex1 ("^([0-9]+)$");
        smatch match;
        if (regex_search(last, match, regex1) == true)
        {
            return 1;
        }


        return 0;


    }
    else if (Attribute ==  "nil")
    {
        if (last=="")
        {
            return 1;
        }
        return 0;
    }

}
bool isThere(string label,vector <std::array<string,3>> table)
{
    for(int i=0 ; i<table.size(); i++)
    {
        std::array<string,3> element=table[i];
        if(element[0]==label)
        {
            return false;
        }
    }
    return true;
}
string returnCount (string label,vector <std::array<string,3>> table)
{
    for(int i=0 ; i<table.size(); i++)
    {
        std::array<string,3> element=table[i];
        if(element[0]==label)
        {
            return element[1];
        }
    }
    return "error";
}
vector<string> read(string filename)
{

    vector<string> lines;

    lines.clear();
    int n = filename.length();
    char char_array[n+1];
    strcpy(char_array, filename.c_str());
    ifstream file;
    file.open(char_array);
    if(file.is_open())
    {
        string s;
        while (getline(file, s))
        {
            lines.push_back(s);
        }
    }
    else
    {

        cout << "Error in file : check if the path contain spaces" ;
    }
    return lines;
}

int main()
{
    cout<<"enter file name:  ";
    string filename;
    string input;
    getline(cin, input);
    regex inputRegex("^([pass2]{5})\\s([A-Z|a-z|0-9|.]*)$");
    smatch matchInput;
    if (regex_search(input, matchInput, inputRegex) == true)
    {
        filename = matchInput.str(2);
    }
    else
    {
        cout<<"You entered wrong command"<<endl;
        system("pause");
        return 0;
    }
    Mnemonic mne;
    mne.fillMnemonics();
    vector <string> lines = read(filename);
    vector <string> code ;
    string start ("000");
    bool check=false;
    vector <std::array<string, 3>> symbolTable;
    int counter=0;
    int lineNumber = 1;

    for (int i =0 ; i < lines.size() ; i++)
    {
        string spacesLine;
        string line = lines[i] ;
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        regex regex_1("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*(BASE)(\\s)*(([*])|([A-Z0-9]+))(\\s)*$");
        regex regex0("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([EQU|ORG]{3})(\\s)*(([_|'|#|@|=])?(\\s)*(([A-Z|0-9|*|+|/|\-]+)))(\\s)*$"); // EQU ORG
        regex regex1("^(\\s)*([+])?([_|A-Z|0-9]+)(\\s)*$"); // RSUB not having label nor parameter
        regex regex2("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)+(([A-Z|0-9|#|@|'|*|+|/|\-]+)(\\s)*([,])(\\s)*([A-Z]+))(\\s)*$"); // ADDR r1,r2
        regex regex3("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)*([*])(\\s)*$"); //JUMP *
        regex regex4("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)*(([_|'|#|@])?(\\s)*(([A-Z|0-9|*|+|/|\-]+)))(\\s)*$"); // has all 3 parameter
        regex regex5("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)*(=?[X|C][']([A-Z0-9]+)['])(\\s)*$"); // can have X'' or C''
        regex regex6("^\\s*$");//spaces
        regex regex7("^[\\s]*\\..*");//comment
        smatch match;
        smatch match2;
        if(regex_search(line, match, regex_1) == true)
        {
            if(match.str(2)=="")
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                {
                    spacesLine+=" ";
                }
                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                start=ss.str();
                string error=" ****** this statement can not have a label  ";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }
        }
        else if(regex_search(line, match, regex0) == true)
        {
            if(match.str(5)=="ORG")
            {

                if(match.str(2)!="")
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string error=" ****** this statement can not have a label  ";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);

                }
                else
                {
                    regex regexOrg("^[A-Z]([A-Z|0-9])*?$");
                    regex expr("^([0-9|A-Z]+)([*|+|/|/|\-])([0-9|A-Z]+)$");
                    string orgOp=match.str(11);
                    smatch matcher;
                    if(regex_search(orgOp, matcher, regexOrg) == true)
                    {
                        if(isThere(orgOp,symbolTable))
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            start=ss.str();
                            string error=" ****** undefined symbol in operand ";
                            errorsM (counter, ss,code, lineNumber, start,line, check, error);
                        }
                        else
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            start=ss.str();
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                            {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                        }
                    }
                    else if (regex_search(orgOp, match2, expr) == true )
                    {
                        string first  = match2.str(1);
                        string op  = match2.str(2);
                        string second  = match2.str(3);
                        exeprssionForReserving(first,second, op, symbolTable, counter, code, lineNumber, start, line, check, false);
                    }
                }
            }
            else if (match.str(5)=="EQU")
            {
                regex regexEQ("^[A-Z]([A-Z|0-9])*?$");
                regex regexEQ2("^([0-9])*?$");
                regex expr("^([0-9|A-Z]+)([*|+|/|/|\-])([0-9|A-Z]+)$");
                string EqOp=match.str(11);
                smatch matcher;
                string label =match.str(2);
                if(match.str(2)=="")
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string error=" ****** this statement requires a label   ";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }

                else if(isThere(label,symbolTable))
                {
                    if(regex_search(EqOp, matcher, regexEQ) == true)
                    {
                        if(isThere(EqOp,symbolTable))
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            start=ss.str();
                            string error=" ****** undefined symbol in operand ";
                            errorsM (counter, ss,code, lineNumber, start,line, check, error);
                        }
                        else
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            string newCounter=returnCount(match.str(11),symbolTable);
                            temp[1]=newCounter;
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            start=ss.str();
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                            {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                        }
                    }
                    else if(regex_search(EqOp, matcher, regexEQ2) == true)
                    {
                        std::array<string,3> temp;
                        temp[0]=match.str(2);
                        temp[1]=match.str(11);
                        temp[2]="Absolute";
                        symbolTable.push_back(temp);
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }
                    else if (regex_search(EqOp, match2, expr) == true )
                    {
                        string first  = match2.str(1);
                        string op  = match2.str(2);
                        string second  = match2.str(3);
                        exeprssionForReserving(first,second, op, symbolTable, counter, code, lineNumber, start, line, check, false);
                    }

                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string error="****** duplicate label definition  ";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);

                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                start=ss.str();
                string error="****** unrecognized operation code";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);

            }
        }
        else if (regex_search(line, match, regex1) == true)
        {

            if(mne.isFound(match.str(3)))
            {
                if(CheckLast(mne.getAttribute(match.str(3)),match.str(4))==1)
                {

                    bool checkFormat=false;
                    bool for4=false;
                    if(match.str(2)=="+")
                    {

                        if(mne.getLength(match.str(3))!=3)
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            counter+=mne.getLength(match.str(3));
                            start=ss.str();
                            string error="****** can not be format 4 instruction";
                            errorsM (counter, ss,code, lineNumber, start,line, check, error);
                            checkFormat=true;
                        }
                        else
                        {
                            for4=true;
                        }
                    }
                    if(checkFormat==false)
                    {
                        if(start=="000")
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            ss>>std::hex>>counter;
                            counter+=mne.getLength(match.str(3));
                            start=ss.str();
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                            {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);


                        }
                        else
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            counter+=mne.getLength(match.str(3));
                            start=ss.str();
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                            {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                        }
                        if(for4==true)
                        {
                            counter++;
                        }
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=mne.getLength(match.str(3));
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else if (match.str(3)=="END")
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter-=1;
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                {
                    spacesLine+=" ";
                }
                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter+=mne.getLength(match.str(3));
                start=ss.str();
                string error="****** unrecognized operation code";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }
        }
        else if (regex_search(line, match, regex2) == true)
        {
            if(mne.isFound(match.str(5)))
            {
                if(CheckLast(mne.getAttribute(match.str(5)),match.str(7))==1)
                {
                    if (mne.isFound(match.str(2)))
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        start=ss.str();
                        string error=" ****** can't make a label with this word  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                    else if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        bool checkFormat=false;
                        bool for4=false;
                        if(match.str(4)=="+")
                        {

                            if(mne.getLength(match.str(5))!=3)
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                errorsM (counter, ss,code, lineNumber, start,line, check, error);
                            }
                            else
                            {
                                for4=true;
                            }
                        }
                        if(checkFormat==false)
                        {
                            if(start=="000")
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                ss>>std::hex>>counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);


                            }
                            else
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                            }
                            if(for4==true)
                            {
                                counter++;
                            }
                        }
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=mne.getLength(match.str(5));
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);

                    }
                }
                else
                {
                    cout << "Sddddddddddddddddd" ;
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=mne.getLength(match.str(5));
                    start=ss.str();
                    string error="****** unrecognized operation code";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);

                }

            }
        }
        else if (regex_search(line, match, regex3) == true)
        {
            if(mne.isFound(match.str(5)))
            {
                if(CheckLast(mne.getAttribute(match.str(5)),match.str(7))==1)
                {
                    if (mne.isFound(match.str(2)))
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        start=ss.str();
                        string error=" ****** can't make a label with this word  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                    else if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        bool checkFormat=false;
                        bool for4=false;
                        if(match.str(4)=="+")
                        {

                            if(mne.getLength(match.str(5))!=3)
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                errorsM (counter, ss,code, lineNumber, start,line, check, error);
                            }
                            else
                            {
                                for4=true;
                            }
                        }
                        if(checkFormat==false)
                        {
                            if(start=="000")
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                ss>>std::hex>>counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);


                            }
                            else
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                            }
                            if(for4==true)
                            {
                                counter++;
                            }
                        }
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=mne.getLength(match.str(5));
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=mne.getLength(match.str(5));
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                start=ss.str();
                string error="****** unrecognized operation code";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }

        }
        else if (regex_search(line, match, regex4) == true)
        {
            if (mne.isFound(match.str(2)))
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                start=ss.str();
                string error=" ****** can't make a label with this word  ";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }
            else if ( (match.str(2)!=""&&match.str(5)=="END")||match.str(7)=="END")
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                start=ss.str();
                string error=" ****** this statement can not have a label  ";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }
            else  if(match.str(5)=="START")
            {
                regex staRegex("^[0-8|A-F]{0,4}$");
                smatch match2;
                string last=match.str(7);
                if(regex_search(last, match2, staRegex) == true)
                {
                    if(start=="000")
                    {
                        stringstream ss;

                        ss<<setfill('0') << setw(8)<<std::hex<<match.str(7);
                        ss>>std::hex>>counter;
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);

                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<match.str(7);
                        ss>>std::hex>>counter;
                        string error="****** duplicate or misplaced START statement";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }

            }
            else if (match.str(5)=="END")
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter-=1;
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                {
                    spacesLine+=" ";
                }
                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
            }
            else if(mne.isFound(match.str(5)))
            {
                if(CheckLast(mne.getAttribute(match.str(5)),match.str(7))==1)
                {
                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        bool checkFormat=false;
                        bool for4=false;
                        if(match.str(4)=="+")
                        {

                            if(mne.getLength(match.str(5))!=3)
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                errorsM (counter, ss,code, lineNumber, start,line, check, error);
                            }
                            else
                            {
                                for4=true;
                            }
                        }
                        if(checkFormat==false)
                        {
                            if(start=="000")
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                ss>>std::hex>>counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                            }
                            else
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                            }
                            if(for4==true)
                            {
                                counter++;
                            }
                        }
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=mne.getLength(match.str(5));
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);

                    }
                }
                else if(match.str(5)=="LDB"&&CheckLast(mne.getAttribute(match.str(5)),match.str(7))==2)
                {
                    if (mne.isFound(match.str(2)))
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        start=ss.str();
                        string error=" ****** can't make a label with this word  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                    else if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        bool checkFormat=false;
                        bool for4=false;
                        if(match.str(4)=="+")
                        {

                            if(mne.getLength(match.str(5))!=3)
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                errorsM (counter, ss,code, lineNumber, start,line, check, error);
                            }
                            else
                            {
                                for4=true;
                            }
                        }
                        if(checkFormat==false)
                        {
                            if(start=="000")
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                ss>>std::hex>>counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);


                            }
                            else
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                            }
                            if(for4==true)
                            {
                                counter++;
                            }
                        }
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=mne.getLength(match.str(5));
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                }

                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=mne.getLength(match.str(5));
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else if(match.str(5)=="RESW")
            {
                regex staRegex("^[0-9]{0,4}$");
                regex expr("^([0-9|A-Z]+)([*|+|\|\-])([0-9|A-Z]+)$");
                smatch match2;
                string last=match.str(7);
                if(regex_search(last, match2, staRegex) == true )
                {
                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=3*std::stoi( match.str(7));
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=3*std::stoi( match.str(7));
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                }
                else if (regex_search(last, match2, expr) == true )
                {
                    string first  = match2.str(1);
                    string op  = match2.str(2);
                    string second  = match2.str(3);
                    exeprssionForReserving(first,second, op, symbolTable, counter, code, lineNumber, start, line, check, true);
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=3*std::stoi( match.str(7));
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else if(match.str(5)=="RESB")
            {
                // cout << "s  " ;
                regex staRegex("^[0-9]{0,4}$");
                regex expr("^([0-9|A-Z]+)([*|+|/|/|\-])([0-9|A-Z]+)$");
                smatch match2;
                string last=match.str(7);
                if(regex_search(last, match2, staRegex) == true )
                {
                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=std::stoi( match.str(7));
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }

                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=std::stoi( match.str(7));
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                }
                else if (regex_search(last, match2, expr) == true )
                {
                    string first  = match2.str(1);
                    string op  = match2.str(2);
                    string second  = match2.str(3);
                    exeprssionForReserving(first,second, op, symbolTable, counter, code, lineNumber, start, line, check, false);
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=std::stoi( match.str(7));
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else if(match.str(5)=="WORD")
            {
                regex staRegex("^[0-9]{0,4}$");
                smatch match2;
                string last=match.str(7);
                if(regex_search(last, match2, staRegex) == true)

                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=3;
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=3;
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);

                    }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=3;
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else if(match.str(5)=="BYTE")
            {
                regex staRegex("^[0-9]{0,4}$");
                smatch match2;
                string last=match.str(7);
                if(regex_search(last, match2, staRegex) == true)
                {
                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=1;
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=1;
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=1;
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter+=mne.getLength(match.str(5));
                start=ss.str();
                string error="****** unrecognized operation code";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }
        }
        else if (regex_search(line, match, regex5) == true)
        {
            if (mne.isFound(match.str(2)))
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                start=ss.str();
                string error=" ****** can't make a label with this word  ";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }
            else if(mne.isFound(match.str(5)))
            {
                if(CheckLast(mne.getAttribute(match.str(5)),match.str(7))==1)
                {

                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        bool checkFormat=false;
                        bool for4=false;
                        if(match.str(4)=="+")
                        {
                            if(mne.getLength(match.str(5))!=3)
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                errorsM (counter, ss,code, lineNumber, start,line, check, error);
                            }
                            else
                            {
                                for4=true;
                            }
                        }
                        if(checkFormat==false)
                        {
                            if(start=="000")
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                ss>>std::hex>>counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);

                            }
                            else
                            {
                                stringstream ss;
                                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                                counter+=mne.getLength(match.str(5));
                                start=ss.str();
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                                {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                            }
                            if(for4==true)
                            {
                                counter++;
                            }
                        }
                        else
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            counter+=mne.getLength(match.str(5));
                            start=ss.str();
                            string error="****** illegal operand";
                            errorsM (counter, ss,code, lineNumber, start,line, check, error);
                        }
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=mne.getLength(match.str(5));
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }
                }
            }
            else if(match.str(5)=="WORD")
            {
                regex staRegex("^[0-9]{0,4}$");
                smatch match2;
                string last=match.str(7);
                if(regex_search(last, match2, staRegex) == true)
                {
                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=3;
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=3;
                        start=ss.str();
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }

                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=3;
                    start=ss.str();
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else if(match.str(5)=="BYTE")
            {
                regex staRegex("=?([X|C])[']([A-Z0-9]+)[']");
                smatch match2;
                string last=match.str(7);
                if(regex_search(last, match2, staRegex) == true)
                {
                    if(isThere(match.str(2),symbolTable))
                    {
                        if(match.str(2)!="")
                        {
                            std::array<string,3> temp;
                            temp[0]=match.str(2);
                            temp[1]=std::to_string(counter);
                            temp[2]="Relocatable";
                            symbolTable.push_back(temp);
                        }
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        if(match2.str(1)=="C")
                        {
                            string str=match2.str(2);
                            counter+=str.length();
                        }
                        else
                        {
                            counter+=1;
                        }
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
                        {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        if(match2.str(1)=="C")
                        {
                            string str=match2.str(2);
                            counter+=str.length();
                        }
                        else
                        {
                            counter+=1;
                        }
                        string error="****** duplicate label definition  ";
                        errorsM (counter, ss,code, lineNumber, start,line, check, error);
                    }

                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    if(match2.str(1)=="C")
                    {
                        string str=match2.str(2);
                        counter+=str.length();
                    }
                    else
                    {
                        counter+=1;
                    }
                    string error="****** illegal operand";
                    errorsM (counter, ss,code, lineNumber, start,line, check, error);
                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter+=mne.getLength(match.str(5));
                start=ss.str();
                string error="****** unrecognized operation code";
                errorsM (counter, ss,code, lineNumber, start,line, check, error);
            }
        }
        else if (regex_search(line, match, regex6) == true)
        {

        }
        else if (regex_search(line, match, regex7) == true)
        {
            string state ;
            stringstream ss;
            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++)
            {
                spacesLine+=" ";
            }
            ss<<setfill('0') << setw(8)<<std::hex<<counter;
            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
            lineNumber++;
            code.push_back(state);
        }
        else
        {
            stringstream ss;
            ss<<setfill('0') << setw(8)<<std::hex<<counter;
            start=ss.str();

            string error="****** unrecognized operation code";

            errorsM (counter, ss,code, lineNumber, start,line, check, error);

        }
    }
    ofstream myfile;
    myfile.open ("Output.txt");
    cout << "line no.     Address  Label    Mnem.   Operands    Comments"<<endl;
    myfile << "line no.     Address  Label    Mnem.   Operands    Comments" << "\n";
    for (int i=0 ; i<code.size(); i++)
    {
        cout<<code[i]<<endl;
        myfile << code[i] + "\n";
    }
    if(check==false)
    {
        cout << "   e n d     p h a s e  1 "<<endl;
        myfile <<  "     e n d     p h a s e  1 \n";
        cout << "   s y m b o l     t a b l e   (values in decimal) "<<endl;
        myfile <<  "  s y m b o l     t a b l e   (values in decimal) \n";
        for (int i=0 ; i<symbolTable.size(); i++)
        {
            std::array<string,3> temp=symbolTable[i];
            cout<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<endl;
            myfile << temp[0]<<" "<<temp[1]<<" "<<temp[2]+".\n";
        }
    }
    else
    {
        cout << "   i n c o m p l e t e    a s s e m b l y"<<endl;
        myfile <<  "   i n c o m p l e t e    a s s e m b l y \n";

    }
    myfile.close();
    cout<<endl<<endl;
    cout<<"   E N D   o f   P A S S  1"<<endl;
    cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl<<endl;
    cout<<"   S T A R T   o f   P A S S  2"<<endl;
    cout<<endl;
    vector<string> opCodes;
    vector<string> errorMes;
    Object_Code oc;
    oc.setSymbolTable(symbolTable);
    errorMes = oc.getErrorMes();

    // fiiling all op codes and writing file output_opcode.txt
    ofstream myfile2;
    myfile2.open ("Output_OPCODE.txt");
    for (int i = 0; i < code.size(); i++) {
        string res;
        if (i != code.size() - 1) {
            res = oc.evaluateLine(code[i], code[i+1]);
            opCodes.push_back(res);
        } else {
            res = oc.evaluateLine(code[i], "");
            opCodes.push_back(res);
        }
    }

    cout<<endl<<endl;
    myfile2<<"line no.     Address  Label    Mnem.   Operands    Comments          OpCODE"<<endl;
    cout<<"line no.     Address  Label    Mnem.   Operands    Comments          OpCODE"<<endl;
    for (int i = 0; i < opCodes.size(); i++) {
        string res = opCodes[i];
        if (find(errorMes.begin(), errorMes.end(), res) != errorMes.end()) {
            string spaces = "";
            vector<string> tempresults = oc.split(code[i]);
            for (int vb = 0; vb < 30 - tempresults[tempresults.size() - 1].length(); vb++) {
                spaces+=" ";
            }
            myfile2<<code[i]<<spaces<<"\n";
            cout<<code[i]<<spaces<<endl;
            myfile2<<"\t"<<res<<endl;
            cout<<"\t"<<res<<endl;
            continue;
        }
        if (res != "") {
            string spaces = "";
            vector<string> tempresults = oc.split(code[i]);
            for (int vb = 0; vb < 30 - tempresults[tempresults.size() - 1].length(); vb++) {
                spaces+=" ";
            }
            myfile2<<code[i]<<spaces<<res<<"\n";
            cout<<code[i]<<spaces<<res<<endl;
        } else {
            myfile2<<code[i]<<"\n";
            cout<<code[i]<<endl;
        }
    }
    myfile2.close();

    /* ********* OBJECT FILE *********** */

    cout<<" "<<endl;
    cout<<" "<<endl;

    vector<string> objectFile;
    vector<string> addresses;
    vector<string> temp1;
    vector<string> temp2;
    string line;
    ofstream myfile3;
    int startingIndex;
    myfile3.open ("Object_File.txt");
    myfile3<<"Object File...."<<endl;
    cout<<"Object File...."<<endl;

            /* ******** HEADER ********** */
    for (int i = 0; i < code.size(); i++) {
        line = "";
        temp1 = oc.split(code[i]);
        temp2 = oc.split(code[code.size() - 2]);

        std::size_t found = code[i].find("START");
        if (found!=std::string::npos){
            startingIndex = i;
            line = "H";
            string address0 = temp1[0]; //line Number
            string address1 = temp1[1]; //Address
            string address2 = temp1[2]; //Label
            string address3 = temp1[3]; //Mnemonics

            string StartingAddress = temp1[1]; //Address
            string EndingAddress = temp2[1]; //Address

            addresses.push_back(address1);

            char xChar[StartingAddress.length() + 1];
            strcpy(xChar, StartingAddress.c_str());
            char yChar[EndingAddress.length() + 1];
            strcpy(yChar, EndingAddress.c_str());
            int firstNumber = hexadecimalToDecimal(xChar);
            int secondNumber = hexadecimalToDecimal(yChar);
            int answerDecimal = operation(secondNumber, firstNumber, "-");
            string answerHexaDecimal = decimalToHexadecimal(answerDecimal);
            if (firstNumber == 0){
                answerDecimal = operation(answerDecimal, 2, "+");
                answerHexaDecimal = "";
                answerHexaDecimal = decimalToHexadecimal(answerDecimal);
            }
            string programName = temp1[2];
            int programNameLength = programName.length();
            line += programName;
            for (int j = 0; j < 6 - programNameLength; j++){
                line+=" ";
            }
            line+="^";
            string start ="";
            string programLength ="";
            for (int j = 2; j < 8; j++){
                start += StartingAddress[j];
            }
            line += start;
            line += "^";
            for (int j = 2; j < 8; j++){
                programLength += answerHexaDecimal[j];
            }
            line += programLength;
            myfile3<<line<<endl;
            cout<<line<<endl;
            break;
        }
    }


        /* ******** TEXT ********** */
    line = "";
    string startingAddressDefault = temp1[1];
    string startingAddress = temp1[1];
    string tempAddress = "";
    string displacement = "1D";
    string one = "1";
    int tempIndex = 0;
    int displacmentIndex;
    int counteer = 0;

    for (int f = 1; f < code.size(); f++){
        vector<string> teemp = oc.split(code[f]);
        if (teemp[1] == startingAddress){
            startingIndex = f;
        }
    }

    for (int h = startingIndex; h < code.size(); h++){
        if (h+1 >= code.size()){
            break;
        }
        vector<string> temp = oc.split(code[h]);
        vector<string> temp1 = oc.split(code[h+1]);
        int flag = 0;
        if (temp[3] == "RESB" || temp[3] == "RESW"){ //CASE1
            startingAddress = temp1[1];
            displacement = "1D";
        }
        else if (temp1[3] == "RESB" || temp1[3] == "RESW"){ //CASE2
            if (opCodes[h+1] == ""){
                h++;
            } else {
                line = "T";
                line += temp1[1];
                line += "01";
                line += opCodes[h+1];
                h++;
            }
            vector<string> temp3 = oc.split(code[h+1]);
            startingAddress = temp3[1];
            displacement = "1D";
        }
        else { //CASE3

            for (int f = 0; f < 30; f++){
                char xChar[startingAddress.length() + 1];
                strcpy(xChar, startingAddress.c_str());
                char yChar[displacement.length() + 1];
                strcpy(yChar, displacement.c_str());
                int firstNumber = hexadecimalToDecimal(xChar);
                int secondNumber = hexadecimalToDecimal(yChar);
                int answerDecimal = operation(secondNumber, firstNumber, "+");
                string answerAddress = decimalToHexadecimal(answerDecimal); //ADDED

                counteer = 0;
                for (int u = h + 1; u < code.size(); u++){
                    vector<string> temp2 = oc.split(code[u]);
                    string currentAddress = temp2[1];
                    if (answerAddress == currentAddress){
                        flag = 1;
                        vector<string> temp3 = oc.split(code[u]);
                        tempAddress = temp3[1];
                        displacmentIndex = u;
                        tempIndex = u+1;
                        break;
                    } else {
                        counteer++;
                    }
                }
                if (!flag){
                    char xChar[displacement.length() + 1];
                    strcpy(xChar, displacement.c_str());
                    char yChar[one.length() + 1];
                    strcpy(yChar, one.c_str());
                    int firstNumber = hexadecimalToDecimal(xChar);
                    int secondNumber = hexadecimalToDecimal(yChar);
                    int answerDecimal = operation(firstNumber, secondNumber, "-");
                    displacement = decimalToHexadecimal(answerDecimal);

                }
                if (flag){
                    break;
                }
            }

            if (flag){
                line = "T";
                string startAddress = "";
                for (int j = 2; j < 8; j++){
                    startAddress += startingAddress[j];
                }
                line += startAddress;
                line += "^";
                string disp = "";
                if (displacement.length() > 2){
                    for (int j = 6; j < 8; j++){
                        disp += displacement[j];
                    }
                    line += disp;
                } else {
                    line += displacement;
                }

                line += "^";

                for (int k = startingIndex; k < displacmentIndex; k++){
                    line+= opCodes[k];
                }

                h = displacmentIndex - 1;
                startingAddress = tempAddress;
                startingIndex = tempIndex;
                myfile3<<line<<endl;
                cout<<line<<endl;
                displacement = "1D";

            } else {
                h = displacmentIndex - 1;
                startingAddress = tempAddress;
                startingIndex = tempIndex;
                displacement = "1D";
            }
        }

    }


            /* ******** END ********** */
    line = "";
    string startAddress="";
    for (int j = 2; j < 8; j++){
        startAddress += startingAddressDefault[j];
    }
    line = "E";
    line += startAddress;
    myfile3<<line<<endl;
    cout<<line<<endl;



    myfile3.close();



    system("pause");
    return 0;
}

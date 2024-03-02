#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include "Mnemonic.h"

using namespace std;
int CheckLast(string  Attribute, string last)
{

    if (Attribute == "m")
    {
        regex regex1("^(([_|'|#|@])?(\\s)*(([A-Z0-9]+)))(\\s)*[,](\\s)*([X])$");
        regex regex2("^([_|'|#|@])?(\\s)*([A-Z|0-9]+)$");
        regex regex3("^[=](\\s)*[X|C](\\s)*[']([A-Z0-9])*[']$");
        smatch match;
        if (regex_search(last, match, regex1) == true)
        {
            return 1;
        }
        else if (regex_search(last, match, regex2) == true)
        {
            return 1;
        }
        else if (regex_search(last, match, regex2) == true)
        {
            return 1;
        }
        else if (last == "*")
        {
            return 1;
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
    string filename ;
    cin>>filename;
    Mnemonic mne;
    mne.fillMnemonics();
    vector <string> lines = read(filename);
    vector <string> code ;
    string start ("000");
    bool check=false;
    vector <std::array<string, 3>> symbolTable;
    int counter=0;
    int lineNumber = 1;

    //cout<<lines.size()<<endl;
    for (int i =0 ; i < lines.size() ; i++)
    {
        string spacesLine;
        string line = lines[i] ;
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        regex regex0("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([EQU|ORG]{3})(\\s)*(([_|'|#|@|=])?(\\s)*(([A-Z|0-9]+)))(\\s)*$"); // EQU ORG
        regex regex1("^(\\s)*([+])?([_|A-Z|0-9]+)(\\s)*$"); // RSUB not having label nor parameter
        regex regex2("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)+(([A-Z|#|@|']+)(\\s)*([,])(\\s)*([A-Z]+))(\\s)*$"); // ADDR r1,r2
        regex regex3("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)*([*])(\\s)*$"); //JUMP *
        regex regex4("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)*(([_|'|#|@])?(\\s)*(([A-Z|0-9]+)))(\\s)*$"); // has all 3 parameter
        regex regex5("^(\\s)*([_|A-Z|0-9]+)*?(\\s)*([+])?([_|A-Z]+)(\\s)*(=?[X|C][']([A-Z0-9]+)['])(\\s)*$"); // can have X'' or C''
        regex regex6("^\\s*$");//spaces
        regex regex7("^[\\s]*\\..*");//comment
        smatch match;
        if(regex_search(line, match, regex0) == true)
        {
            if(match.str(5)=="ORG")
            {
                if(match.str(2)!="")
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error=" ****** this statement can not have a label  ";
                    code.push_back(error);
                }
                else
                {
                    regex regexOrg("^[A-Z]([A-Z|0-9])*?$");
                    string orgOp=match.str(11);
                    smatch matcher;
                    if(regex_search(orgOp, matcher, regexOrg) == true)
                    {
                        if(isThere(orgOp,symbolTable))
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            start=ss.str();
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                            check=true;
                            string error=" ****** undefined symbol in operand ";
                            code.push_back(error);
                        }
                        else
                        {
                            stringstream ss;
                            ss<<setfill('0') << setw(8)<<std::hex<<counter;
                            start=ss.str();
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                        }
                    }
                }
            }
            else if (match.str(5)=="EQU")
            {
                regex regexEQ("^[A-Z]([A-Z|0-9])*?$");
                regex regexEQ2("^([0-9])*?$");
                string EqOp=match.str(11);
                smatch matcher;
                string label =match.str(2);
                if(match.str(2)=="")
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error=" ****** this statement requires a label   ";
                    code.push_back(error);
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
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                            check=true;
                            string error=" ****** undefined symbol in operand ";
                            code.push_back(error);
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
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error=" ****** duplicate label definition   ";
                    code.push_back(error);
                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                //counter+=mne.getLength(match.str(4));
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                    spacesLine+=" ";
                }
                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
                check=true;
                string error="****** unrecognized operation code";
                code.push_back(error);
            }
        }
        else if (regex_search(line, match, regex1) == true)
        {
            /*cout<<match.str(2)<<endl;
            cout<<1<<endl;*/
            //cout<<mne.getOpCode(match.str(4))<<endl;
            if(mne.isFound(match.str(3)))
            {
                if(CheckLast(mne.getAttribute(match.str(3)),match.str(4))==1)
                {
                    /* if(match.str(2)!="")
                     {
                         symbolTable.push_back(make_pair(match.str(2),counter));
                     }*/
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
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                            check=true;
                            checkFormat=true;
                            string error="****** can not be format 4 instruction";
                            code.push_back(error);
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
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
                }
            }
            else if (match.str(3)=="END")
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter-=1;
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                    spacesLine+=" ";
                }
                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
                check=true;
                string error="****** unrecognized operation code";
                code.push_back(error);

            }
        }
        else if (regex_search(line, match, regex2) == true)
        {
            //cout<<mne.getOpCode(match.str(4))<<endl;
            if(mne.isFound(match.str(5)))
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
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                                check=true;
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                code.push_back(error);
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=mne.getLength(match.str(5));
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** unrecognized operation code";
                    code.push_back(error);

                }

            }
        }
        else if (regex_search(line, match, regex3) == true)
        {
            //cout<<mne.getOpCode(match.str(4))<<endl;
            if(mne.isFound(match.str(5)))
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
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                                check=true;
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                code.push_back(error);
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error=" ****** duplicate label definition   ";
                        code.push_back(error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=mne.getLength(match.str(5));
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                //counter+=mne.getLength(match.str(4));
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                    spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
                check=true;
                string error="****** unrecognized operation code";
                code.push_back(error);

            }

        }
        else if (regex_search(line, match, regex4) == true)
        {
            // cout<<mne.getOpCode(match.str(4))<<endl;

            if(match.str(5)=="START")
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
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate or misplaced START statement";
                        code.push_back(error);



                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
                }

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
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                                check=true;
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                code.push_back(error);
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=mne.getLength(match.str(5));
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
                }
            }
            else if(match.str(5)=="RESW")
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
                        counter+=3*std::stoi( match.str(7));
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=3*std::stoi( match.str(7));
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
                }
            }
            else if(match.str(5)=="RESB")
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
                        counter+=std::stoi( match.str(7));
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
                    }
                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=std::stoi( match.str(7));
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
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
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
                    }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=3;
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
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
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
                    }

                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=1;
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter+=mne.getLength(match.str(5));
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                    spacesLine+=" ";
                }
                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
                check =true;
                string error="****** unrecognized operation code";
                code.push_back(error);

            }
        }
        else if (regex_search(line, match, regex5) == true)
        {
            //cout<<mne.getOpCode(match.str(4))<<endl;
            if(mne.isFound(match.str(5)))
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
                                string state ;
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                    spacesLine+=" ";
                                }
                                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                                lineNumber++;
                                code.push_back(state);
                                check=true;
                                checkFormat=true;
                                string error="****** can not be format 4 instruction";
                                code.push_back(error);
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                            string state ;
                            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                                spacesLine+=" ";
                            }
                            state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                            lineNumber++;
                            code.push_back(state);
                            check=true;
                            string error="****** illegal operand";
                            code.push_back(error);
                        }
                    }
                    else
                    {
                        stringstream ss;
                        ss<<setfill('0') << setw(8)<<std::hex<<counter;
                        counter+=mne.getLength(match.str(5));
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
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
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                            spacesLine+=" ";
                        }
                        state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
                    }

                }
                else
                {
                    stringstream ss;
                    ss<<setfill('0') << setw(8)<<std::hex<<counter;
                    counter+=3;
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
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
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
                        start=ss.str();
                        string state ;
                        for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                        lineNumber++;
                        code.push_back(state);
                        check=true;
                        string error="****** duplicate label definition  ";
                        code.push_back(error);
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
                    start=ss.str();
                    string state ;
                    for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                        spacesLine+=" ";
                    }
                    state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                    lineNumber++;
                    code.push_back(state);
                    check=true;
                    string error="****** illegal operand";
                    code.push_back(error);
                }
            }
            else
            {
                stringstream ss;
                ss<<setfill('0') << setw(8)<<std::hex<<counter;
                counter+=mne.getLength(match.str(5));
                start=ss.str();
                string state ;
                for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
                    spacesLine+=" ";
                }
                state =to_string(lineNumber)+spacesLine+ss.str()+" "+line;
                lineNumber++;
                code.push_back(state);
                check=true;
                string error="****** unrecognized operation code";
                code.push_back(error);

            }
        }
        else if (regex_search(line, match, regex6) == true)
        {

        }
        else if (regex_search(line, match, regex7) == true)
        {
            string state ;
            stringstream ss;
            for (int vb = 0; vb < 13 - (to_string(lineNumber)).length(); vb++) {
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
            //counter+=mne.getLength(match.str(4));
            start=ss.str();
            check=true;
            string error="****** unrecognized operation code";
            //string error="****** illegal operand";
            code.push_back(error);

        }


    }
    ofstream myfile;
    myfile.open ("Output.txt");
    cout << "line no.     Address  Label    Mnem.   Operands Comments"<<endl;
    myfile << "line no.     Address  Label    Mnem.   Operands Comments" << "\n";
    for (int i=0 ; i<code.size(); i++)
    {
        cout<<code[i]<<endl;
        myfile << code[i] + "\n";
    }
    if(check==false)
    {
        cout << "   e n d     p h a s e 1 "<<endl;
        myfile <<  "     e n d     p h a s e 1 \n";
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
    return 0;
}




#include "Mnemonic.h"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>

using namespace std;

Mnemonic::Mnemonic()
{
    //ctor
}

//
// Created by ziadh on 4/21/2019.
//
map<string, pair<string, int> > mnemonics;
map<string, string> attr;


/*
* fills the mnemonics map from the mnemonics.txt file.
*/
void Mnemonic :: fillMnemonics() {
    ifstream file;
    file.open("mnemonics.txt");
    if (file.is_open()) {
        int i = 0;
        string name;
        string first;
        int second;
        string attribute;
        while(!file.eof()) {
            string temp;
            istringstream iss;
            file >> temp;
            if (i == 0) {
                name = temp;
                i++;
            } else if (i == 1) {
                attribute = temp;
                i++;
            } else if (i == 2) {
                istringstream iss2(temp);
                iss2 >> second;
                i++;
            } else if (i == 3) {
                first = temp;
                pair<string, int> p;
                p.first = first;
                p.second = second;
                mnemonics[name] = p;
                attr[name] = attribute;
                /*cout << "name: " << name << endl;
                cout << "attribute: " << attr[name] << endl;
                cout << "first: " << mnemonics[name].first << endl;
                cout << "second: " << mnemonics[name].second << endl;
                cout << endl;*/
                i = 0;
            }
            /*cout << "string: " << temp << endl;
            cout << endl;*/
        }
    }
}

/*
* returns the opCode of the specific m mnemonic.
*/
string Mnemonic :: getOpCode(string m) {
    return mnemonics[m].first;
}

/*
* returns the length of the specific m mnemonic.
*/
int Mnemonic :: getLength(string m) {
    return mnemonics[m].second;
}

/*
* returns the attribute of the specific m mnemonic.
*/
string Mnemonic :: getAttribute(string m) {
    return attr[m];
}
/*
*if key is found
*/
bool Mnemonic :: isFound(string m)
{
    return !(mnemonics.find(m)==mnemonics.end());
}

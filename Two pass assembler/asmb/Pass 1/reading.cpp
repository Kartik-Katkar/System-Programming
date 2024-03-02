#include <fstream>
#include<string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

reading::reading()
{\
    //ctor
}
void reading::readFile(const string filename, vector<string>& lines)
{
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
            lines.push_back(s);

    }
    else
    {

        cout << "Error in file : check if the path contain spaces" ;
    }

}
/*vector<string>::reading read(string filename){

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
        while (getline(file, s)){
            lines.push_back(s);
        }
    }
    else
    {

        cout << "Error in file : check if the path contain spaces" ;
    }
    return lines;
}*/

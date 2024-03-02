#ifndef OBJECT_CODE_H
#define OBJECT_CODE_H

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <set>

using namespace std;

class Object_Code
{
    public:
        Object_Code();
        void setSymbolTable(std::vector <std::array<string, 3>> s);
        string evaluateLine(string line, string nextline);
        string calcDisplacement(string address, string nextaddress, string attribute, bool isPlus);
        std::vector<std::string> split(string line);
        std::vector<std::string> getErrorMes();
        std::string getRegisterNum(string registerN);
        int operation (int a, int b, string operatoor);
        bool checkAandR (string exprssion1, string operation, string exprssion2);
        bool checkIfExp(string attribute);
        virtual ~Object_Code();

    protected:

    private:
        std::set<std::string> fillExceptionsIndex();
};

#endif // OBJECT_CODE_H

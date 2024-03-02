#ifndef MNEMONIC_H
#define MNEMONIC_H


#include <string>

using namespace std;

class Mnemonic {
    public:
        Mnemonic();
        void fillMnemonics();
        string getOpCode(string m);
        int getLength(string m);
        string getAttribute(string m);
        bool isFound(string m);
};

#endif // MNEMONIC_H

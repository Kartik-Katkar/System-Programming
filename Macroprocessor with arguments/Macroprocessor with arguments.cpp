#include <bits/stdc++.h>
using namespace std;

struct MNT{ // Macro Name Table
    int index;
    string name;
    int mntIndex;
};

struct MDT{ // Macro Definition Table
    int mdtindex;
    string arg;
    string card;
};

struct ALA{ // Argument List Array
    string macroName;
    string formalp;
    string positnp;
};
struct AVP{ // Actual VS Positional 
    string macroName;
    string actual;
    string posarg;
};

struct MNT mnt[100];
struct MDT mdt[100];
struct ALA ala[100];
struct AVP avp[100];

void insertMDT(string macroName,int MNT_index,int MDT_index){
    mnt[MNT_index].index = MNT_index;
    mnt[MNT_index].name = macroName;
    mnt[MNT_index].mntIndex = MDT_index;
}

void insertMNT(string _card,string _arg,int MDT_index){
    mdt[MDT_index].card = _card;
    mdt[MDT_index].mdtindex = MDT_index;
    mdt[MDT_index].arg = _arg;
}

void insertALA(string macroName,string formalp,string positnp,int index){
    ala[index].macroName = macroName;
    ala[index].formalp = formalp;
    ala[index].positnp = positnp;
}

void insertAVP(string macroName,string actual,string posarg,int index){
    avp[index].macroName = macroName;
    avp[index].actual = actual;
    avp[index].posarg = posarg;
}

int main(){
    ifstream file;
    string filename, line;
    filename = "input.txt";
    vector<string> expandedcode;
    map<string,int> mdtMap;
    map<string,string> alaMap;
    map<string,string> avpMap;
    vector<vector<string>> avpTab;
    file.open(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    int MDT_index = 21; 
    int MNT_index = 1;
    while (getline(file, line)){
        if(line.empty()) continue;
        if (line.compare(0, 5, "macro") == 0) {
            stringstream ss(line);
            string token;
            vector<string> components;
            while (getline(ss, token, ' ')) {
                components.push_back(token);
            }
            // ALA Table Initialization
            string macroName = components[1];
            insertMDT(components[1],MNT_index++,MDT_index);
            mdtMap[macroName] = MDT_index;
            int index = alaMap.size();
            int pos = 0;
            for(int i=2;i<components.size();i++) {
                string formarg;
                if(components[i][components[i].length()-1]==','){
                    formarg = components[i].substr(0,components[i].length()-1);
                } 
                else{
                    formarg= components[i];
                }
                string posarg = "#" + to_string(pos);
                insertALA(macroName,formarg,posarg,index);
                string key = macroName + "|" +formarg;
                alaMap[key] = posarg;
                string avpKey = macroName + "|" +posarg;
                avpMap[avpKey] = formarg;
                index++;
                pos++;
            }
            // MDT Table
            int formal = 0;index = 0;
            while(getline(file,line)){
                if(line.compare(0,4,"mend")==0){
                    insertMNT("mend"," ",MDT_index++);
                    break;
                }else{
                    stringstream ss(line);
                    string token;
                    vector<string> components;
                    while (getline(ss, token, ' ')) {
                        components.push_back(token);
                    }
                    string key = macroName + "|" +components[1]; // components[1] is FormalArgument
                    // string opcode = (alaMap.find(key)!=alaMap.end())?alaMap[key]:components[1];
                    string opcode ;
                    if(alaMap.find(key)!=alaMap.end()){
                        opcode = alaMap[key];
                    }else{
                        opcode = components[1];
                        // avpMap[posKey] = components[1];
                        // cout<<components[0]<<" hero "<<components[1]<<endl;
                    }
                    insertMNT(components[0],opcode,MDT_index++);
                }
                index++;formal++;
            }
        }
        // Expanded Code
        else{
            if(line.compare(0,5,".code")==0){
                while(getline(file,line)){
                    stringstream ss(line);
                    string token;
                    vector<string> components;
                    while (getline(ss, token, ' ')) {
                        components.push_back(token);
                    }
                    if(line.compare(0,4,"endp")==0){
                        expandedcode.push_back("endp");
                    }else{
                        string card = components[0];
                        int ind = mdtMap[card];
                        int index = 1;
                        for(int i=ind;mdt[i].card!="mend";i++){
                            string key = card + "|" + mdt[i].arg;
                            if(avpMap.find(key)==avpMap.end()) expandedcode.push_back(mdt[i].card+" "+mdt[i].arg);
                            else{
                                string argVal = components[index++];
                                if(argVal[argVal.size()-1]==','){
                                    expandedcode.push_back(mdt[i].card+" "+argVal.substr(0,argVal.size()-1));
                                    // insertAVP(card,argVal.substr(0,argVal.size()-1),mdt[i].arg,avpind++);
                                    avpTab.push_back({card,argVal.substr(0,argVal.size()-1),mdt[i].arg});
                                }
                                else{
                                    expandedcode.push_back(mdt[i].card+" "+argVal);
                                    // insertAVP(card,argVal.substr(0,argVal.size()-1),mdt[i].arg,avpind++);
                                    avpTab.push_back({card,argVal,mdt[i].arg});
                                } 
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<"Index"<<"\t"<<"Name"<<"\t"<<"MDT Index"<<endl;
    for(int i=1;i<MNT_index;i++){
        cout<<mnt[i].index<<"\t"<<mnt[i].name<<"\t"<<mnt[i].mntIndex<<endl;
    }cout<<endl;
    cout<<"Index"<<"\t"<<"Card"<<endl;
    for(int i=21;i<MDT_index;i++){
        cout<<mdt[i].mdtindex<<"\t"<<mdt[i].card+" "+mdt[i].arg<<endl;
    }cout<<endl;
    cout<<"Name"<<"\t"<<"formal"<<"\t"<<"positional"<<endl;
    for(int i=0;i<alaMap.size();i++){
        cout<<ala[i].macroName<<"\t"<<ala[i].formalp<<"\t"<<ala[i].positnp<<endl;
    }cout<<endl;
    cout<<"Expanded Code: "<<endl;
    for(int i=0;i<expandedcode.size();i++){
        cout<<expandedcode[i]<<endl;
    }cout<<endl;
    cout<<"Name"<<"\t"<<"Actual"<<"\t"<<"positional"<<endl;
    for(auto it:avpTab){
        cout<<it[0]<<"\t"<<it[1]<<"\t"<<it[2]<<endl;
    }cout<<endl;
}
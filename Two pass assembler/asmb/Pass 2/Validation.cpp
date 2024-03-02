using namespace std;
Validation::Validation()
{
    //ctor
}

void Validation :: removeSpaces(string &line){

    int n = line.length();
    int first = 0;
    int last = n - 1;

    for (int k = 0; k < n; k++){
        if (line[k] != ' '){
            first = k;
            cout << "First: " << first << endl;
            break;
        }
    }

    if (line[n - 1] == ' '){
        for (int k = n - 1; k >=0 ; k--){
            if (line[k] != ' '){
                last = k;
                cout << "Last: " << last << endl;
                break;
            }
        }
    }


    for(int i = last; i >= first; i-- ){
        if(line[i] == ' ' && line[i] == line[i-1]){ //added equal sign
            line.erase( line.begin() + i );
        }
    }
}

void Validation :: parsing (string &line){
    //printf("%p",line);
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    cout<<line;
    regex regex1("^(\\s)*([_|a-z|]+)*?(\\s)*([_|a-z]+)(\\s)*(([a x s t l])(\\s)*[,](\\s)*([a x s t l]))?(\\s)*$"); // ADDR r1,r2
    regex regex2("^(\\s)*([_|a-z|]+)*?(\\s)*([_|a-z]+)(\\s)*((([_|'|#|@])?(\\s)*(([a-z0-9]+)))[,](\\s)*([x]))(\\s)*$"); // LDA #300
    regex regex3("^(\\s)*([_|a-z|]+)*?(\\s)*([_|a-z]+)(\\s)*([*])(\\s)*$"); //JUMP *
    regex regex4("^(\\s)*([_|a-z|]+)*?(\\s)*([_|a-z]+)(\\s)*(([_|'|#|@])?(\\s)*(([a-z|0-9]+)))(\\s)*$");






    smatch match;

    if (regex_search(line, match, regex1) == true)
    {
        cout << "Match size = " << match.size() << endl;
        cout << "Whole match : " << match.str(0) << endl;
        cout << "First capturing group is '" << match.str(2)
             << "' which is captured at index " << match.position(2)
             << endl;
        cout << "Second capturing group is '" << match.str(4)
             << "' which is captured at index " << match.position(4)
             << endl;
        cout << "Third capturing group is '" << match.str(6)
             << "' which is captured at index " << match.position(6)
             << endl;
    }
    else if (regex_search(line, match, regex2) == true)
    {

        cout << "Match size = " << match.size() << endl;
        cout << "Whole match : " << match.str(0) << endl;
        cout << "First capturing group is '" << match.str(2)
             << "' which is captured at index " << match.position(2)
             << endl;
        cout << "Second capturing group is '" << match.str(4)
             << "' which is captured at index " << match.position(4)
             << endl;
        cout << "Third capturing group is '" << match.str(6)
             << "' which is captured at index " << match.position(6)
             << endl;

    }
    else if (regex_search(line, match, regex3) == true)
    {
        cout << "Match size = " << match.size() << endl;
        cout << "Whole match : " << match.str(0) << endl;
        cout << "First capturing group is '" << match.str(2)
             << "' which is captured at index " << match.position(2)
             << endl;
        cout << "Second capturing group is '" << match.str(4)
             << "' which is captured at index " << match.position(4)
             << endl;
        cout << "Third capturing group is '" << match.str(6)
             << "' which is captured at index " << match.position(6)
             << endl;
    }
    else if (regex_search(line, match, regex4) == true)
    {
        cout << "Match size = " << match.size() << endl;
        cout << "Whole match : " << match.str(0) << endl;
        cout << "First capturing group is '" << match.str(2)
             << "' which is captured at index " << match.position(2)
             << endl;
        cout << "Second capturing group is '" << match.str(4)
             << "' which is captured at index " << match.position(4)
             << endl;
        cout << "Third capturing group is '" << match.str(6)
             << "' which is captured at index " << match.position(6)
             << endl;
    }
    else
    {
        cout << "No match is found" << endl;
    }
}


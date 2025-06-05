
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Token {
    public:
    // It tokenizes strings based on white space ' '
    vector<string> tok(string s) {
        vector<string> res;
        istringstream ss(s);
        string word;
        while (ss >> word)
            res.push_back(word);
        return res;
    }
};


vector<string> getWords(string s, char delim){
    stringstream ss(s);
    vector<string> res;
    string placeholder;

    while(getline(ss, placeholder, delim)){
        res.push_back(placeholder);
    }

    return res;
}


int main(){
    string s = "Revanth Pershad";
    Token tk = Token();
    for(auto x : tk.tok(s))
        cout << x << " ";

    cout << endl;
    s = "Revanth,Pershad,Puli";
    for(auto x : getWords(s))
        cout << x << " ";
}
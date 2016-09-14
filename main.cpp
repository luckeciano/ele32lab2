#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



vector<char> alphabet;

bool inAlphabet(char atual) {
    for (int i = 0; i < alphabet.size(); i++) {
        if (alphabet[i] == atual) {
            return true;
        }
    }
    return false;
}

bool inDic(string Sc, vector<string> dic) {
    for (int i = 0; i < dic.size(); i++) {
        if (dic[i] == Sc) {
            return true;
        }
    }
    return false;
}

void readAlphabet(string bookPath){
    ifstream myfile;
    char atual;
    myfile.open (bookPath);
    if (myfile.is_open()){
        while (myfile.get(atual)){
            if (!inAlphabet(atual)) {
                alphabet.push_back(atual);
            }
            
        }
        myfile.close();
    }
 
}

void lempelZiv(string bookPath) {
    
    ifstream myfile;
    ofstream compacOutput;
    compacOutput.open ("output.txt");
    vector<string> dictionary;
    for (int i = 0; i < alphabet.size(); i++) {
        dictionary.push_back(string(1, alphabet[i]));
    }
    vector<char> Sc;
    
    char atual;
    myfile.open (bookPath);
    if (myfile.is_open()){
        string Sc = "";
        string S = "";
        while (myfile.get(atual)){
            Sc = S + atual;
            if (!inDic(Sc, dictionary)) {
                dictionary.push_back(Sc);
                compacOutput << inBin(S);
            }
            
            S += atual;
        }
        myfile.close();
        compacOutput.close();
    }
    
    
}

int main() {
    
    readAlphabet("annakarenina-english.txt");
    for (int i = 0; i < alphabet.size(); i++) {
        cout << alphabet[i] << endl;
    }
    
    
}
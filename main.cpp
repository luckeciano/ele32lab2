#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
using namespace std;



vector<char> alphabet;

bool inAlphabet(char atual) {
    bool inDict = false;
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

string inBin(string Sc, vector<string> dictionary){
    if (!inDic(Sc, dictionary)){
        return "";
    }
    int pos;
    int exponent = 0;
    int noOfBits = 1;
    for (pos = 0; dictionary[pos] != Sc ; pos++){
        if (pos > noOfBits){
            noOfBits *= 2;
            exponent++;
        }
    }
    if (pos > noOfBits){
            noOfBits *= 2;
            exponent++;
    }
    const unsigned int ssize = exponent;
    return bitset<ssize>(pos).to_string();
    
}

void lempelZiv(string bookPath) {
    
    ifstream myfile;
    vector<string> dictionary;
    for (int i = 0; i < alphabet.size(); i++) {
        dictionary.push_back(string(1, alphabet[i]));
    }
    vector<char> Sc;
    
    char atual;
    myfile.open (bookPath);
    if (myfile.is_open()){
        while (myfile.get(atual)){
            
        }
        myfile.close();
    }
    
    
}

int main() {
    
    readAlphabet("annakarenina-english.txt");
    for (int i = 0; i < alphabet.size(); i++) {
        cout << alphabet[i] << endl;
    }
    
    vector<string> dic;
    dic.push_back("a");
    dic.push_back("ab");
    dic.push_back("abc");
    dic.push_back("abcd");
    dic.push_back("abcde");
    cout<<inBin("abc",dic);
    
}
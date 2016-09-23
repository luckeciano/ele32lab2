#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace std;



vector<char> alphabet;
int L = 100;

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

int computeB(int number) {
    int b;
    float bFloat = log2(number - 1);

    if (bFloat - long(bFloat) > 0.000000) {
        b = long(bFloat) + 1;
    }   else b = long(bFloat);
    return b;
}

string inBin (string Sc, vector<string> dictionary) {
    int j;
    for (int k  = 0 ; k < dictionary.size(); k++){
        if (dictionary[k] == Sc) {
            j = k;
            break;
        }
    }
    int number = dictionary.size();
    int b = computeB(number);
    string r;
    while(j!=0) {r=(j%2==0 ?"0":"1")+r; j/=2;}
    while (r.size() < b) {
        r = "0" + r;
    }
    return r;

}



void init(vector<string> &dictionary) {
    dictionary.push_back("");
    for (int i = 0; i < alphabet.size(); i++) {
        dictionary.push_back(string(1, alphabet[i]));
    }

}

void lempelZiv(string bookPath) {

    ifstream myfile;
    ofstream compacOutput;
    compacOutput.open ("compressed_data.txt");
    vector<string> dictionary;
    init(dictionary);
    vector<char> Sc;

    char atual;
    myfile.open (bookPath);
    for (int i = 0; i < dictionary.size(); i++) {
        compacOutput << dictionary[i];
    }
    compacOutput << '\\';
    if (myfile.is_open()){
        string Sc = "";
        string S = "";
        while (myfile.get(atual)){
            if (dictionary.size() == L) {
                dictionary.clear();
                init(dictionary);
                Sc = "";
            }
            
            Sc = S + atual;
            if (!inDic(Sc, dictionary)) {
                dictionary.push_back(Sc);
                compacOutput << inBin(S, dictionary);
                Sc = "";
                S = atual;
            } else  S += atual;
            


        }
        compacOutput << '\\';
        compacOutput << S;
        myfile.close();
        compacOutput.close();
    }


}
int binToDec(vector<int> binary) {
    int value= 0;
    for (int i = binary.size() - 1; i >=0 ; i--) {
        value += binary[i] * pow(2, binary.size() - 1 - i);
    }

    return value;

}

void uncompress(string compactedPath) {
    ifstream myfile;
    ofstream uncompressedOutput;
    uncompressedOutput.open("uncompressed_data.txt");
    vector<string> dictionary;
    char symbol;
    dictionary.push_back("");

    myfile.open(compactedPath);
    myfile.get(symbol);
    while (symbol != '\\') {
        string aux = string(1,symbol);
        dictionary.push_back(aux);
        myfile.get(symbol);
    }
    vector<string> initialDic;
    initialDic = dictionary;

  
    if (myfile.is_open()) {
        int i = dictionary.size() + 1;
        string S = "";
        while(!myfile.eof()) {
             if (i == L + 1) {
                dictionary.clear();
                dictionary = initialDic;
                i = dictionary.size() + 1;
                S = "";
            }
            if (myfile.peek() == '\\')
                break;   
            int b = computeB(i);
            vector<int> eBin;
            int t = 0;
            char auxChar;
            for (int t = 0; t < b; t++) {
                char auxChar;
                myfile.get(auxChar);
                if (!myfile.eof()) {
                    int auxInt = auxChar - 48;
                    eBin.push_back(auxInt);
                }
            }
            int e = binToDec(eBin);
            if (e >= dictionary.size()) {
                S += S[0];
                uncompressedOutput << S;
                dictionary.push_back(S);
            } else {
                uncompressedOutput << dictionary[e];
                bool putInDic = false;
                for (int x = 0; x < dictionary[e].size(); x++) {
                    S +=  dictionary[e][x];
                    if (!inDic(S, dictionary)) {
                        dictionary.push_back(S);
                        putInDic = true;
                        S = string (dictionary[e].begin() + x, dictionary[e].end());
                        break;
                    }
    
                }
            }
            i ++;
          
           
        }
        char aux;
        myfile.get(aux); //simbolo de termino
        string endString;
        myfile >> endString;
        uncompressedOutput << endString;

    }


}

int main() {
    readAlphabet("test.txt");
    lempelZiv("test.txt");
    uncompress("compressed_data.txt");

}
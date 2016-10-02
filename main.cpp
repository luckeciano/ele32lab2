#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <chrono>
using namespace std;
using namespace std::chrono;



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

void lempelZiv(string bookPath, string compactPath) {

    ifstream myfile;
    ofstream compacOutput;
    compacOutput.open (compactPath);
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
    high_resolution_clock::time_point t1, t2;
    
    L = 100;
    cout << "L = " << L << endl;
    t1 = high_resolution_clock::now();
    readAlphabet("la-carita-del-prossimo.txt");
    lempelZiv("la-carita-del-prossimo.txt", "la-carita-del-prossimo-comp-100.txt");
    t2 = high_resolution_clock::now();
    auto duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "La Carita del Prossimo: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("der-dunkelgraf.txt");
    lempelZiv("der-dunkelgraf.txt", "der-dunkelgraf-comp-100.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Der Dunkelgraf: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("los-argonautas.txt");
    lempelZiv("los-argonautas.txt", "los-argonautas-comp-100.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Los Argonautas: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("annakarenina-english.txt");
    lempelZiv("annakarenina-english.txt", "annakarenina-english-comp-100.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Anna Karenina (English): " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("notre-dame-de-paris.txt");
    lempelZiv("notre-dame-de-paris.txt", "notre-dame-de-paris-comp-100.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Notredame de Paris: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("annakarenina-portugues.txt");
    lempelZiv("annakarenina-portugues.txt", "annakarenina-portugues-comp-100.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Anna Karenina (Portugues): " << duracao << endl;
    
    alphabet.clear();
    
    L = 10000;
    cout << endl << "L = " << L << endl;
    t1 = high_resolution_clock::now();
    readAlphabet("la-carita-del-prossimo.txt");
    lempelZiv("la-carita-del-prossimo.txt", "la-carita-del-prossimo-comp-10000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "La Carita del Prossimo: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("der-dunkelgraf.txt");
    lempelZiv("der-dunkelgraf.txt", "der-dunkelgraf-comp-10000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Der Dunkelgraf: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("los-argonautas.txt");
    lempelZiv("los-argonautas.txt", "los-argonautas-comp-10000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Los Argonautas: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("annakarenina-english.txt");
    lempelZiv("annakarenina-english.txt", "annakarenina-english-comp-10000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Anna Karenina (English): " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("notre-dame-de-paris.txt");
    lempelZiv("notre-dame-de-paris.txt", "notre-dame-de-paris-comp-10000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Notredame de Paris: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("annakarenina-portugues.txt");
    lempelZiv("annakarenina-portugues.txt", "annakarenina-portugues-comp-10000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Anna Karenina (Portugues): " << duracao << endl;
    
    alphabet.clear();
    
    L = 1000000;
    cout << endl << "L = " << L << endl;
    t1 = high_resolution_clock::now();
    readAlphabet("la-carita-del-prossimo.txt");
    lempelZiv("la-carita-del-prossimo.txt", "la-carita-del-prossimo-comp-1000000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "La Carita del Prossimo: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("der-dunkelgraf.txt");
    lempelZiv("der-dunkelgraf.txt", "der-dunkelgraf-comp-1000000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Der Dunkelgraf: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("los-argonautas.txt");
    lempelZiv("los-argonautas.txt", "los-argonautas-comp-1000000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Los Argonautas: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("annakarenina-english.txt");
    lempelZiv("annakarenina-english.txt", "annakarenina-english-comp-1000000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Anna Karenina (English): " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("notre-dame-de-paris.txt");
    lempelZiv("notre-dame-de-paris.txt", "notre-dame-de-paris-comp-1000000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Notredame de Paris: " << duracao << endl;
    
    alphabet.clear();
    
    t1 = high_resolution_clock::now();
    readAlphabet("annakarenina-portugues.txt");
    lempelZiv("annakarenina-portugues.txt", "annakarenina-portugues-comp-1000000.txt");
    t2 = high_resolution_clock::now();
    duracao = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Anna Karenina (Portugues): " << duracao << endl;
    
    alphabet.clear();
    //uncompress("compressed_data.txt");

}
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



vector<char> dic;

bool inDic(char atual) {
    bool inDict = false;
    for (int i = 0; i < dic.size(); i++) {
        if (dic[i] == atual) {
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
            if (!inDic(atual)) {
                dic.push_back(atual);
            }
            
        }
        myfile.close();
    }
 
}

int main() {
    
    readAlphabet("annakarenina-portugues.txt");
    cout << dic.size() << endl;
    
    
}
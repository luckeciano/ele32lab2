#include <iostream>

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

void readAlphabet(){
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
    
    
    
    
}
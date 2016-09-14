#include <iostream>

using namespace std;



vector<char> dic;

bool inDic() {
    
}

void readBook(){
    ifstream myfile;
    char atual;
    myfile.open (bookPath);
    if (myfile.is_open()){
        while (myfile.get(atual)){
            if (!inDic) {
                dic.push_back(atual);
            }
            
        }
        myfile.close();
    }
 
}


int main() {
    
    
    
    
    
}
#include "charlist.h"
#include <cstdlib>
#include <sstream>
using namespace std;

int main(){
    string line;
    cout << "Input word and key to jumble: ";
    while(getline(cin, line)){
        stringstream s(line);
        CharList clist;
        int pos, len;
        string str;
        s >> str;
        len = str.length();
        cout << str << " is jumbled by key ";
        for(int i = 0; i < len; i++){
            s >> pos;
            if( pos % 2){ // odd number
                clist.insertFront(str[i]);
            } else {
                clist.insertRear(str[i]);
            }
            cout << pos; 
        }
        cout << " to " << clist << endl;
        cout << "Input word and key to jumble: ";
    }
    cout << endl;
}

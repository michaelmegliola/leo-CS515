#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Set s1;
    for (int i=1; i<10000; i++){
        s1.insert(i);
        s1.insert(i-1);
    }
    assert(s1.size()==10000);
    
    for (int i=1; i<10000; i++){
        s1.erase(i);
        s1.erase(i-1);
    }
    assert(s1.size()==0);
    cout << "done" << endl;
}

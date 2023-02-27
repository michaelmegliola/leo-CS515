#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Set s1;
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(2);
    s1.insert(4);
    s1.insert(6);
    
    assert(s1.size()==5);
    
    // test assignment operator
    Set s2;
    assert(s2.size()==0);
    s2 = s1;
    assert(s2.size()==5);
    cout << s1 << endl;
    cout << s2 << endl;
       
    assert(s1 == s2);
    
    s1.clear();
    assert(s2.size()==5);
     
    s1.insert(1);
    s1.insert(9);
    s1.insert(3);
    s1.insert(10);
    s1.insert(21);
    s1.insert(3);
    s1.insert(4);
    s1.insert(21);
    s1.insert(33);
    s1.insert(21);
    s1.insert(14);
    s1.insert(9);
    s1.insert(1); 
    assert(s1.size()==8);
    cout << s1 << endl;
    assert(s2.size()==5);
}

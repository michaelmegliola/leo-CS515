// test driver for set ADT with built-in iterator
#include "set.h"
#include <cassert>
#include <iostream>
#include <string>
using namespace std;


int main(){
    Set s1;
    Set::Iterator it1, it2; 
    
    // insert more
    for (int i = 1; i < 9; i++){
       s1.insert(to_string(i));
    }
    
    // test iterator
    it1 = s1.begin();
    int i = 1;
    while( it1 != s1.end() ){
        assert(*it1 == to_string(i));
        it1++;
        i++;
    }

    // test iterator and find
    it1 = s1.find("8"); 
    assert(it1 != s1.end());
    assert(*it1 == "8");
    
    cout << s1 << endl;
    
    *it1 = "9";
    it2 = s1.find("9"); 
    assert( it1 == it2 );
    
    cout << s1 << endl;
    
    it1 = s1.end();
    it1--;
    i = 7; 
    while( it1 != s1.begin() && i > 0 ){
        it1--;
        assert(*it1 == to_string(i));
        i--;
    }
   
    Set s2 = s1;
    
    cout << s2 << endl;
    
    s1.insert("a");
    s1.insert("z");
    s1.insert("d");
    
    Set tmp = s1 & s1;
    cout << tmp << endl;
    
    tmp = s1 | s1;
    cout << tmp << endl;
    
    tmp = s1 & s2;
    cout << tmp << endl;
    
    tmp = tmp & s1;
    cout << tmp << endl;
    
}

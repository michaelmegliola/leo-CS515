// test driver for set ADT with built-in iterator
#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Set s1;
    Set::Iterator it; 
    
    s1.erase("aa");
    s1.insert("ba");
    s1.insert("bc");
    s1.insert("ac");
    assert(s1.size()==3);
    s1.insert("bc");
    assert(s1.size()==3);
    s1.insert("zc");
    s1.insert("kc");
    assert(s1.size()==5);
    

    cout << "++basic operations and iterators++"<< endl;
    it = s1.begin(); 
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    assert(s1.find("ee")==s1.end());
    assert(s1.find("kc")!=s1.end());
    s1.erase("kc");
    assert(s1.size()==4);
    assert(s1.find("kc")==s1.end());

    s1.insert("ma");
    s1.insert("ll");
    s1.insert("er");
    it = s1.begin(); 
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    s1.insert("od");
    s1.insert("fd");
    s1.insert("rf");
    
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    s1.insert("od");
    s1.insert("fd");
    s1.insert("rf");
    
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    assert(s1.size()==10);
       
    
    s1.erase("od");
    assert(s1.size()==9);
    s1.erase("od");
    assert(s1.size()==9);
    s1.erase("bc");
    assert(s1.size()==8);
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    // test overloaded operator <<
    cout << s1 << endl;
    
    // test copy constructor
    cout << "++copy constructor and set equality++"<< endl;
    Set s2 = s1;
    assert(s2.size()==8);
    assert(s2 == s1);
    
    s1.clear();
    assert(s1.size()==0);
    assert(s1.find("ac")==s1.end());
    assert(s1.find("fd")==s1.end());
    
    assert(s2.size()==8);
    cout << s2 << endl; 
   
    // test assignment operator
    cout << "++assignment operator and set equality++"<< endl;
    s1.insert("aa");
    cout << s1 << endl;
    s1 = s2;
    assert(s1==s2);
    
    
    s1.clear();
    s1.insert("aa");
    s1.insert("ba");
    s1.insert("cf");
    s1.insert("do");
    s1.insert("vd");
    s1.insert("ll");
    s1.insert("nj");
    s1.insert("ra");
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    Set tmp;
    
    cout << "++set difference ++"<< endl;
    tmp  = s1 - s2;
    cout << "difference: " << tmp << endl;
    
    // set intersec
    cout << "++set intersec++"<< endl;
    tmp = s1 & s2;
    cout << "intersec: " << tmp << endl;
    
    cout << "++set join"<< endl;
    tmp = s1 | s2;
    cout << "join: " << tmp << endl;
    
     
}

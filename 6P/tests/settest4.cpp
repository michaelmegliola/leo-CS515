// test driver for set ADT with built-in iterator
#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Set s1;
    Set::Iterator it; 
    
    s1.erase("aa");
    assert(s1.size()==0);
    s1.insert("aa");
    
    assert(s1.size()==1);
    s1.insert("ca");
    s1.insert("ca");
    assert(s1.size()==2);

    assert(s1.find("ea")==s1.end());
    it = s1.find("ca");
    assert(it!=s1.end());
    assert(*it=="ca");

    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    it = s1.begin();
    it++;
    *it = "zzz";
    
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    Set s2 = s1;
    
    s1.insert("oa");
    s1.insert("fa");
    s1.insert("pa");
    s1.insert("it");
    s1.erase("ca");
    s1.erase("ca");
    
    s2.insert("ca");
    s2.insert("ff");
    s2.insert("ca");
    s2.insert("ff");
    s2.insert("ea");
    s2.insert("it");
    s2.insert("aba");
    s2.insert("ffd");
    s2.insert("eafdf");
    s2.insert("cad");
    s2.insert("fif");
    s2.insert("ear"); 
    
    it = s2.end();
    while( it != s2.begin() ){
        cout << *it << " ";
        it--;
    }
    cout << *it; 
    cout << endl;
    
    Set tmp = s1 & s1;
    cout << tmp << endl;
    
    tmp = s1 | s1;
    cout << tmp << endl;
    
    tmp = s1 & s2;
    cout << tmp << endl;
    
    tmp = tmp & s1;
    cout << tmp << endl;
    
}

// test driver for set ADT with built-in reverse_iterator
#include "set.h"
#include <cassert>
#include <iostream>
#include <string>
using namespace std;


int main(){
    
    Set s1; 
    s1.insert("aa");
    s1.insert("ca");
    s1.insert("oa");
    s1.insert("fa");
    s1.insert("pa");
    s1.insert("it");
    
    Set::Iterator it; 
    Set::Reverse_Iterator rit; 
    
    // test reverse iterator
    rit = s1.rbegin();
    while( rit != s1.rend() ){
        cout << *rit << " ";
        rit++;
    }
    cout << endl;
   
    rit = s1.rend();
    while( rit != s1.rbegin() ){
        rit--;
        cout << *rit << " ";
    }
    cout << endl;
    
    // test iterator
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
   
    it = s1.end();
    while( it != s1.begin() ){
        it--;
        cout << *it << " ";
    }
    cout << endl;
    
    s1.insert("it");
    s1.insert("ga");
    s1.insert("ok");
    s1.insert("la");
    s1.insert("qa");
    s1.insert("ot");
    
    // test reverse iterator
    rit = s1.rbegin();
    while( rit != s1.rend() ){
        cout << *rit << " ";
        rit++;
    }
    cout << endl;
   
    rit = s1.rend();
    while( rit != s1.rbegin() ){
        rit--;
        cout << *rit << " ";
    }
    cout << endl;
    
    // test iterator
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
   
    it = s1.end();
    while( it != s1.begin() ){
        it--;
        cout << *it << " ";
    }
    cout << endl;
    
   
    
    
}

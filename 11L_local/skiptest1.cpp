#include "skiplist.h"
#include <cassert>

int main(){
    SkipList s(4, 0.5);
   
    s.insert(10);
    s.insert(75);
    s.insert(20);
    s.insert(64);
    s.insert(25);
    s.insert(23);
    s.insert(46);
    s.insert(27);
    s.insert(35);
    s.insert(52);

    s.erase(25);
    assert(s.find(25)==false);
    
    s.erase(10);
    assert(s.find(10)==false);
    
    s.erase(64);
    assert(s.find(64)==false);
    
    s.erase(35);
    assert(s.find(35)==false);
    
    s.erase(35);
    assert(s.find(35)==false);
    
    s.erase(100);
    assert(s.find(100)==false);
    
}

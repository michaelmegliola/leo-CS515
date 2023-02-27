#include "skiplist.h"
#include <cassert>
#include <cstdlib>
#include <limits>
using namespace std;

int main(){
    SkipList s(5, 0.5);
   
    s.erase(25);
    assert(s.find(25)==false);
    
    s.insert(10);
    s.insert(75);
    s.insert(25);
    s.insert(23);
    s.insert(46);
    s.insert(27);
    s.insert(35);
    s.insert(52);
    s.insert(20);
    s.insert(64);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(7);
    s.insert(125);
    s.insert(123);
    s.insert(146);
    s.insert(127);
    s.insert(135);
    s.insert(152);
    s.insert(1);
    s.insert(7);
    s.insert(5);
    s.insert(6);
    

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
    
    s.erase(3);
    assert(s.find(3)==false);
    
    s.erase(125);
    assert(s.find(125)==false);
    
    s.erase(123);
    assert(s.find(123)==false);
    
    s.erase(7);
    assert(s.find(7)==false);
    
    s.erase(75);
    assert(s.find(75)==false);
    
    s.erase(25);
    assert(s.find(25)==false);
    
    s.erase(23);
    assert(s.find(23)==false);
   
    s.erase(46);
    assert(s.find(46)==false);
    
    s.erase(27);
    assert(s.find(27)==false);
    
    s.erase(35);
    assert(s.find(35)==false);
    
    s.erase(52);
    assert(s.find(52)==false);
    
    s.erase(20);
    assert(s.find(20)==false);
    
    s.erase(64);
    assert(s.find(64)==false);
    
    s.erase(2);
    assert(s.find(2)==false);
    
    s.erase(3);
    assert(s.find(3)==false);
    
    s.erase(4);
    assert(s.find(4)==false);
    
    s.erase(7);
    assert(s.find(7)==false);
    
    s.erase(146);
    assert(s.find(146)==false);
    
    s.erase(127);
    assert(s.find(127)==false);
    
    s.erase(135);
    assert(s.find(135)==false);
    
    s.erase(152);
    assert(s.find(152)==false);
    
    s.erase(1);
    assert(s.find(1)==false);
    
    s.erase(5);
    assert(s.find(5)==false);
    
    s.erase(6);
    assert(s.find(6)==false);
    
    s.erase(101);
    assert(s.find(101)==false);

    
    s.erase(numeric_limits<int>::max()-1);
    assert(s.find(numeric_limits<int>::max()-1)==false);
    
    s.erase(numeric_limits<int>::min()+1);
    assert(s.find(numeric_limits<int>::min()+1)==false);

}

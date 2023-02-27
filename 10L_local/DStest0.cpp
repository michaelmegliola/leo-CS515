#include "DisjointSet0.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(){
    DisjointSet s;
   
    /*
     *   you fill in here to set up the disjoint set 
     */
    
    assert(s.findSet(1) == s.findSet(6)); // 1 and 6 are connected.
    assert(s.findSet(3) != s.findSet(6)); // 3 and 6 are not connected.
    assert(s.findSet(1) == s.findSet(1)); // 1 and 1 are connected.
    assert(s.findSet(3) == s.findSet(5)); // 3 and 5 are connected.
    assert(s.findSet(3) != s.findSet(9)); // 3 and 9 are not connected.
    
}

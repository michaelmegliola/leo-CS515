// tests for operator[] and map iterator

#include "map.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Map<int, int> m1;
    
    assert(m1.size()==0);
    Map<int, int>::Iterator it = m1.find(1);
    assert(it == m1.end());
    
    m1[1] = 1;
    m1[2] = 1;
    m1[35] = 1;
    m1[39] = 1;
    m1[44] = 1;
    m1[4] = 1;
    m1[28] = 1;
    m1[3] = 1;
    m1[21] = 1;
    m1[31] = 1;
    m1[12] = 1;
    m1[33] = 1;
    m1[45] = 1;
    m1[49] = 1;
    m1[17] = 1;
    
    assert(m1.size()==15);
    
    // elements in the set
    it = m1.find(17);
    assert( it->key == 17);
    assert( it->data == 1);
    assert( it != m1.end());
    
    it = m1.find(12);
    assert( it->key == 12);
    assert( it->data == 1);
    assert( it != m1.end());
    
    it = m1.find(4);
    assert( it->key == 4);
    assert( it->data == 1);
    assert( it != m1.end());
    
    it = m1.find(1);
    assert( it->key == 1);
    assert( it->data == 1);
    assert( it != m1.end());
    
    it = m1.find(49);
    assert( it->key == 49);
    assert( it->data == 1);
    assert( it != m1.end());
    
    it = m1.find(21);
    assert( it->key == 21);
    assert( it->data == 1);
    assert( it != m1.end());
    
    
    it = m1.find(28);
    assert( it->key == 28);
    assert( it->data == 1);
    assert( it != m1.end());
    
    // elements not in the set
    it = m1.find(13);
    assert( it == m1.end());
    
    it = m1.find(18);
    assert( it == m1.end());
    
    it = m1.find(0);
    assert( it == m1.end());
    
    it = m1.find(100);
    assert( it == m1.end());
    
    it = m1.find(42);
    assert( it == m1.end());
    
    
    it = m1.find(50);
    assert( it == m1.end());
    
    
    it = m1.find(15);
    assert( it == m1.end());
    
    it = m1.find(-10);
    assert( it == m1.end());
    
    m1[44] = 2;
    m1[4] = 2;
    m1[28] = 2;
    m1[3] = 2;
    m1[39] = 2;
    m1[33] = 2;
    m1[45] = 2;
    m1[49] = 2;
    m1[17] = 2;
    
    // elements in the set
    it = m1.find(44);
    assert( it->key == 44);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.find(4);
    assert( it->key == 4);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.find(28);
    assert( it->key == 28);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.find(3);
    assert( it->key == 3);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.find(39);
    assert( it->key == 39);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.find(33);
    assert( it->key == 33);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.find(45);
    assert( it->key == 45);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.find(49);
    assert( it->key == 49);
    assert( it->data == 2);
    assert( it != m1.end());
    
    
    it = m1.find(17);
    assert( it->key == 17);
    assert( it->data == 2);
    assert( it != m1.end());
    
    it = m1.begin();
    while ( it != m1.end() ){
        cout << it->key << " ";
        it++;
    }
    cout << endl;

    
}

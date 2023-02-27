// tests for map iterator
#include <iostream>
#include <string>
#include <cassert>
#include "map.h"
using namespace std;

int main(){
    Map<int, int> m1;
    assert( m1.insert(12, 1) == true);
    assert( m1.insert(11, 2) == true);
    assert( m1.insert(13, 1) == true);
    assert( m1.insert(10, 2) == true);
    assert( m1.insert(9, 1) == true);
    assert( m1.insert(8, 2) == true);
    assert( m1.insert(7, 1) == true);
    assert( m1.insert(6, 2) == true);
    assert( m1.insert(14, 1) == true);
    assert( m1.insert(15, 2) == true);
    assert( m1.insert(17, 1) == true);
    assert( m1.insert(20, 2) == true);
    assert( m1.insert(44, 1) == true);
    assert( m1.insert(54, 2) == true);
    assert( m1.insert(55, 1) == true);
    assert( m1.insert(25, 2) == true);
    assert( m1.insert(18, 1) == true);
    assert( m1.insert(19, 2) == true);
    assert( m1.insert(97, 1) == true);
    assert( m1.insert(21, 2) == true);

    Map<int, int>::Iterator it = m1.begin();
    
    while ( it != m1.end() ){
        cout << it->key << " ";
        it++;
    }
    cout << endl;
    
    it = m1.begin();
    for (int i=0; i<19; i++)
        it++;
    assert((*it).key == 97);
    
    it++;
    assert(it == m1.end());
    it++; // ++ should not go beyound end
}

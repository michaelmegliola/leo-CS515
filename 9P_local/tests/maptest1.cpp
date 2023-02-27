// tests for insert() method
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
    
    assert( m1.insert(14, 1) == false);
    assert( m1.insert(15, 2) == false);
    assert( m1.insert(17, 1) == false);
    assert( m1.insert(20, 2) == false);

    //cout << m1;
    
    Map<int, char> m2;
    assert( m2.insert(14, 60) == true);
    assert( m2.insert(15, 60) == true);
    assert( m2.insert(17, 60) == true);
    assert( m2.insert(9, 60) == true);
    assert( m2.insert(8, 60) == true);
    assert( m2.insert(7, 60) == true);
    assert( m2.insert(6, 60) == true);
    assert( m2.insert(20, 60) == true);
    assert( m2.insert(10, 60) == true);
    assert( m2.insert(12, 60) == true);
    assert( m2.insert(11, 60) == true);
    assert( m2.insert(13, 60) == true);
    
    assert( m2.insert(7, 60) == false);
    assert( m2.insert(6, 60) == false);
    assert( m2.insert(20, 60) == false);
    assert( m2.insert(10, 60) == false);

    //cout << m2;
    
    Map<int, char> m3;
    assert( m3.insert(1, 65) == true);
    assert( m3.insert(2, 65) == true);
    assert( m3.insert(3, 65) == true);
    assert( m3.insert(4, 65) == true);
    assert( m3.insert(5, 65) == true);
    assert( m3.insert(6, 65) == true);
    assert( m3.insert(7, 65) == true);
    assert( m3.insert(8, 65) == true);
    assert( m3.insert(9, 65) == true);
    assert( m3.insert(10, 65) == true);
    
    assert( m3.insert(7, 7) == false);
    assert( m3.insert(6, 7) == false);
    assert( m3.insert(3, 7) == false);
    assert( m3.insert(4, 7) == false);
    
    //cout << m3;
}

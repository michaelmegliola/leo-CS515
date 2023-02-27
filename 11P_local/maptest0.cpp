#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main(){
    Map<string, string> m1;
    cout << "\n\nMap test 1\n\n";
    
    assert( m1.insert("cute", "boy") == true);
    assert( m1.insert("cool", "breeze") == true);
    assert( m1.insert("warm", "fire") == true);
    assert( m1.insert("red", "rose") == true);
    assert( m1.insert("cool", "ice") == false);
    
    cout << m1 << "\n";
    Map<string, string>::Iterator iter = m1.begin();
    while (iter != m1.end()){
        cout << iter->key << " ";
        iter++;
    }
    
    iter++;
    iter++; 
    
    cout << "\n\nMap test 2\n\n";
    Map<int, int> m2;
    m2[29] = 1;
    m2[34] = 1;
    m2[39] = 1;
    m2[23] = 1;
    m2[87] = 1;
    m2[45] = 1;
    m2[83] = 1;
    m2[22] = 1;
    m2[12] = 1;
    m2[57] = 1;
    m2[21] = 1;
    m2[30] = 1;
    m2[2] = 1;
    m2[26] = 1;
    m2[5] = 1;
    m2[11] = 1;
    m2[32] = 1;
    m2[86] = 1;
    cout << m2 << "\n\n\n\n\n";
    
    m2[29] = 2;
    m2[34] = 2;
    m2[39] = 2;
    m2[23] = 2;
    m2[87] = 2;
    m2[45] = 2;
    m2[83] = 2;
    m2[22] = 2;
    m2[12] = 2;
    m2[57] = 2;
    m2[21] = 2;
    m2[30] = 2;
    m2[2] = 2;
    m2[26] = 2;
    m2[5] = 2;
    m2[11] = 2;
    m2[32] = 2;
    m2[86] = 2;
    cout << m2 << "\n\n";
    
    Map<int, int>::Iterator iter2 = m2.begin();
    while (iter2 != m2.end()){
        cout << iter2->key << " ";
        iter2++;
    }
	cout << endl;
    
}

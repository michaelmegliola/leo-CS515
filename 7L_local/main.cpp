#include <iostream>
#include "set.h"
#include <cassert>
using namespace std;

int main() {
    Set s1;
    s1.insert(14);
    s1.insert(9);
    s1.insert(3);
    s1.insert(19);
    s1.insert(21);
    s1.insert(33);
    s1.insert(35);
    s1.insert(17);
    //================
    //s1.insert(11);// |
    //s1.insert(12);// |
    //s1.insert(13);// |
    //================
    assert(s1.size()==8);
    cout << s1;

    // uncomment the code for testing
    cout << "Depth First In Order Traverse: " << endl;
    s1.depthFirstInOrder();
    cout << "\nBreadth First Traverse: " << endl;
    s1.breadthFirst();
    cout << endl;
}

#include "HuffTree.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
    HuffTree h;
    char c[7] = {'e', 'f', 'd', 'a', 'g'};
    int f[7] = {12, 4, 2, 3, 1};
    h.buildTree(c,f,5);

    cout << h.getCode('e') << endl;
    cout << h.getCode('f') << endl;
    cout << h.getCode('a') << endl;
    cout << h.getCode('g') << endl;
    cout << h.getCode('d') << endl;
}

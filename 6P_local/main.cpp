#include <iostream>
#include "set.h"
#include <cassert>
using namespace std;

int main() {
    Set s1;
    s1.insert("a");
    s1.insert("b");
    s1.insert("c");
    assert(s1.size()==3);
    s1.insert("c");
    assert(s1.size()==3);
    cout << s1;
}

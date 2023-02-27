#include <iostream>
#include "PQueue0.cpp"

int main() {
    int i, x;

    cout << "Test 0: Enqueuing..." << endl;
    int a0[4] = {24, 55, 22, 31};
    PQueue q0(a0, 4);
    assert(q0.size() == 4);
    cout << "Test 0: Dequeuing..." << endl;
    for (i = 1; i <= 4; i++) {
        x = q0.findMin();
        q0.deleteMin();
        cout << x << " ";
    }
    cout << endl;
}

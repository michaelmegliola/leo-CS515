#include <iostream>
using namespace std;

int main(){
    int i = 3;
    int *ptr = &i;
    int **pptr = &ptr;

    while((*ptr)--)
	    cout << "hello" << endl;
    for(int j = 0; j < 3; j++)
        cout << "bye" << endl;	
}

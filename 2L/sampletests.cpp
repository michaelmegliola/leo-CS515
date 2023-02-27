#include <iostream>
#include <cstdlib>
using namespace std;

int myatoi(const char * ptr);

int main(){

    cout << myatoi("98") << " " << atoi("98") << endl;
    cout << myatoi("  98123") << " " << atoi("  98123") << endl;
    cout << myatoi("+98") << " " << atoi("+98") << endl;
    cout << myatoi("98a") << " " << atoi("98a") << endl;
    cout << myatoi("a98") << " " << atoi("a98") << endl;
    cout << myatoi("1a98") << " " << atoi("1a98") << endl;
    cout << myatoi("+ 98") << " " << atoi("+ 98") << endl;
    cout << myatoi("    ") << " " << atoi("    ") << endl;
	// ADD YOUR OWN TEST CASES HERE
	
}




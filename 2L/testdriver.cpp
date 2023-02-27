#include <iostream>
#include <cstdlib>
using namespace std;

int myatoi(const char * ptr);

int main(){
    cout << myatoi("2") << " " << atoi("2") << endl;
	cout << myatoi("203") << " " << atoi("203") << endl;
	cout << myatoi("232345") << " " << atoi("232345") << endl;
	cout << myatoi("2.0") << " " << atoi("2.0") << endl;
	cout << myatoi("2.") << " " << atoi("2.") << endl << endl;
	
    cout << myatoi("23.2") << " " << atoi("23.2") << endl;
    cout << myatoi("23.8") << " " << atoi("23.8") << endl;
    cout << myatoi("0.002003") << " " << atoi("0.002003") << endl;
    cout << myatoi("    ") << " " << atoi("    ") << endl;
    cout << myatoi("  123") << " " << atoi("  123") << endl << endl;
    
    cout << myatoi("  12 3") << " " << atoi("  12 3") << endl;
    cout << myatoi("+28") << " " << atoi("+28") << endl;
    cout << myatoi("-28") << " " << atoi("-28") << endl;
    cout << myatoi("2b8a") << " " << atoi("2b8a") << endl;
    cout << myatoi("a98") << " " << atoi("a98") << endl << endl;
    
    cout << myatoi("11-a98") << " " << atoi("11-a98") << endl;
    cout << myatoi("+ 98") << " " << atoi("+ 98") << endl;
    cout << myatoi(" -28") << " " << atoi(" -28") << endl;
    cout << myatoi("--28") << " " << atoi("--28") << endl;
    cout << myatoi("-+28") << " " << atoi("-+28") << endl << endl;
    
    // used in starter code
    /*
   
    cout << myatoi("98") << " " << atoi("98") << endl;
    cout << myatoi("  98123") << " " << atoi("  98123") << endl;
    cout << myatoi("+98") << " " << atoi("+98") << endl;
    cout << myatoi("98a") << " " << atoi("98a") << endl;
    cout << myatoi("a98") << " " << atoi("a98") << endl;
    cout << myatoi("1a98") << " " << atoi("1a98") << endl;
    cout << myatoi("+ 98") << " " << atoi("+ 98") << endl;
    cout << myatoi("    ") << " " << atoi("    ") << endl;
    */
}


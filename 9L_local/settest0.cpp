#include <iostream>
#include <cstdlib>
#include <cassert>
#include "set.h"
using namespace std;

int main1(){
    Set<int> s1;
		
	s1.insert(2);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(3);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(12);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(11);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(13);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(10);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(9);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(8);
	cout << s1;
	cout << "************************************" << endl;
		
	s1.insert(7);
	cout << s1;
	cout << "************************************" << endl;
    
}

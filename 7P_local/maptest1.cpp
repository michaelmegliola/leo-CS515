// tests for insert() method
#include <iostream>
#include <string>
#include <cassert>
#include "map.h"
using namespace std;

int main(){
	
	Map m1;
	
	cout << m1; 

	assert( m1.insert("12", "1") == true);
	assert( m1.insert("9", "1") == true);
	assert( m1.insert("6", "2") == true);
	assert( m1.insert("11", "2") == true);
	assert( m1.insert("15", "2") == true);
	assert( m1.insert("10", "2") == true);
	assert( m1.insert("8", "2") == true);
	assert( m1.insert("13", "1") == true);
	assert( m1.insert("7", "1") == true);
	assert( m1.insert("14", "1") == true);

    cout << m1; 

}

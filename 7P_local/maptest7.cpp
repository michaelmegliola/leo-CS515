// test for copy constructor and assignment operator

#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main(){
	Map m1;
	assert( m1.insert("a", "boy") == true);
	assert( m1.insert("k", "kite") == true);
	assert( m1.insert("z", "zoo") == true);
	assert( m1.insert("b", "breeze") == true);
	assert( m1.insert("r", "fire") == true);
	assert( m1.insert("d", "rose") == true);
	assert( m1.insert("c", "ice") == true);
	assert( m1.insert("c", "car") == false);
	
	Map m2;
	cout << "++++++++new tree++++++++++++" << endl;
	cout << m2 << endl;
	cout << "++++++++new tree again++++++++++++" << endl;
	m2 = m1; 
	cout << m2 << endl;

	assert(m1.size()==7);
	assert(m2.size()==7);

	m1.erase("c");
	m2["c"] = "cute";

	assert(m1.size()==6);
	assert(m2.size()==7);
	cout << "++++++++tree 1++++++++++++" << endl;
	cout << m1 << endl;
	cout << "++++++++tree 2++++++++++++" << endl;
	cout << m2 << endl;

	m2.insert("haha", "me here");
	cout << "++++++++new tree again++++++++++++" << endl;
	m2 = m1;
	cout << m2 << endl;

}

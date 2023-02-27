#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main(){
	Map m1;
	assert( m1.insert("a", "boy") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++" << endl;
	assert( m1.insert("b", "breeze") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;
	assert( m1.insert("r", "fire") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;
	assert( m1.insert("d", "rose") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;
	assert( m1.insert("c", "ice") == true);
	cout << m1 << endl;
	assert( m1.insert("c", "car") == false);


	
	Map::Iterator iter = m1.begin();
	cout << "here:" << iter->data << std::endl;

	m1["new"] = "element";

	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;

	m1["cool"] = "ice";  
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;

	m1.erase("cool");
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;
	
	Map m2(m1);
	m2.erase("a");
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;
	cout << m2 << endl;
	
}

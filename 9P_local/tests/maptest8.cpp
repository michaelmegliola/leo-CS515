// test for assignment operator only (not copy constructor)
// not required in Spring 2015

#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main(){
	Map<string, string> m1;
	Map<string, string>::Iterator it;

	assert( m1.insert("a", "boy") == true);
	assert( m1.insert("k", "kite") == true);
	assert( m1.insert("z", "zoo") == true);
	assert( m1.insert("b", "breeze") == true);
	assert( m1.insert("r", "fire") == true);
	assert( m1.insert("d", "rose") == true);
	assert( m1.insert("c", "ice") == true);
	assert( m1.insert("c", "car") == false);

	Map<string, string> m2;
	
	cout << "++++++++m2++++++++++++" << endl;
	it = m2.begin();
	while(it != m2.end()){
		cout << it->key << " "; 
		it++;
	}
	cout << endl;
	
	m2 = m1; 
	assert(m1.size()==7);
	assert(m2.size()==7);
   
	cout << "++++++++m2 after assignment++++++++++++" << endl;
	it = m2.begin();
	while(it != m2.end()){
		cout << it->key << " "; 
		it++;
	}
	cout << endl; 

	m1.erase("c");
	m2["c"] = "cute";

	assert(m1.size()==6);
	assert(m2.size()==7);
	cout << "++++++++m1 after modificiation++++++++++++" << endl;
	it = m1.begin();
	while(it != m1.end()){
		cout << it->key << " "; 
		it++;
	}
	cout << endl;

	cout << "++++++++m2 after modificiation++++++++++++" << endl;
	it = m2.begin();
	while(it != m2.end()){
		cout << it->key << " "; 
		it++;
	}
	cout << endl;
	
	m2.insert("haha", "me here");
	cout << "++++++++m2 after modificiation++++++++++++" << endl;
	it = m2.begin();
	while(it != m2.end()){
		cout << it->key << " "; 
		it++;
	}
	cout << endl;
	
	
	m2 = m1;
	
	
	cout << "++++++++m2 after modificiation again++++++++++++" << endl;
	it = m2.begin();
	while(it != m2.end()){
		cout << it->key << " "; 
		it++;
	}
	cout << endl;

	cout << "++++++++m1 after modificiation again++++++++++++" << endl;
	it = m1.begin();
	while(it != m1.end()){
		cout << it->key << " "; 
		it++;
	}
	cout << endl;
}

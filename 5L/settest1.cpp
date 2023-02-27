#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
	Set s1;
	s1.insert(1);
	s1.insert(2);
	s1.insert(3);
	assert(s1.size()==3);
	s1.insert(3);
	assert(s1.size()==3);

	assert(s1.find(4)==false);
	assert(s1.find(3)==true);
	s1.erase(3); 
	assert(s1.size()==2);
	assert(s1.find(3)==false);

	s1.insert(2);
	s1.insert(4);
	s1.insert(6);
	assert(s1.size()==4);
	s1.erase(6);
	assert(s1.size()==3);
	s1.erase(6);
	assert(s1.size()==3);
	s1.erase(1);
	assert(s1.size()==2);
	cout << s1 << endl;

	s1.clear();
	assert(s1.size()==0);
	assert(s1.find(2)==false);
	assert(s1.find(4)==false);

	s1.insert(1);
	s1.insert(9);
	s1.insert(3);
	s1.insert(10);
	s1.insert(21);
	s1.insert(3);
	s1.insert(4);
	s1.insert(21);
	s1.insert(33);
	s1.insert(21);
	s1.insert(14);
	s1.insert(9);
	s1.insert(1); 
	assert(s1.size()==8);
	cout << s1 << endl;

	s1.erase(1);
	s1.erase(9);
	s1.erase(3);
	s1.erase(10);
	s1.erase(21);
	s1.erase(3);
	s1.erase(4);
	s1.erase(21);
	s1.erase(33);
	s1.erase(21);
	s1.erase(14);
	s1.erase(9);
	s1.erase(1);

	assert(s1.size()==0);
	cout << s1 << endl;
}

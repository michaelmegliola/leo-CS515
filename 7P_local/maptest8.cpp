// test must finish within 60 seconds on agate with our grading system. 


#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
using namespace std;

int main(){
	Map m;
	int key;
	stringstream ss;
	srand(time(0));
	for (int i=1; i<1000000; i++){
		key = rand()%100000;
		m.insert(std::to_string(key), "hello");
	}
	Map m1 = m;
}

#include "map.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

int main(){
	Map m;
	Map::Iterator it;
	
	assert(m.insert("20", "a"));
	assert(m.insert("10", "b"));
	assert(m.insert("15", "c"));
	assert(m.insert("5", "d"));
	assert(m.insert("30", "e"));
	assert(m.insert("25", "f"));
	assert(m.insert("35", "g"));
	assert(m.insert("21", "h"));
	assert(m.insert("22", "i"));
	assert(m.insert("23", "j"));
	assert(m.size()==10);
	cout << m << endl;
	
	
	assert(m.erase("20")); 
	cout << "------------erase 20------------" << endl;
	assert(m.size()==9);
	cout << m << endl;
	
	assert(m.erase("15")); 
	cout << "------------erase 15------------" << endl;
	assert(m.size()==8);
	cout << m << endl;
	
	assert(m.erase("35")); 
	cout << "------------erase 35------------" << endl;
	assert(m.size()==7);
	cout << m << endl;;
    
	
	assert(m.insert("16", "k"));
	assert(m.insert("18", "l"));
	assert(m.insert("17", "m"));
	cout << "------------insert 16-18------------" << endl;
    assert(m.size()==10);
    cout << m << endl;
   
	
	assert(m.erase("10")); 
	cout << "------------erase 10------------" << endl;
	assert(m.size()==9);
	cout << m << endl;
    
	assert(m.erase("5")); 
	cout << "------------erase 5------------" << endl;
    assert(m.size()==8);
    cout << m << endl;
    

    assert(m.erase("30")); 
	cout << "------------erase 30------------" << endl;
    assert(m.size()==7);
    cout << m << endl;
    
	
	assert(m.erase("25")); 
	cout << "------------erase 25------------" << endl;

    assert(m.size()==6);
    cout << m << endl;
   
	
	
	assert(m.erase("21")); 
	cout << "------------erase 21------------" << endl;

    assert(m.size()==5);
    cout << m << endl;
    
	
	assert(m.erase("18")); 
	cout << "------------erase 18------------" << endl;

    assert(m.size()==4);
    cout << m << endl;
    

    assert(m.erase("17")); 
	cout << "------------erase 17------------" << endl;
    assert(m.size()==3);
    cout << m << endl;
    
	
	assert(m.erase("16")); 
	cout << "------------erase 16------------" << endl;
    assert(m.size()==2);
    cout << m << endl;
    
	
	assert(m.erase("22")); 
	cout << "------------erase 22------------" << endl;
    assert(m.size()==1);
    cout << m << endl;
    

    assert(m.erase("23")); 
	cout << "------------erase 23------------" << endl;

    assert(m.size()==0);
    cout << m << endl;
	
	assert(m.erase("23")==false); 
	cout << "------------erase 23 again------------" << endl;
	cout << m << endl;
}





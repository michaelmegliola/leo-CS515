#include "skiplist.h"
#include <cassert>
using namespace std;

int main(){
    SkipList s(4, 0.5);
    srand(time(0));
    
    /*for (int i=0; i<50; i++){
        s.insert( rand() % 500 );
    }*/
    
    cout << "Test insert" << endl;
    s.insert(100);
    s.insert(150);
    s.insert(200);
    s.insert(240);
    s.insert(250);
    s.insert(255);
    s.insert(265);
    s.insert(275);
    s.insert(299);
    s.insert(520);
    
    cout << "test << operator" << endl;
    cout << s;
    
    cout << "Test find" << endl;
    assert(s.find(100)==true);
    assert(s.find(150)==true);
    assert(s.find(200)==true);
    assert(s.find(250)==true);
    assert(s.find(520)==true);
    assert(s.find(240)==true);
    assert(s.find(255)==true);
    assert(s.find(275)==true);
    assert(s.find(265)==true);
    assert(s.find(299)==true);
    assert(s.find(233)==false);
    assert(s.find(277)==false);
    assert(s.find(291)==false);

   
    cout << "Test erase" << endl;
    s.erase(100);
    assert(s.find(100)==false);
    s.erase(265);
    assert(s.find(265)==false);
    cout << s;
    
    cout << "Test copy constructor" << endl;
    SkipList newList = s;
    cout << "New list" << endl;
    cout << newList;
    cout << "Original list" << endl;
    cout << s;
    
    cout << "Modifying original list" << endl;
    s.insert(218);
    s.erase(250);
    s.erase(275);
    cout << "Original list" << endl;
    cout << s;
    
    cout << "Test assignment operator" << endl;
    s = newList;
    cout << "Original list" << endl;
    cout << s;
}

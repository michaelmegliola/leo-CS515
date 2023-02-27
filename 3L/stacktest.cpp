/* 
 * This test driver tests fixed sized stack implementation
 */

#include "stack.h"

int main(){
    stack s;
    
    assert(s.size()==0);
    assert(s.capacity()==8);
    assert(s.empty()==true);
    
    try {
        s.pop();
    } catch ( EmptyStackException e ){
        cout << "exception caught \n";
    }
    
    assert(s.size()==0);
    assert(s.capacity()==8);
    assert(s.empty()==true);

    s.push(2);
    s.push(4);
    s.push(6);
    s.push(8);
    s.push(10);
    s.push(12);
    assert(s.size()==6);
    assert(s.capacity()==8);
    assert(s.empty()==false);
    
   
    try {
        s.push(14);
        s.push(16);
        s.push(100);
    } catch ( FullStackException e ){
        cout << "exception caught \n";
    }
    
    assert(s.top()==16);
    s.pop();
    s.top()--; // modify top element
    assert(s.top()==13);
    s.pop();
    assert(s.size()==6);
    assert(s.capacity()==8);
    
    // testing copy constructor
    stack t(s);
    assert(t.size()==s.size());
    s.pop();
    assert(t.top()==12);
    assert(s.top()==10);
    
    s.pop();
    s.pop();
    
    // testing assignment operator
    t = s;
    assert(t.top()==6);
    
    try {
     s.pop();
     s.pop();
     s.pop();
     s.pop();
     s.pop();
     s.pop();
     s.pop();
    } catch  ( EmptyStackException e ){
        cout << "exception caught \n";
    }
}


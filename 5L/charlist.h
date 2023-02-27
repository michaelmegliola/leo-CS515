// A singly linked list implementation


#ifndef CHARLIST_H
#define CHARLIST_H
#include <iostream>
using namespace std;

class CharList {
public:
    // constructs empty list
    CharList() : head(0){}
    
    // copy constructor
    CharList(const CharList &v){
        copyCode(v);
    }
    
    // destructor
    ~CharList(){
        destructCode();
    }
    
    // assignment operator
    CharList& operator =(const CharList &v){
        if (this != &v) {
            destructCode();
            copyCode(v);
        }
        return *this;
    }
    
    // insert a char nod at the list front
    void insertFront(char);
    
    // insert a char node at the list back
    void insertRear(char);
    
    // convert to string
    string toStr();
    
private:
    struct Elem {
        char info;
        Elem *next;
    };
    // pointer to list head
    Elem *head;
    
    // common code for copy constructor and assignment
    void copyCode(const CharList & v);
    
    // common code for deallocation
    void destructCode();
    
friend  ostream& operator<<(ostream& out, CharList c);
};


#endif

// a set implemented with sorted doubly linked list with dummy header and tail nodes. 
// the set supports two iterators for set traversal. 
// set type is typedef as string 
//
// Feb, 2015 KJIN
// Edited Feb 2016 by mdp to better follow conventions

#ifndef SET_H
#define SET_H
#include <string>

using namespace std;
typedef string ELEMENT_TYPE;  // a set for string elements

class Set{
  public:
    //-----Constructors, destructors, and assignment-----
    Set(); // constructs empty set
    Set(const Set &rhs); // copy constructor
    ~Set();

    Set& operator=(const Set &rhs); // assignment operator

    //-----Basic operations-----
    // insert an element
    void insert(ELEMENT_TYPE);
    
    // remove an element from the set
    void erase(ELEMENT_TYPE);
    
    // remove all elements from set
    void clear();
    
    // return size of the set
    int size() const; 
    
    //-----Iterators-----
    class Iterator; //Forward-declaring so we can use the class now but define it later
    class Reverse_Iterator;
    // return an iterator to the element if val is found, or set::end() otherwise.
    Iterator find(ELEMENT_TYPE) const;
    
    // return an iterator pointing at the begining of the list
    Iterator begin() const;
    
    // return an iterator pointing at one element beyond the end of list
    Iterator end() const;
    
    // return an reverse iterator pointing at the reverse beginning of the list
    Reverse_Iterator rbegin() const;
    
    // return an reverse iterator pointing at one element beyond the beginning of list
    Reverse_Iterator rend() const;
    
    // friend top level function for output all list elements
    // elements are output as a single white space delimited 
    friend ostream& operator<< (ostream&, Set&);

  private:
    //---Forward-declare shared private structure---
    struct Elem;
    
  public:
    class Iterator{
      public:
        //-----Constructors-----
    	Iterator(); // construct a null iterator
        explicit Iterator(Elem *cur); // construct an iterator given pointer to Elem 
        
        //-----Overloaded operators-----
        ELEMENT_TYPE& operator*(); //dereference
        Iterator operator++(int); //post-increment operator
        Iterator operator--(int); //post-decrement operator
        bool operator==(Iterator it) const; // equality operator
        bool operator!=(Iterator it) const; // inequality operator
        
      private:
        Elem* _cur;
    };

    class Reverse_Iterator{
      public:
        //-----Constructors-----
    	Reverse_Iterator(); // construct a null iterator
        explicit Reverse_Iterator(Elem *cur); // construct an iterator given pointer to Elem 
        
        //-----Overloaded operators-----
        ELEMENT_TYPE& operator*(); //dereference
        Reverse_Iterator operator++(int); //post-increment operator
        Reverse_Iterator operator--(int); //post-decrement operator
        bool operator==(Reverse_Iterator it) const; // equality operator
        bool operator!=(Reverse_Iterator it) const; // inequality operator
        
      private:
        Elem* _cur;
    };
    
  private: //private members of Set
    struct Elem {
        ELEMENT_TYPE info;
        Elem *prev, *next;
    };
    
    // dummy header and tail nodes
    Elem *_head, *_tail;
    int _size;
    
    // common code for copy constructor and assignment
    void copyCode(const Set & v);
    
    // common code for deallocation
    void destructCode();
    
    // output set elements
    ostream& dump(ostream& out, const Set &v);
    
};

// set intersect and union
Set operator&(const Set&, const Set&);
Set operator|(const Set&, const Set&);

// set difference 
Set operator-(const Set&, const Set&);
// set equality
bool operator==(const Set& s1, const Set& s2);

#endif

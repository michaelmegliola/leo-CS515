// Set ADT implemented with a simple standard trie
// assume all keys are lower case alphabetic letters only


#ifndef SET_H
#define SET_H
#include <iostream>
#include <string>
#define ALPHABET_SIZE 26
using namespace std;

class Set{
    struct TrieNode{
      TrieNode *child[ALPHABET_SIZE]; // very space in-efficient 
      bool  isWord;
      TrieNode() : isWord(false){   // default constructor
          for(int i=0; i<ALPHABET_SIZE; i++)
              child[i]=0;
      }
      ~TrieNode() {
          for(int i=0; i<ALPHABET_SIZE; i++)
              delete child[i];
      }
    };
    
public:
    // constructs empty set
    Set();
    
    ~Set() { delete _root; }

    // insert a key into the set
    // return false if key already exists; otherwise insert new key and return true
    bool insert(string);
    
    // remove a key from the set
    // return false if the key doesn't exist; otherwise remove key and return true
    bool erase(string);
  
    // search for a key
    // return true if an element is found; false otherwise
    bool find(string);
    
     // return size of the set
    int size();
private:

    TrieNode * _root;
    int _size;
};

#endif

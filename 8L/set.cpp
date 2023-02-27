// Set ADT implemented with a simple standard trie
// assume all keys are lower case alphabetic letters only

#include "set.h"

Set::Set() {
    _root = new TrieNode();     //create root node
    _size = 0;
}


// insert a key into the set
// return false if key already exists; otherwise insert new key and return true
bool Set::insert(string key) {
    TrieNode* cur = _root;                      //start at the root
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';               //convert key to numeric index
        if (cur->child[index] == 0) {           //if child does not exist: create it
            cur->child[index] = new TrieNode();
        }
        cur = cur->child[index];                //continue to next node
    }
    if (cur->isWord)                            //key already exists: return false
        return false;
    else {
        cur->isWord = true;                     //mark key as a word
        _size++;                                //increment size, return true
        return true;
    }
}

// remove a key from the set
// return false if the key doesn't exist; otherwise remove key and return true
bool Set::erase(string key) {
    TrieNode *cur = _root;              //start at root
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (cur->child[index] == 0)     //if path does not exist, return false
            return false;
        cur = cur->child[index];        //next node
    }
    if (cur->isWord) {          //if path is a word
        cur->isWord = false;    //set to false
        _size--;                //decrement size
        return true;            //return true
    } else     //path is not a word, return false
        return false;
}

// search for a key
// return true if an element is found; false otherwise
bool Set::find(string key) {
    TrieNode* cur = _root;              //start at root
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (cur->child[index] == 0)     //if path does not exist, false
            return false;
        cur = cur->child[index];        //next node
    }
    return cur->isWord;                 //true if path is word, else false
}

// return size of the set
int Set::size() {
    return _size;
}

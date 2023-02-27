// the SkipList manages insertion, erase and find; it has two sentinal nodes (head and tail).
// the values inserted into the skiplist are between ( numeric_limits<int>::min(), numeric_limits<int>::max() )


#ifndef SKIP_LIST
#define SKIP_LIST
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
using namespace std; 

typedef int ELEMENT_TYPE;  // key is int type

class SkipList{
  public:
    SkipList(int, float = 0.5);
    SkipList(const SkipList&);
    ~SkipList();
    bool insert(ELEMENT_TYPE);
    bool erase(ELEMENT_TYPE);
    bool find(ELEMENT_TYPE);
    SkipList& operator=(const SkipList&);
    void output(); 
  private:
    struct SkipNode{
        SkipNode(ELEMENT_TYPE, int);
        ~SkipNode();
        SkipNode** nextNodes;
        int height;
        ELEMENT_TYPE info;
    };
    SkipNode * _head, * _tail;
    float _probability; //likelihood of a node getting taller at each level
    int _maxHeight; //maximum hieght a node can be
    int _curHeight; // height of the tallest node that's currently in the list
    int randomLevel();
    void copyCode(const SkipList&);
    void destructCode();
    ostream& dump(ostream&, const SkipList&) const;
friend ostream& operator<< (ostream&, const SkipList&);
    
};

#endif //SKIP_LIST


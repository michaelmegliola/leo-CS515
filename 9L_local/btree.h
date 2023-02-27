// A B-Tree for storing string data, the key is an int.

#include <iostream>
#include <string>
using namespace std;


// The BTreeNode class is an Abstract Base Class.  This means that no
// instance of the BTreeNode class can exist.  Only classes which
// inherit from the BTreeNode class may exist.  Furthermore, any class
// which inherits from the BTreeNode class MUST define the methods
// insert() and dump().  The indent() method does not have to
// be defined as it will be inherited in all subclasss of BTreeNode
class BTreeNode{
public:
    BTreeNode(): size(0) {}
    virtual BTreeNode *insert(int &newKey, string item) = 0;
    virtual void dump(int depth) = 0;
    void indent(int);

protected:
    static const int ORDER = 4; // order of the B-Tree is ORDER
    int keys[ORDER];  // need room for ORDER elements 
    int size;   
};

// BTree leaf node
// BLeaf is a subclass of BTreeNode. This means it inherit all public methods
// of BTreeNode and it can access all protected memebers of BTreeNode
// BLeaf provides the concrete implementation of insert() and dump() methods.
// A BLeaf object has a data array and an array of keys for locating the data;
// it does not keep reference to child nodes. (A leaf node has no children nodes)

class BLeaf : public BTreeNode{
private:
    string data[ORDER];  // data storage for ORDER elements

public:
     // define virtual methods from BTreeNode
    BTreeNode * insert(int &newKey, string item);
    void dump(int depth);
};

// BTree internal node
// BInternal is a subclass of BTreeNode. This means it inherit all public methods
// of BTreeNode and it can access all protected memebers of BTreeNode
// BInternal provides the concrete implementation of insert() and dump() methods.
// A BInternal node DOES NOT store data; it is only for indexing during BTree search.
// A BInternal node maintain a list of pointers and key values to its children nodes.
class BInternal : public BTreeNode{
private:
    BTreeNode * child[ORDER]; // pointers to subtrees

    friend class BTree;

public:
    // define virtual methods from BTreeNode
    BTreeNode * insert(int &newKey, string item);
    void dump(int depth);
};

// The BTree class
// The big four methods are omited.
// Can only insert into the Btree. Erase is not implemented.
class BTree {
private:
    BTreeNode * root;
public:
    BTree(){ root = new BLeaf();}
    void insert(int newKey, string item);
    void dump() {
        root->dump(0);
    }
};


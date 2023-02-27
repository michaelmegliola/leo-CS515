#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <string>
using namespace std;

struct HuffNode{
    // default constructor
    HuffNode(HuffNode* l = 0, HuffNode* r = 0, int f = 0, char d = '\0')
        : left(l), right(r), freq(f), data(d){}
    HuffNode * left, * right;  // two child node
    unsigned int freq; // freqency of the node
    char data;  // char value for leaf nodes; '\0' for internal nodes
    string code;  // Huffman code for leaf nodes; not assigned for internal nodes

    // do not change above code
    // you may add below here
    public:
        friend bool operator== (const HuffNode &n1, const HuffNode &n2);
        friend bool operator!= (const HuffNode &n1, const HuffNode &n2);
        friend bool operator> (const HuffNode &n1, const HuffNode &n2);
        friend bool operator>= (const HuffNode &n1, const HuffNode &n2);
        friend bool operator< (const HuffNode &n1, const HuffNode &n2);
        friend bool operator<= (const HuffNode &n1, const HuffNode &n2);
};

class HuffTree {
public:
    // get Huffman code and return it as a string
    string getCode(char);

    // build Huffman tree from an array of characters
    // and and an array of their corresponding freqencys;
    // the size of both arrays is given
    void buildTree(char *chs, int *freqs, int size);
    ~HuffTree();

private:
    HuffNode* _root; // root of the Huffman tree
    // do not change above code
    // you may add below here
    string _found;
    void find(HuffNode* p, char c);
    void encode(HuffNode* p, string s);
    void destructCode(HuffNode*);
};

#endif
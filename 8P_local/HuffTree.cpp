#include "HuffTree.h"
#include "PQueue.h"

/**
 * CS515 Assignment 8
 * File: HuffTree.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: Apr 8, 2021
 * Collaboration Declaration: none
 *  Assistance received from online resources
 *      Geeks for Geeks, C++ documents
 */

string HuffTree::getCode(char c) {
    _found = "";
    find(_root, c);     //find is recursive
    return _found;
}

void HuffTree::find(HuffNode* p, char c) {
    if (c == p->data)       //if found, save the encoded string
        _found = p->code;
    if (p->left != 0)       //look left
        find(p->left, c);
    if (p->right != 0)      //look right
        find(p->right, c);
}

void HuffTree::encode(HuffNode* p, string s) {
    if (p == nullptr)
        return;

    if (p->data != 0)   //if this is a leaf, save the string
        p->code = s;

    encode(p->left, s + "0");   //build string then recursive call
    encode(p->right, s + "1");
}

void HuffTree::buildTree(char * chs, int * freqs, int size) {
    PQueue<HuffNode, 28> pq;        //size is 28 because 26 alpha characters and two sentinels
    for (int i = 0; i < size; i++)  //insert nodes into priority queue
        pq.insert(HuffNode(0, 0, freqs[i], chs[i]));

    while (pq.size() > 1) {
        HuffNode temp1 = pq.findMin();       //pop first two elements off queue, combine them, then push
        pq.deleteMin();
        HuffNode temp2 = pq.findMin();
        pq.deleteMin();
        HuffNode* p1 = new HuffNode(temp1);
        HuffNode* p2 = new HuffNode(temp2);
        pq.insert(HuffNode(p1, p2, temp1.freq+temp2.freq));
    }

    _root = new HuffNode();                 //root is the only remaining element on queue
    *_root = pq.findMin();
    encode(_root, "");                   //put encoded strings into nodes
}

void HuffTree::destructCode(HuffNode* p) {
    if (p != nullptr) {                     //recursively delete all nodes in tree
        if (p->left != nullptr)
            destructCode(p->left);
        if (p->right != nullptr)
            destructCode(p->right);
        delete p;
    }
}

HuffTree::~HuffTree() {
    destructCode(_root);
}

bool operator== (const HuffNode &n1, const HuffNode &n2) {return n1.freq == n2.freq;}
bool operator!= (const HuffNode &n1, const HuffNode &n2) {return n1.freq != n2.freq;}
bool operator> (const HuffNode &n1, const HuffNode &n2) {return n1.freq > n2.freq;}
bool operator>= (const HuffNode &n1, const HuffNode &n2) {return n1.freq >= n2.freq;}
bool operator< (const HuffNode &n1, const HuffNode &n2) {return n1.freq < n2.freq;}
bool operator<= (const HuffNode &n1, const HuffNode &n2) {return n1.freq <= n2.freq;}


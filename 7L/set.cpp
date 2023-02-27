#include "set.h"
#include <stack>

Set::Set():_size(0){
    // create a dummy root node
    _root = new Elem;
    _root->info = numeric_limits<int>::max();
    _root->left = _root;  // empty tree
    _root->right = 0;
    _root->rightThread = false;
}

Set::~Set(){
    if (_root->left != _root)  // not an empty tree
        destructCode(_root->left);
    delete _root;
}

void Set::destructCode(Elem *& p){
    if (p->left != nullptr)                      //if there a left child, call destruct on it
        destructCode(p->left);
    if (!p->rightThread && p->right != nullptr)  //if there a right child, call destruct on it
        destructCode(p->right);
    delete p;                                    //delete current
}


// returns true if the new node is inserted, otherwise false
bool Set::insert(ELEMENT_TYPE v){
    if (insert(_root->left, v, _root)){
        _size++;
        return true;
    }
    return false;
}

// insert helper method
// returns true if the new node is inserted, otherwise false
bool Set::insert(Elem *&cur, const ELEMENT_TYPE &value, Elem *lastLeft){
    if (cur == _root || cur == 0) {
        cur = new Elem;
        cur->info = value;
        cur->left = 0;
        cur->right = lastLeft;
        cur->rightThread = true;
        return true;
    }

    if (value == cur->info){
        return false;
    }
    // insert at left
    if (value < cur->info)
        return insert( cur->left, value, cur);

    // insert at right
    if (!cur->rightThread){
        return insert(cur->right, value, lastLeft);
    } else {  // current's right is a thread; add a new node
        cur->rightThread = false;
        cur->right = new Elem;
        cur->right->info = value;
        cur->right->left = 0;
        cur->right->right = lastLeft;
        cur->right->rightThread = true;
        return true;
    }
}

// print out tree elements in depth first in order
void Set::depthFirstInOrder(){
    if (_size == 0)                         //set is empty
        return;

    std::stack<Elem*> s;                    //use stack in place of recursion
    Elem* cur = _root->left;                //start at root
    while (!s.empty() || cur != nullptr) {  //while there are still nodes
        while (cur != nullptr) {            //traverse left as far as possible
            s.push(cur);                    //push each element to stack
            cur = cur->left;
        }
        cur = s.top();                      //print top of stack
        cout << cur->info << " ";
        s.pop();
        cur = (cur->rightThread)? nullptr:cur->right;  //traverse right if there is a right child
    }
}

void Set::breadthFirst(){
    if (_size == 0)                 //set is empty
        return;

    queue<Elem*> q;                 //make empty queue to hold horizontal elements
    q.push(_root->left);            //first row is root
    while (!q.empty()) {            //while there are more nodes...
        Elem* cur = q.front();
        cout << cur->info << " ";   //print front element
        if (cur->left != nullptr)   //push the children on the next row
            q.push(cur->left);
        if (!(cur->rightThread) && cur->right != nullptr)
            q.push(cur->right);
        q.pop();                    //next element
    }
}

int Set::size() const{
    return _size;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Set::printTree(ostream& out, int level, Elem *p){
    int i;
    if (p) {
        if (p->right && !p->rightThread)
            printTree(out, level+1,p->right);
        for(i=0;i<level;i++)
            out << "\t";
        out << p->info << '\n';
        printTree(out, level+1,p->left);
    }
}

// outputs information in tree in inorder traversal order
ostream& Set::dump(ostream &out){
    if ( _root == _root->left) // tree empty
        return out;
    printTree(out, 0, _root->left);   // print tree structure
    return out;
}


// outputs using overloaded << operator
ostream& operator << (ostream &s, Set &v){
    v.dump(s);
    return s;
}

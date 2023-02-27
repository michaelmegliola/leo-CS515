/**
 * CS515 Lab 9
 * File: set.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: April 10, 2021
 * Collaboration Declaration:
 * Assistance received from online resources
 *   Geeks for Geeks
 */

//////////////////////////////////////
// Public functions
//////////////////////////////////////

template<typename T>
Set<T>::Set():_root(0), _size(0){}


template<typename T>
Set<T>::Set(const Set& rhs){
    _root = copyCode(rhs._root);
}

template<typename T>
Set<T>& Set<T>::operator=(const Set<T> &rhs){
    if(this != &rhs){
        destructCode(_root);
        _root = copyCode(rhs._root);
    }
    return *this;
}

template<typename T>
Set<T>::~Set(){
    destructCode(_root);
}

template<typename T>
int Set<T>::size() const{
    return _size;
}

template<typename T>
void Set<T>::insert(T x) {
    insert(x, _root);
}
 
// print tree "laying down"
template<typename T>
void Set<T>::printTree() const{
    printTree(0, _root);
}

// output the structure of tree. The tree is output as "lying down"
// in which root is the LEFT most node.
template<typename T>
void Set<T>::printTree(int level, Elem *node) const{
    int i;
    if (node) {
        printTree(level+1, node->right);
        for (i=0; i<level; i++)
            cout << "\t";
        cout << node->info << "(" << node->height << ")" << endl;
        printTree(level+1, node->left);
    }
}

// stand alone output function
// outputs using overloaded << operator
template<typename T>
ostream& operator<< (ostream& out, const Set<T>& v){
    v.printTree();
    return out;
}

//////////////////////////////
// Private Functions
//////////////////////////////

// helper method for recusively insertion
template<typename T>
void Set<T>::insert(T x, Elem *& node) {
    if (node == 0){ // insert here
        node = new Elem(x, 0, 0);
        _size++;
    }
    // move to left
    else if (x < node->info) {
        insert(x, node->left);
    }
    // move to right
    else if (x > node->info) {
        insert(x, node->right);
    }
    
    if (height(node->left) - height(node->right) == 2) { // calculate load factor
        if(x < node->left->info) // outside case
            rotateRight(node);
        else  // inside case
            doubleRotateRight(node);
    }
    
    if (height(node->left) - height(node->right) == -2) { // calculate load factor
        if (x > node->right->info) // outside case
            rotateLeft(node);
        else  // inside case
            doubleRotateLeft(node);
    }
    node->height = max(height(node->left), height(node->right)) + 1; // update height
}
 
template<typename T>
int Set<T>::height(Elem *node) {
    return node == 0 ? -1 : node->height;
}

// return the address of the minimum node in the tree
template<typename T>
typename Set<T>::Elem* Set<T>::findMin(Elem *node) {
    if (node == 0)
        return node;
    while (node->left)  // move to the leftmost node
        node = node->left;
    return node;
}


// common copy code for copying a tree recursively
template<typename T>
typename Set<T>::Elem* Set<T>::copyCode(Set<T>::Elem *node){
    if (node)
        return new Elem(node->info, copyCode(node->left), copyCode(node->right), node->height);
    else
        return 0;
}

// common destruct code for deallocation and make an empty tree
template<typename T>
void Set<T>::destructCode(Elem *& node){
    if (node){
        destructCode(node->left);
        destructCode(node->right);
        delete node;
    }
    node = 0;
}
 
// single right rotation
template<typename T>
void Set<T>::rotateRight(Elem *& node) {
    Elem* beta = node->left;   //store beta
    node->left = beta->right;  //rotate right
    beta->right = node;
    node = beta;               //replace node with beta
    beta->right->height--;
    beta->height = max(height(beta->left), height(beta->right)) + 1; // update height
}

// single left rotation
template<typename T>
void Set<T>::rotateLeft(Elem *& node){
    Elem* beta = node->right;   //store beta
    node->right = beta->left;   //rotate left
    beta->left = node;
    node = beta;                //replace node with beta
    beta->left->height--;
    beta->height = max(height(beta->left), height(beta->right)) + 1; // update height
}

// double right rotation
template<typename T>
void Set<T>::doubleRotateRight(Elem *& node) {
    rotateLeft(node->left);    //rotate left on left child
    rotateRight(node);         //then rotate right
}

// double left rotation
template<typename T>
void Set<T>::doubleRotateLeft(Elem *& node) {
    rotateRight(node->right);  //rotate right on right child
    rotateLeft(node);          //then rotate left
}

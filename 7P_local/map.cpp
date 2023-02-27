// A non-generic Map ADT implemented with a BST data structure
// The BST is not-balanced and non-threaded
#include "map.h"

Map::Map(){
    // create a dummy root node and set up an empty tree
    _root = new Elem;
    _root->left = _root;
    _root->right = 0;
    _size = 0;

}

Map::~Map() {
    if (size() != 0)
        destructCode(_root->left);
    delete _root;
}

// common code for deallocation
void Map::destructCode(Elem *& p) {     //recursive: call on any children then delete this
    if (p->left != nullptr)
        destructCode(p->left);
    if (p->right != nullptr)
        destructCode(p->right);
    delete p;
}

// copy constructor
Map::Map(const Map &v){
    // if empty tree
    if (v._root == v._root->left){
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _size = 0;
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        copyCode(_root->left, v._root->left);
        _size = v._size;
    }
}

// common copy code for deep copy a tree
void Map::copyCode(Elem* &newRoot, Elem* origRoot){
    newRoot = new Elem;
    newRoot->key = origRoot->key;
    newRoot->data = origRoot->data;
    if (origRoot->left == nullptr)
        newRoot->left = nullptr;
    else
        copyCode(newRoot->left, origRoot->left);
    if (origRoot->right == nullptr)
        newRoot->right = nullptr;
    else
        copyCode(newRoot->right, origRoot->right);
}

// assignment operator
Map& Map::operator=(const Map &rhs) {
    if (size() == 0) {
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _size = 0;
    } else {
        destructCode(_root->left);
        copyCode(_root->left, rhs._root->left);
    }
    return *this;
}

Map::Elem& Map::Iterator::operator*() {
    return *_cur;
}

Map::Elem* Map::Iterator::operator->() {
    return _cur;
}

bool Map::Iterator::operator==(Iterator it) const {
    return _cur == it._cur;
}

bool Map::Iterator::operator!=(Iterator it) const {
    return _cur != it._cur;
}

Map::Iterator Map::find(KEY_TYPE key) const {
    Elem* p = _root->left;
    while (p != nullptr) {
        if (key < p->key)
            p = p->left;
        else if (key > p->key)
            p = p->right;
        else
            break;
    }
    return Map::Iterator(p);
}

Map::Iterator Map::begin() const {
    if (size() == 0)
        return Map::Iterator(nullptr);
    else
        return Map::Iterator(_root->left);
}

Map::Iterator Map::end() const {
    return Map::Iterator(nullptr);
}

// insert an element; return true if successful
bool Map::insert(KEY_TYPE k, VALUE_TYPE v) {
    if (size() == 0) {          //p is the first element
        Elem* p = new Elem();   //construct elem at root->left
        p->key = k;
        p->data = v;
        _root->left = p;
        _size++;
        return true;
    } else {                            //there are already elements in the map
        Elem* cur = _root->left;
        while (true) {
            if (k == cur->key) {        //key already exists
                cur->data = v;
                return false;
            } else if (k < cur->key && cur->left == nullptr) {   //key's location is not populated (left)
                Elem* p = new Elem();   //construct elem
                p->key = k;
                p->data = v;
                cur->left = p;
                _size++;
                return true;
            } else if (k > cur->key && cur->right == nullptr) {   //key's location is not populated (right)
                Elem* p = new Elem();   //construct elem
                p->key = k;
                p->data = v;
                cur->right = p;
                _size++;
                return true;
            }

            if (k < cur->key)         //move cur right or left according to key
                cur = cur->left;
            else if (k > cur->key)
                cur = cur->right;
        }
    }
}

bool Map::erase(KEY_TYPE key) {
    if (size() == 0)
        return false;
    Elem* cur = _root->left;
    Elem** p = &_root->left;
    while (cur != nullptr) {
        if (key < cur->key) {                                   //look to the left
            p = &cur->left;
            cur = cur->left;
        } else if (key > cur->key) {                            //look to the right
            p = &cur->right;
            cur = cur->right;
        } else if (cur->key == key) {                           //found the key
            if (cur->left == nullptr && cur->right == nullptr)
                *p = nullptr;
            else if (cur->right == nullptr)
                *p = cur->left;
            else if (cur->left == nullptr)
                *p = cur->right;
            else {
                Elem* right_min = cur->right;
                p = &cur->right;
                while (right_min->left != nullptr) {
                    p = &right_min->left;
                    right_min = right_min->left;
                }
                cur->key = right_min->key;
                cur->data = right_min->data;
                cur = right_min;
                *p = nullptr;
            }
            break;
        }
    }
    if (cur != nullptr) {           // delete the element
        delete cur;
        _size--;
        if (_size == 0)
            _root->left = _root;    // if empty, restore the root
        return true;
    } else
        return false;
}

VALUE_TYPE& Map::operator[](KEY_TYPE key) {
    Iterator it = find(key);
    if (it == end()) {
        insert(key, "");
        it = find(key);
    }
    return it->data;
}

// return size of the Map
int Map::size() const {
    return _size;
}

//
//  Do Not Modify Below Here
//
//
// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Map::printTree(ostream& out, int level, Elem *p) const{
    int i;
    if (p) {
        printTree(out, level+1, p->right);
        for(i=0;i<level;i++) {
            out << "\t";
        }
        out << p->key << " " << p->data << '\n';
        printTree(out, level+1, p->left);
    }
}

// outputs information in tree
ostream& Map::dump(ostream& out) const{
    if ( _root == _root->left) { // tree empty
        return out;
    }
    printTree(out, 0, _root->left);   // print tree structure
    return out;
}

// outputs using overloaded << operator
ostream& operator<< (ostream& out, const Map& v){
    v.dump(out);
    return out;
}

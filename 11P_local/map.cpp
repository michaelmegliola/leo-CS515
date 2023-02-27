// A generic Map implemented with right-threaded AVL

#include <map> // helper container for thread copying

/**
 * CS515 Program 11
 * File: map.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: Apr 29, 2021
 * Collaboration Declaration: none
 *  Assistance received from online resources:
 *      Geeks for Geeks, Tutorials Point
 */

template <typename KEY, typename T>
Map<KEY, T>::Map(){
    // create a dummy root node
    _root = new Elem;
    _root->left = nullptr;
    _root->right = 0;
    _root->rightThread = false;
    _size = 0;
    _threaded = false;
}

// copy constructor
template <typename KEY, typename T>
Map<KEY, T>::Map(const Map<KEY,T> &v){
    // if empty tree
    if (v._root == v._root->left){
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _size = 0;
        _threaded = false;
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes
        _threaded = false;
        rethread(_root);
        _size = v._size;
    }
}

template <typename KEY, typename T>
Map<KEY,T>& Map<KEY,T>::operator=(const Map &rhs) {
    if (rhs.size() == 0) {
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _size = 0;
        _threaded = false;
    } else {
        if (_root->left && _root->left != _root)
            destructCode(_root->left);
        copyCode(_root->left, rhs._root->left);
        _threaded = false;
        rethread(_root);
        _size = rhs.size();
    }
    return *this;
}

template <typename KEY, typename T>
Map<KEY,T>::~Map() {
    if (size() != 0) {
        remove_threading(_root->left);
        if (_root->left != _root)
            destructCode(_root->left);
    }
    delete _root;
}

template <typename KEY, typename T>
void Map<KEY,T>::destructCode(Elem *& p) {
    if (p->left != nullptr && p->left != _root)
        destructCode(p->left);
    if (p->right != nullptr && !p->rightThread)
        destructCode(p->right);
    delete p;
}

// construct a key-element map to rethread the new tree
// the map contains all nodes key values and their corresonding elem node address
// for furture lookup in setting up threads
template <typename KEY, typename T>
void Map<KEY, T>::addToMap(Elem* root, map<KEY, Elem*> &keyElemMap){
	if (root) {
		keyElemMap[root->key] = root;
		addToMap(root->left, keyElemMap);
		if (!root->rightThread)
			addToMap(root->right, keyElemMap);
	}
}

// common copy code for thread copying
template <typename KEY, typename T>
void Map<KEY, T>::copyThread(Elem* &newRoot, Elem* origRoot){
	// construct the key-element map for new and orig tree
	map<KEY, Elem*> newKeyElemMap;
	map<KEY, Elem*> origKeyElemMap;
	addToMap(newRoot->left, newKeyElemMap);
	addToMap(origRoot->left, origKeyElemMap);

	// start at the last element in the tree, which threads to root
	typename std::map<KEY, Elem*>::reverse_iterator it = origKeyElemMap.rbegin();
	newKeyElemMap[it->first] -> rightThread = true;
	newKeyElemMap[it->first] -> right = newRoot;

	// then thread the rest of the tree backwardly
	it++;
	while(it != origKeyElemMap.rend()){
		if (it->second->rightThread){
			newKeyElemMap[it->first] -> rightThread = true;
			newKeyElemMap[it->first] -> right = newKeyElemMap[ origKeyElemMap[it->first]->right->key ];
		}
		it++;
	}
}

// common copy code for deep copy a tree without copying threads
template <typename KEY, typename T>
void Map<KEY,T>::copyCode(Elem* &newRoot, Elem* origRoot){
	if (origRoot == 0)
		newRoot = 0;
	else{
		newRoot = new Elem;
		newRoot->key = origRoot->key;
		newRoot->data = origRoot->data;
		newRoot->rightThread = origRoot->rightThread;
		copyCode(newRoot->left, origRoot->left);
		if (!origRoot->rightThread)
			copyCode(newRoot->right, origRoot->right);
	}
}

template <typename KEY, typename T>
int Map<KEY, T>::height(Elem* p) {
    return p == nullptr ? 0 : p->height;
}

template <typename KEY, typename T>
int Map<KEY, T>::balance(Elem* p) {
    return p == nullptr ? 0 : height(p->left) - height(p->right);
}

template <typename KEY, typename T>
int Map<KEY, T>::max_child_height(Map<KEY, T>::Elem* p) {
    int left = height(p->left);
    int right = height(p->right);
    return left > right ? left : right;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::rotate_left(Elem* a) {
    Elem* b = a->right;
    Elem* subtree = b->left;
    b->left = a;
    a->right = subtree;
    a->height = max_child_height(a)+1;
    b->height = max_child_height(b)+1;
    return b;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::rotate_right(Elem* c) {
    Elem* b = c->left;
    Elem* subtree = b->right;
    b->right = c;
    c->left = subtree;
    c->height = max_child_height(c)+1;
    b->height = max_child_height(b)+1;
    return b;
}

template <typename KEY, typename T>
bool Map<KEY, T>::insert(KEY k, T v) {
    bool return_val = true;
    _root->left = insert(_root->left, k, v, &return_val);
    _threaded = false;
    return return_val;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::insert(Elem* root, const KEY &k, const T &v, bool* return_val) {
    if (root == nullptr) {
        Elem* p = new Elem();
        p->key = k;
        p->data = v;
        p->height = 1;
        p->left = nullptr;
        p->right = nullptr;
        p->rightThread = false;
        _size++;
        return p;
    }

    if (root->rightThread) {
        root->right = nullptr;
        root->rightThread = false;
    }

    if (k < root->key)
        root->left = insert(root->left, k, v, return_val);
    else if (k > root->key)
        root->right = insert(root->right, k, v, return_val);
    else {
        *return_val = false;
        root->data = v;
        return root; //the keys are equal
    }

    root->height = max_child_height(root)+1;

    int bal = balance(root);
    if (bal > 1 && k < root->left->key)
        return rotate_right(root);
    else if (bal > 1 && k > root->left->key) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    else if (bal < -1 && k > root->right->key)
        return rotate_left(root);
    else if (bal < -1 && k < root->right->key) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    } else
        return root;
}

template <typename KEY, typename T>
void Map<KEY, T>::rethread(Elem* root) {
    if (_threaded)
        return;
    if (_size > 0) {
        remove_threading(root);
        thread(root);
        Elem *max = root;
        while (max->right) //thread right-most element back to sentinel
            max = max->right;
        max->rightThread = true;
        max->right = _root;
    }
    _threaded = true;
}

template <typename KEY, typename T>
void Map<KEY, T>::thread(Elem* root) {
    if (!root) {return;} //return if root is null

    if (root->left) {
        Elem* left_max = root->left;
        while (left_max && left_max->right && !left_max->rightThread)
            left_max = left_max->right;

        left_max->right = root;
        left_max->rightThread = true;
    }
    thread(root->left);
    if (!root->rightThread)
        thread(root->right);
}

template <typename KEY, typename T>
void Map<KEY, T>::remove_threading(Elem* root) {
    if (!root)
        return;
    if (root->rightThread) {    //remove all threading from the tree
        root->right = nullptr;
        root->rightThread = false;
    }
    remove_threading(root->left);
    if (!root->rightThread)
        remove_threading(root->right);
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() {  // return the left most (smallest) tree node
    rethread(_root);
    if (size() == 0)
        return end();
    else {
        Elem* p = _root->left;
        while (p->left)
            p = p->left;
        return Iterator(p, _root);
    }
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const {  // return the dummy root node
	return Iterator(_root, _root);
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int) {
    if (_cur != _end && _cur->rightThread)
        _cur = _cur->right;
    else {
        if (_cur == _end || _cur->right == _end)
            _cur = _end;
        else {
            Elem *right_min = _cur->right;
            while (right_min->left != nullptr)
                right_min = right_min->left;
            _cur = right_min;
        }
    }
	return *this;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem& Map<KEY, T>::Iterator::operator*(){
	return *_cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::Iterator::operator->(){
	return _cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator==(Iterator it){
    return _cur == it._cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator!=(Iterator it){
    return _cur != it._cur;
}

template <typename KEY, typename T>
int Map<KEY, T>::size() const{
	return _size;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		if (p->right && !p->rightThread)
			printTree(out, level+1,p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << '\n';
		printTree(out, level+1,p->left);
	}
}

// outputs information in tree in inorder traversal order
template <typename KEY, typename T>
ostream& Map<KEY, T>::dump(ostream& out) const{
	if ( _root == _root->left) {// tree empty
		return out;
	}
	printTree(out, 0, _root->left);   // print tree structure
	return out;
}

template<typename KEY, typename T>
T& Map<KEY, T>::operator[](KEY key) {
    Iterator it = find(key);
    if (it == end()) {
        insert(key, T());
        it = find(key);
    }
    return it->data;
}

template<typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::find(KEY key) const {
    Elem* p = _root->left;
    while (p != nullptr) {
        if (p->key == key)
            break;
        else if (p->left && key < p->key)
            p = p->left;
        else if (p->right && !p->rightThread && key > p->key)
            p = p->right;
        else
            p = nullptr;
    }
    if (p == nullptr)
        return end();
    else
        return Iterator(p, _root);
}

// outputs using overloaded << operator
template<typename KEY, typename T>
ostream& operator<< (ostream& out, const Map<KEY, T>& v){
	v.dump(out);
	return out;
}

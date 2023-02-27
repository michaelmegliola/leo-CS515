// A generic Map implemented with right-threaded BST
// BST is not balanced

#include <map> // helper container for thread copying
#include <cassert>

template <typename KEY, typename T>
Map<KEY, T>::Map(){
    // create a dummy root node
    _root = new Elem;
    _root->left = _root;  // empty tree
    _root->right = 0;
    _root->rightThread = false;
    _size = 0;
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
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes
        copyThread(_root, v._root); // to copy the threading; must pass dummy nodes to complete the threads
        _size = v._size;
    }
}

template <typename KEY, typename T>
Map<KEY,T>::~Map() {
    if (size() != 0)
        destructCode(_root->left);
    delete _root;
}

template <typename KEY, typename T>
Map<KEY,T>& Map<KEY,T>::operator=(const Map &rhs) {
    if (rhs.size() == 0) {
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _size = 0;
    } else {
        if (_root->left != _root)
            destructCode(_root->left);
        copyCode(_root->left, rhs._root->left);
        copyThread(_root, rhs._root);
        _size = rhs.size();
    }
    return *this;
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
void  Map<KEY,T>::copyCode(Elem* &newRoot, Elem* origRoot){
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
bool Map<KEY, T>::insert(KEY k, T v) {
    if (size() == 0) {          //p is the first element
        Elem* p = new Elem();   //construct elem at root->left
        p->key = k;
        p->data = v;
        p->left = nullptr; p->right = nullptr; p->rightThread = false;
        _root->left = p;
        _size++;
        return true;
    } else                   //there are already elements in the map
        return insert(_root->left, k, v, nullptr);
}

template <typename KEY, typename T>
bool Map<KEY, T>::insert(Elem *& root, const KEY &k, const T &v, Elem *lastLeft) {

    if (root->key == k) {  //the key already exists
        root->data = v;
        return false;
    }
    else if (k > root->key) {          //go to the right
        if (root->right == nullptr || root->rightThread) {
            Elem *p = new Elem();      //construct elem
            p->key = k;
            p->data = v;
            p->left = nullptr; p->right = nullptr; p->rightThread = false;
            root->right = p;
            root->rightThread = false;
            _size++;

            if (lastLeft != nullptr) { //thread node to lastLeft
                p->right = lastLeft;
                p->rightThread = true;
            }
            return true;
        } else
            return insert(root->right, k, v, lastLeft);
    } else {                        //go to the left
        if (root->left == nullptr) {
            Elem *p = new Elem();   //construct elem
            p->left = nullptr;
            p->key = k;
            p->data = v;
            root->left = p;
            _size++;

            p->right = root;        //thread node to parent
            p->rightThread = true;
            return true;
        } else
            return insert(root->left, k, v, root);  //root is now lastLeft
    }
}

template <typename KEY, typename T>
bool Map<KEY, T>::erase(KEY key) {
    Iterator it = find(key);    //find the element to be deleted
    if (it == end())
        return false;

    Iterator pred = begin();    //find the predecessor (for use in maintaining threads)
    Elem* predecessor = _root;
    while (pred != it) {
        predecessor = &*pred;
        pred++;
    }

    it++;                       //find the successor (for use in maintaining threads)
    Elem* successor = &*it;
    bool skip = false;

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
            if (cur->left == nullptr && (cur->right == nullptr || cur->rightThread)) //no children
                *p = nullptr;
            else if (cur->right == nullptr || cur->rightThread)                      //left child only
                *p = cur->left;
            else if (cur->left == nullptr && !cur->rightThread)                      //right child only
                *p = cur->right;
            else {                                                                   //two children
                skip = true;                           //in the two child case, skip using predecessor
                Elem* right_min = cur->right;          //find successor (right min is successor)
                Elem* right_min_parent = cur;
                while (right_min->left != nullptr) {
                    right_min_parent = right_min;
                    right_min = right_min->left;
                }

                if (right_min_parent == cur) {      //right min is immediate child
                    right_min_parent->right = right_min->right;
                    right_min_parent->rightThread = right_min->rightThread;  //maintain thread
                }
                else {
                    if (!right_min->rightThread) //right min is to the left of right child}
                        right_min_parent->left = right_min->right;
                    else
                        right_min_parent->left = nullptr;
                }

                cur->key = right_min->key;
                cur->data = right_min->data;
                cur = right_min;
            }
            break;
        }
    }

    if (!skip && predecessor != _root) { //for case except two child case, maintain thread here
        if (predecessor->rightThread || predecessor->right == nullptr) {
            if (successor == nullptr) {
                predecessor->right = nullptr;
                predecessor->rightThread = false;
            }
            else {
                predecessor->right = &*successor; //thread predecessor to successor
                predecessor->rightThread = true;
            }
        }
        else
            predecessor->rightThread = false;
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

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() const {  // return the left most (smallest) tree node
    if (size() == 0)
        return Iterator(nullptr);
    else {
        Elem* p = _root->left;
        while (p->left != nullptr)
            p = p->left;
        return Iterator(p);
    }
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const {  // return the dummy root node
	return Iterator(nullptr);
} 

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int) {
    if (_cur != nullptr) {
        if (_cur != nullptr && _cur->rightThread) //if threaded, successor is right pointer
            _cur = _cur->right;
        else {
            if (_cur->right == nullptr)
                _cur = nullptr;
            else {
                Elem *right_min = _cur->right;    //else successor is right min
                while (right_min->left != nullptr)
                    right_min = right_min->left;
                _cur = right_min;
            }
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
    Iterator it = begin();
    while (it != end()) {
        if (it->key == key)
            return it;
        it++;
    }
    return it;
}

// outputs using overloaded << operator
template<typename KEY, typename T>
ostream& operator<< (ostream& out, const Map<KEY, T>& v){
	v.dump(out);
	return out;
}

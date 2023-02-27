#include "skiplist.h"

// construct a new skipnode with given key and height
SkipList::SkipNode::SkipNode( ELEMENT_TYPE in, int h ) : info(in), height(h){
    nextNodes = new SkipNode* [h+1]; // height 0 un-used
    for ( int x = 1; x <= height; x++ ){
        nextNodes[x] = 0;
    }
}

// SkipNode dustructor
SkipList::SkipNode::~SkipNode(){
    delete [] nextNodes;
}

// SkipList constructor: construct an empty skiplist of max height m and and probability p with default value 0.5
// current height initialize to 1
SkipList::SkipList(int m, float p) : _curHeight(1), _maxHeight(m), _probability(p){
    // Create head with intMin and tail with intMax;
    int intMin = numeric_limits<int>::min(); // minimum int value
    int intMax = numeric_limits<int>::max(); // maximum int value
    _head = new SkipNode(intMin, _maxHeight);   //
    _tail = new SkipNode(intMax, _maxHeight);
    // attach them to form an empty list
    for ( int x = 1; x <= _maxHeight; x++ ){
        _head->nextNodes[x] = _tail;
    }
    srand(time(0));
}

// copy constructor
SkipList::SkipList(const SkipList& v): _probability(v._probability), _maxHeight(v._maxHeight), _curHeight(v._curHeight){
    copyCode(v);
}

// overloaded operator assignment
SkipList& SkipList::operator=(const SkipList &rhs){
    if (this != &rhs) {
        destructCode();
        copyCode(rhs);
    }
    return *this;
}

// commom code for destruction
void SkipList::destructCode(){
    // Walk bottom level nodes and delete all
    SkipNode * cur;
    cur = _head;
    while ( _head->nextNodes[1] != _tail ){
        _head = _head->nextNodes[1];
        delete cur;
        cur = _head;
    }
    delete _head;
    delete _tail;
}

// destructor
SkipList::~SkipList(){
    destructCode();
}

// Returns a random height between 1 and maximum node height.
int SkipList::randomLevel(){
    int level = 1;
    // (double)rand()/RAND_MAX return a random number between (0, 1)
    while ( ((double)rand()/RAND_MAX < _probability) && (level < _maxHeight))
        level++;
    return level;

    //for testing/debugging; produces deterministic node heights.
    //static int i = 0;
    //int level[10] = {4,1,2,1,4,1,2,1,4,1};
    //return level[i++];
}

// insert a node key into the skiplist, return false if key already exists
// otherwise insert key and return true.
bool SkipList::insert( ELEMENT_TYPE info ) {
    // pointer array to keep track of the next nodes at the insertion point
    SkipNode **lookBack = new SkipNode *[_maxHeight + 1];
    SkipNode *cur = _head;
    bool result = true;
    int curInfo;
    // find where new node goes
    for (int i = 0; i < _maxHeight+1; i++)
        lookBack[i] = nullptr;
    for (int h = _curHeight; h >= 1; h--) {
        curInfo = cur->nextNodes[h]->info;
        while (curInfo < info) {
            cur = cur->nextNodes[h];
            curInfo = cur->nextNodes[h]->info;
        }
        lookBack[h] = cur; // keep track of previous node
    }
    cur = cur->nextNodes[1]; // move to next node at level 1
    curInfo = cur->info;

    // If dup, return false
    if (curInfo == info) {
        result = false;
    } else { // Perform an insert
        // FILL IN HERE (using comments to help guide you)
        // get the random height for the new node (call randomLevel)
        int height = randomLevel();
        // prepare insertion point
        SkipNode *p = new SkipNode(info, height);
        // (check if node has higher level than _curHeight, fix lookBack & _curHeight as needed)
        _curHeight = height > _curHeight ? height : _curHeight;
        // Insert new element
        for (int n = 1; n <= height; n++) {
            if (lookBack[n] == nullptr) {
                p->nextNodes[n] = _tail;
                _head->nextNodes[n] = p;
            }
            else {
                p->nextNodes[n] = lookBack[n]->nextNodes[n];
                lookBack[n]->nextNodes[n] = p;
            }
        }
    }
    delete[] lookBack;
    return result;
}

// return ture if the key is found, otherwise false
    bool SkipList::find(ELEMENT_TYPE info){
        int curInfo = 0;
        SkipNode* cur = _head;
        // find starts at top level
        for ( int h = _curHeight; h >= 1; h-- ){
            curInfo = cur->nextNodes[h]->info;
            while ( curInfo < info ){   // remain the current level before move down a level
                cur = cur->nextNodes[h];
                curInfo = cur->nextNodes[h]->info;
            }
        }

        return (curInfo == info);
    }

// erase a node key from the skiplist, return false if key does not exist
// otherwise erase key and return true.
    bool SkipList::erase( ELEMENT_TYPE info ){
        SkipNode **lookBack = new SkipNode *[_maxHeight + 1];
        SkipNode *cur = _head;
        int curInfo;
        // find where new node goes
        for (int i = 0; i < _maxHeight+1; i++)
            lookBack[i] = nullptr;
        for (int h = _curHeight; h >= 1; h--) {
            curInfo = cur->nextNodes[h]->info;
            while (curInfo < info) {
                cur = cur->nextNodes[h];
                curInfo = cur->nextNodes[h]->info;
            }
            lookBack[h] = cur; // keep track of previous node
        }
        cur = cur->nextNodes[1]; // move to next node at level 1
        curInfo = cur->info;

        if (curInfo != info) {//element was not found
            delete[] lookBack;
            return false;
        }

        for (int n = 1; n <= cur->height; n++)
            lookBack[n]->nextNodes[n] = cur->nextNodes[n];

        delete cur;
        delete[] lookBack;
        return true;
    }


// common copy code
    void SkipList::copyCode(const SkipList &v){
        int intMin = numeric_limits<int>::min(); // minimum int value
        int intMax = numeric_limits<int>::max(); // maximum int value
        _head = new SkipNode(intMin, _maxHeight);   //
        _tail = new SkipNode(intMax, _maxHeight);

        for (int x = 1; x <= _maxHeight; x++){
            _head->nextNodes[x] = _tail;
        }

        SkipNode ** lookBack = new SkipNode * [_maxHeight+1];
        for (int x = 1; x <= _maxHeight; x++){
            lookBack[x] = _head;
        }

        // copy elements
        SkipNode* cur = v._head->nextNodes[1];
        while(cur != v._tail){
            // create a new node
            SkipNode* add = new SkipNode(cur->info, cur->height);
            for ( int x = 1; x <= cur->height; x++ ){
                // set add's nextnodes to lookback's next
                add->nextNodes[x] = lookBack[x]->nextNodes[x];
                // set lookback's nextnodes to add
                lookBack[x]->nextNodes[x] = add;
                // update lookback
                lookBack[x] = add;
            }
            cur = cur->nextNodes[1];
        }
        delete[] lookBack;
    }

// output skiplist with all levels to standard out
    void SkipList::output(){
        SkipNode * tmp = _head -> nextNodes[1];
        while ( tmp != _tail ){
            for ( int h = 1; h <= tmp->height; h++ )
                cout << tmp->info << '\t';
            cout << endl;
            tmp = tmp->nextNodes[1];
        }
    }

// helper method to output skiplist
    ostream& SkipList::dump(ostream& os, const SkipList &v) const{
        SkipNode * cur = v._head -> nextNodes[1];
        while ( cur != v._tail ){
            for ( int h = 1; h <= cur->height; h++ )
                os << cur->info << '\t';
            os << endl;
            cur = cur->nextNodes[1];
        }
        return os;
    }

// overloaded output operator
    ostream& operator<< ( ostream& out, const SkipList &v ){
        return v.dump(out, v);
    }
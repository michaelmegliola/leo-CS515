// Below are the stubs for SOME methods
// Make sure all methods in unorderedmap.h are implemented

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(){
    tablesize = 101;
    array = allocate(tablesize);
    entrysize = 0;
    end_entry = new Entry();  //entry to prevent end() from returing a null pointer
}

template<typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(const UnorderedMap& rhs) {
    tablesize = rhs.tablesize;    //copy from rhs
    array = allocate(tablesize);
    entrysize = rhs.entrysize;
    end_entry = new Entry();
    copycode(rhs);
}

template<typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::UnorderedMap& UnorderedMap<KEY, T, H>::operator=(const UnorderedMap& rhs) {
    deletecode();                 //delete existing entries
    delete end_entry;
    tablesize = rhs.tablesize;    //copy from rhs
    array = allocate(tablesize);
    entrysize = rhs.entrysize;
    end_entry = new Entry();
    copycode(rhs);
    return *this;
}

template<typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::copycode(const UnorderedMap& rhs) { //common copy code
    for (int i = 0; i < tablesize; i++) { //traverse table looking for entries
        if (rhs.array[i]) {               //if an entry is found, copy entire linked list
            Entry* p = new Entry();
            array[i] = p;
            p->key = rhs.array[i]->key;
            p->data = rhs.array[i]->data;
            p->next = nullptr;
            Entry* next = rhs.array[i]->next;
            while (next) {                //copy children of top entry
                p->next = new Entry();
                p->next->key = next->key;
                p->next->data = next->data;
                next = next->next;
            }
        }
    }
}

template<typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry** UnorderedMap<KEY, T, H>::allocate(int size) { //common code to allocate table of pointers
    Entry** p = new Entry*[size];  //allocate
    for (int i=0; i<size; i++)     //initialize
        p[i] = nullptr;
    return p;
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::~UnorderedMap(){
    deletecode();
    delete end_entry;
}

template<typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::deletecode() {  //common code to delete entries, then table
    for (int i=0; i<tablesize; i++)           //traverse table
        if (array[i] != nullptr) {
            Entry* p = array[i];              //delete entire linked list
            while (p) {
                Entry* temp = p;
                p = p->next;
                delete temp;
            }
        }
    delete[] array;                           //delete table
    array = nullptr;
}

template <typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::insert(Entry* entry, Entry** target_arr, int size) {
    std::size_t key = H()(entry->key);
    int hashcode = (int) (key % (std::size_t) size);

    if (!target_arr[hashcode])
        target_arr[hashcode] = entry;          //top entry goes directly into table
    else {
        Entry* p = target_arr[hashcode];       //children go at end of linked list
        while (p) {
            if (!p->next) break;
            p = p->next;
        }
        p->next = entry;
    }
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::insert(const KEY & newkey, const T & data) {
    Iterator it = find(newkey);  //if key exists, copy new data into existing entry
    if (it != end()) {
        it->data = data;
        return false;
    }

    Entry* new_entry = new Entry(newkey, data);  //add a new entry
    insert(new_entry, array, tablesize);         //use common insert code
    entrysize++;

    if (entrysize > tablesize*2)                 //if load factor>2, rehash
        rehash();

	return true;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::erase (const KEY& k) {
    std::size_t key = H()(k);
    int hashcode = (int) (key % (std::size_t) tablesize);
    if (!array[hashcode]) //key is not in table
        return false;
    Entry* p = array[hashcode];
    if (p->key == k) {    //key is at the top of the list
        array[hashcode] = p->next;
        delete p;
        entrysize--;
        return true;
    }
    while (p->next) {     //key is a child within list
        Entry* parent = p;
        p = p->next;
        if (p->key == k) {
            parent->next = p->next;
            delete p;
            entrysize--;
            return true;
        }
    }
    return false;          //key is not in table
}

template <typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::rehash(){
    int new_size = nextPrime(tablesize*2);
    Entry** new_array = allocate(new_size);
    for (int i = 0; i < tablesize; i++) {    //traverse table
        Entry* p = array[i];
        while (p) {
            Entry* temp = p->next;           //copy each entry
            p->next = nullptr;
            insert(p, new_array, new_size);  //insert into table
            p = temp;
        }
    }
    delete[] array;
    array = new_array;
    tablesize = new_size;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::find( const KEY & x ) const{
    std::size_t key = H()(x);
    int hashcode = (int) (key % (std::size_t) tablesize);
    if (!array[hashcode])           //nothing in table with this hash code
	    return end();
    Entry* p = array[hashcode];     //found hashcode, look in list for key
    while (p) {
        if (p->key == x)
            return Iterator(p);
        p = p->next;
    }
    return end();
}


template<typename KEY, typename T, typename H>
T& UnorderedMap<KEY, T, H>::operator[](const KEY & k){
    Iterator it = find(k);
    if (it == end()) {
        insert(k, T());
        it = find(k);
    }
    return it->data;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::Iterator::operator++(int){
	if (_cur == _map->end_entry)
	    return *this;
	if (_cur->next) {
	    _cur = _cur->next;
	    return *this;
	}

	for (int i = _n+1; i < _map->tablesize; i++)
        if (_map->array[i]) {
            _cur = _map->array[i];
            _n = i;
            return *this;
        }

	_cur = _map->end_entry;
    _n = _map->tablesize;
	return *this;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::begin() const{

    if (entrysize == 0)
        return end();

    int i;
	for (i = 0; i < tablesize; i++)
       if (array[i])
           break;

	return Iterator(this, array[i], i);
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::end() const{
	return Iterator(end_entry);
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry* UnorderedMap<KEY, T, H>::Iterator::operator->(){
	return _cur;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry& UnorderedMap<KEY, T, H>::Iterator::operator*(){
    if (_cur == nullptr)
        return T();
    else
	    return *_cur;
}


template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator!=(Iterator it){
	return _cur != it._cur;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator==(Iterator it){
	return _cur == it._cur;
}

// Internal method to test if a positive number is prime (not efficient)
bool isPrime( int n ){
	if( n == 2 || n == 3 )
		return true;
	if( n == 1 || n % 2 == 0 )
		return false;
	for( int i = 3; i * i <= n; i += 2 )
		if( n % i == 0 )
			return false;
	return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int nextPrime( int n ){
	if( n % 2 == 0 )
		n++;
	for( ; !isPrime( n ); n += 2 )
		;
	return n;
}

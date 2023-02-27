#include "set.h"
#include <ostream>

/**
 * CS515 Program 6
 * File: set.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: March 25, 2021
 * Collaboration Declaration:
 * Professor Kulik helped with a compiler error
 * Assistance received from online resources
 */

Set::Set() {
    _head = nullptr;  //initialize member variables
    _tail = nullptr;
    _size = 0;
}

// copy constructor
Set::Set(const Set &rhs){
    _head = nullptr;  //initialize member variables
    _tail = nullptr;
    _size = 0;
    copyCode(rhs);    //copy from other set
}

// destructor
Set::~Set(){
    destructCode();
}

// assignment operator
Set& Set::operator =(const Set &v) {
    if (this != &v) {
        destructCode(); //delete any existing info
        copyCode(v);    //copy from other set
    }
    return *this;
}

Set::Iterator::Iterator() {
    _cur = nullptr;
}

Set::Iterator::Iterator(Elem *cur) {
    _cur = cur;
}

// return an iterator pointing at the beginning of the list
Set::Iterator Set::begin() const {
    return Set::Iterator(_head);
}

// return an iterator to the element if val is found, or set::end() otherwise.
Set::Iterator Set::find(ELEMENT_TYPE val) const {
    for (Set::Iterator it = begin(); it != end(); it++) //loop over set
        if (*it == val)     //if val is found, return it
            return it;
    return end();           //else return end
}

// return an iterator pointing at one element beyond the end of list
Set::Iterator Set::end() const{
    if (_size == 0)     //if size is 0, end is null
        return Set::Iterator(nullptr);
    else                //else end is the element past tail
        return Set::Iterator(_tail->next);
}

ELEMENT_TYPE& Set::Iterator::operator*() {
    return _cur->info;
}

Set::Iterator Set::Iterator::operator++(int) { //post-increment operator
    Elem* temp = _cur;
    _cur = _cur->next;      //advance element
    return Iterator(temp);
}

Set::Iterator Set::Iterator::operator--(int) {  //post-decrement operator
    Elem* temp = _cur;
    _cur = _cur->prev;      //move backward
    return Iterator(temp);
}

bool Set::Iterator::operator==(Iterator it) const { //equality operator
    return _cur == it._cur;
}

bool Set::Iterator::operator!=(Iterator it) const { //inequality operator
    return _cur != it._cur;
}

Set::Reverse_Iterator::Reverse_Iterator() { //construct a null iterator
    _cur = nullptr;
}

Set::Reverse_Iterator::Reverse_Iterator(Elem *cur) { //construct an iterator given pointer to Elem
    _cur = cur;
}

// return an reverse iterator pointing at the reverse beginning of the list
Set::Reverse_Iterator Set::rbegin() const {
    return Set::Reverse_Iterator(_tail);        //reverse iterator starts at the tail
}

// return an reverse iterator pointing at one element beyond the beginning of list
Set::Reverse_Iterator Set::rend() const{
    if (_size == 0)
        return Set::Reverse_Iterator(nullptr);
    else
        return Set::Reverse_Iterator(_head->prev);  //reverse end starts at the element before head
}

ELEMENT_TYPE& Set::Reverse_Iterator::operator*() {
    return _cur->info;
}

Set::Reverse_Iterator Set::Reverse_Iterator::operator++(int) {
    Elem* temp = _cur;
    _cur = _cur->prev;  //advancing reverse iterator goes to the previous element
    return Reverse_Iterator(temp);
}

Set::Reverse_Iterator Set::Reverse_Iterator::operator--(int) {
    Elem* temp = _cur;
    _cur = _cur->next;  //decrementing reverse iterator goes to the next element
    return Reverse_Iterator(temp);
}

bool Set::Reverse_Iterator::operator==(Set::Reverse_Iterator it) const {
    return _cur == it._cur;
}

bool Set::Reverse_Iterator::operator!=(Set::Reverse_Iterator it) const {
    return _cur != it._cur;
}

// insert an int into the set;
void Set::insert(ELEMENT_TYPE element) {

    if (find(element) != end())  //if element is present, do not insert
        return;

    Elem* e = new Elem();        //make the new element
    e->info = element;
    e->prev = nullptr;
    e->next = nullptr;

    if (size() == 0) {  //Set is empty
        _head = e;                    //new elements is both head and tail (size==1)
        _tail = e;
        Elem* pre_head = new Elem();  //create dummy element to go before head (for iterators)
        pre_head->prev = nullptr;
        pre_head->next = e;
        e->prev = pre_head;
        Elem* post_tail = new Elem(); //create dummy element to go after tail (for iterators)
        post_tail->next = nullptr;
        post_tail->prev = e;
        e->next = post_tail;
    } else if (e->info < _head->info) {  //element is new head
        _head->prev->next = e;
        e->prev = _head->prev;
        e->next = _head;
        _head->prev = e;
        _head = e;
    } else if (e->info > _tail->info) {  //element is new tail
        _tail->next->prev = e;
        e->next = _tail->next;
        e->prev = _tail;
        _tail->next = e;
        _tail = e;
    } else {                             //element is in the middle of the set
        Elem* cur = _head;
        while (cur != nullptr) {         //advance until element is found (it is known to exist)
            if (e->info < cur->info) {
                e->prev = cur->prev;
                cur->prev->next = e;
                cur->prev = e;
                e->next = cur;
                break;
            }
            cur = cur->next;
        }
    }
    _size++;
}

// remove an int from the set;
void Set::erase(ELEMENT_TYPE val) {
    Elem* cur = _head;
    while (cur != nullptr) {
        if (cur->info == val) {
            if (cur == _head && cur == _tail) {   //element is only element in set
                _head = nullptr;
                _tail = nullptr;
            }
            else if (cur == _head) {              //element is at head
                _head = cur->next;
                _head->prev = nullptr;
            }
            else if (cur == _tail) {              //element is at tail
                _tail = _tail->prev;
                _tail->next = nullptr;
            } else {                              //element is in middle of the set
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
            }
            delete cur;
            _size--;
            break;                                //if element is found and deleted, break
        }
        cur = cur->next;                          //advance to next element
    }
}

// remove all elements from set
void Set::clear() {
    destructCode();
}

// return size of the set
int Set::size() const {
    return _size;
}

void Set::destructCode() {
    if (_size == 0)
        return;
    Elem* temp = _head->prev;
    while (temp != nullptr) {   //delete every element one at a time
        Elem* next = temp->next;
        delete temp;
        temp = next;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;                  //reset all member variables
}

void Set::copyCode(const Set & v) {
    for (Iterator it = v.begin(); it != v.end(); it++) {    //deep copy of every element
        ELEMENT_TYPE next = *it;
        insert(next);
    }
}

std::ostream& Set::dump(std::ostream& out, const Set& v) {
    if (v.size() != 0) {
        for (Set::Iterator it = v.begin(); it != v.end(); it++) {   //put every element into out stream
            out << *it << " ";
        }
    }
    return out;
}

bool operator==(const Set& s1, const Set& s2) {
    if (s1.size() != s2.size())         //if size does not match, return false
        return false;

    Set::Iterator it1 = s1.begin();
    Set::Iterator it2 = s2.begin();
    for (; it1 != s1.end(); it1++) {    //iterate over each element in s1
        if (*it1 != *it2)               //if an element does not match, return false
            return false;
        it2++;
    }
    return true;                        //if everything matches, return true
}

std::ostream& operator<<(std::ostream& out, Set &v) {
    v.dump(out, v);
    return out;
}

// set intersect and union
Set operator&(const Set& s1, const Set& s2) {
    Set set;
    for (Set::Iterator it1 = s1.begin(); it1 != s1.end(); it1++) {  //loop over s1
        if (s2.find(*it1) != s2.end())                              //if the item is in s2, insert it
            set.insert(*it1);
    }
    return set;
}

Set operator|(const Set& s1, const Set& s2) {
    Set set = s1;   //copy s1
    for (Set::Iterator it2 = s2.begin(); it2 != s2.end(); it2++)    //loop over s2
        set.insert(*it2);                                           //insert every element
    return set;
}

// set difference
Set operator-(const Set& s1, const Set& s2) {
    Set set = s1;   //copy s1
    for (Set::Iterator it2 = s2.begin(); it2 != s2.end(); it2++)    //loop over s2
        set.erase(*it2);                                            //remove every element
    return set;
}

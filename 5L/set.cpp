#include "set.h"
/**
 * CS515 Lab 5
 * File: set.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: March 14, 2021
 * Collaboration Declaration: none
 *  Assistance received from online resources
 *      stack overflow, C++ docs
 */

Set::Set() {
    _head = 0;  //initialize member variables
    _tail = 0;
    _size = 0;
}

// copy constructor
Set::Set(const Set &v){
    copyCode(v);
}

// destructor
Set::~Set(){
    destructCode();
}

// assignment operator
Set& Set::operator =(const Set &v) {
    if (this != &v) {
        destructCode();
        copyCode(v);
    }
    return *this;
}

// insert an int into the set;
void Set::insert(ELEMENT_TYPE element) {
    //if the element is already the head or the tail, return
    if ((_head != nullptr && element == _head->info) || (_tail != nullptr && element == _tail->info))
        return;

    if (find(element))  //if the element is in the list, return
        return;

    Elem* e = new Elem; //if element is not in list, make new element
    e->info = element;
    _size++;

    if (_head == nullptr) {  //if list is empty, insert at head
        e->prev = nullptr;
        e->next = nullptr;
        _head = e;
        _tail = e;
    } else if (e->info < _head->info) {  //if element is less than head, insert at head
        e->prev = nullptr;
        e->next = _head;
        _head->prev = e;
        _head = e;
    } else if (element > _head->info && element < _tail->info) { //if element is between head and tail
        Elem *temp = _head;
        while (temp->next->info < e->info)  //find position to insert element
            temp = temp->next;

        Elem* tempnext = temp->next;        //insert element
        temp->next = e;
        e->next = tempnext;
        tempnext->prev = e;
        e->prev = temp;
    } else if (element > _tail->info) {  //if element is greater than tail, insert at tail
        e->prev = _tail;
        e->next = nullptr;
        _tail->next = e;
        _tail = e;
    }
}

// remove an int from the set;
void Set::erase(ELEMENT_TYPE val) {
    if (_size == 0)
        return;

    Elem* temp = _head;
    while (temp != nullptr) {
        if (temp->info == val) {
            if (size() == 1) {  //if there is only one element, reset everything
                _head = nullptr;
                _tail = nullptr;
            } else if (temp == _head) { //if element is at head, remove head
                temp->next->prev = nullptr;
                _head = temp->next;
            } else if (temp == _tail) { //if element is at tail, remove tail
                temp->prev->next = nullptr;
                _tail = temp->prev;
            } else {                    //remove element from middle of list
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            _size--;
            delete temp;
            break;
        }
        temp = temp->next;
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

// return true if an element is found; false otherwise
bool Set::find(ELEMENT_TYPE val) const {
    if (_size == 0)
        return false;

    Elem* temp = _head;
    while (temp != nullptr) {  //advance pointer until element is found
        if (temp->info == val)
            return true;
        temp = temp->next;
    }
    return false;              //if element is not found, return false
}

void Set::destructCode() {
    Elem* temp = _head;
    while (temp != nullptr) {
        Elem* next = temp->next;
        delete temp;
        temp = next;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

void Set::copyCode(const Set & v) {
    Elem *temp = v._head;

    _head = nullptr;
    _tail = nullptr;
    _size = 0;
    while (temp != nullptr) {
        insert(temp->info);
        temp = temp->next;
    }
}

std::ostream& Set::dump(std::ostream& out, const Set &v) const {
    Elem* temp = v._head;
    while (temp != nullptr) {
        out << temp->info << " ";
        temp = temp->next;
    }
    out << endl;
    return out;
}

bool operator==(const Set& s1, const Set& s2) {
    if (s1.size() != s2.size())    //if size does not match, return false
        return false;

    Set::Elem* t1 = s1._head;
    Set::Elem* t2 = s2._head;
    while (t1 != nullptr) {
        if (t1->info != t2->info)  //if an element does not match, return false
            return false;
        t1 = t1->next;
        t2 = t2->next;
    }
    return true;                   //if everything matches, return true
}

std::ostream& operator<< (std::ostream& out, const Set &v) {
    v.dump(out, v);
    return out;
}

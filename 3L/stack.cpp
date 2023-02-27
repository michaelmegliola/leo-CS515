#include "stack.h"

// constructor with default capacity value
stack::stack(int cap) {
    _capacity = cap;
    _arr = new TYPE[_capacity];
    _tos = 0;
}

// copy constructor
stack::stack(const stack& other) {
    _capacity = other._capacity;
    _arr = new TYPE[_capacity];
    _tos = other._tos;              //set all vals to the vals from other
    for (int i = 0; i < _tos; i++)  //deep copy all elements from other
        _arr[i] = other._arr[i];
}

// assignment operator
stack& stack::operator=(const stack& other) {
    if (this != &other) {
        if (_capacity != other._capacity) { //if the capacities differ reallocate array
            delete[] _arr;
            _capacity = other._capacity;
            _arr = new TYPE[_capacity];
        }
        _tos = other._tos;
        for (int i = 0; i < _tos; i++)      //deep copy from other
            _arr[i] = other._arr[i];
    }
    return *this;
}

// move constructor
stack::stack(stack&& other) {
    _arr = other._arr;              //steal data structure from other
    _capacity = other._capacity;    //copy attributes from other
    _tos = other._tos;
    other._arr = nullptr;           //rm data structure from other
    other._capacity = 0;            //reset attributes (unsure if needed, but can't hurt)
    other._tos = 0;
}

// move assignment operator
stack& stack::operator=(stack&& other) {
    if (this != &other) {
        delete[] _arr;                  //delete existing data structure
        _arr = other._arr;              //steal data structure from other
        _capacity = other._capacity;    //copy attributes from other
        _tos = other._tos;
        other._arr = nullptr;           //rm data structure from other
        other._capacity = 0;            //reset attributes (unsure if needed, but can't hurt)
        other._tos = 0;
    }
    return *this;
}

// destructor
stack::~stack() {
    delete[] _arr;
}

// push an element;
// if fixed sized stack, throw FullStackException when stack is full
void stack::push(const TYPE x) {
    if (_tos == _capacity)          //if stack is full, throw
        throw FullStackException();
    _arr[_tos++] = x;
}

// remove and element; throw EmptyStackException when stack is empty
void stack::pop() {
    if (_tos == 0)                      //if stack is empty, throw
        throw EmptyStackException();
    _tos--; //no need to explicitly reset elements, just ignore their values
}

// return a reference to the top element without popping; throw EmptyStackException when stack is empty
TYPE& stack::top() {
    return _arr[_tos-1];
}

// return true if the stack is empty, false otherwise
bool stack::empty() {
    return size() == 0;
}

// return the number of elements currently on the stack
int stack::size() {
    return _tos;
}

// return the current capacity of the stack
int stack::capacity() {
    return _capacity;
}

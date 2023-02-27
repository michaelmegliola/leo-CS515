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

// destructor
stack::~stack() {
    delete[] _arr;
}

void stack::push(const TYPE x) {
    if (_tos == _capacity) {        //if new element will exceed cap, resize array with 2X cap
        TYPE* newarray = new TYPE[_capacity*2];
        for (int i=0; i<_capacity;i++)
            newarray[i] = _arr[i];
        _capacity *= 2;
        delete[] _arr;
        _arr = newarray;
    }
    _arr[_tos++] = x;   //add new element and advance tos
}

// remove and element; throw EmptyStackException when stack is empty
void stack::pop() {
    if (_tos == 0)  //if stack is empty, throw
        throw EmptyStackException();
    _tos--;         //no need to explicitly reset elements, just ignore their values
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

void stack::dump(ostream &os){      //sends items to an output stream
    for(int i = _tos-1; i >= 0; i--)
        os << _arr[i] << " ";
    os << endl;
}

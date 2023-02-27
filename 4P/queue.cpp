#include "queue.h"

// circular array implementation of queue
queue::queue(int cap) {
    _size = 0;
    _front = 0;     //rear = front+size
    _capacity = cap;
    _arr = new TYPE[cap];
}

queue::queue(const queue& other) {
    _front = other._front;
    _capacity = other._capacity;
    _size = other._size;                                //copy all members

    _arr = new TYPE[_capacity];
    for (int i = _front; i < _front+_capacity; i++)     //deep copy arr
        _arr[i%_capacity] = other._arr[i%_capacity];
}

queue& queue::operator=(const queue& other) {
    if (this != &other) {
        if (_capacity != other._capacity) {     //if the array is not already the correct size
            delete[] _arr;                      //  delete
            _capacity = other._capacity;        //  reallocate
            _arr = new TYPE[_capacity];
        }

        _front = other._front;
        _size = other._size;                    //set members

        for (int i = _front; i < _front + _capacity; i++)   //deep copy from other (ignore elements not in use)
            _arr[i % _capacity] = other._arr[i % _capacity];
    }
    return *this;
}

queue::~queue() {
    delete[] _arr;
}

void queue::enqueue(int data) {                 //places item at back of queue
    if (_size == _capacity) {                   //if the new element will exceed the cap of the array
        TYPE* newarray = new TYPE[_capacity*2]; //  remake arr with 2X cap
        int newsize = _size;                    //_size will get changed when dequeue is called
        for (int i = 0; i < newsize; i++)       //avoid uninitialized values (valgrind)
            newarray[i] = 0;
        for (int i = 0; i < _size; i++)         //copy the contents of queue
            newarray[i] = dequeue();

        _front = 0;         //move front in the new queue
        _capacity *= 2;     //double cap
        _size = newsize;    //restore size from stash

        TYPE* temp = _arr;  //save pointer to perform delete
        _arr = newarray;    //swap to new array
        delete[] temp;
    }
    _arr[(_front+_size) % _capacity] = data;    //write data into the queue
    _size++;
}

TYPE queue::dequeue(){                  //removes item from front of queue
    if (empty())
        throw EmptyQueueException();

    int n = _arr[_front % _capacity];   //queue is circular
    _front++;
    _size--;

    return n;
}

void queue::dump(ostream &os){      //sends items to an output stream
    for(int i = _front; i < _front+_size; i++)
        os << _arr[i%_capacity] << endl;
}

int queue::size(){                  //return size
    return _size;
}

bool queue::empty(){                //return true if empty
    return _size == 0;
}

int queue::capacity() {
    return _capacity;
}

TYPE& queue::front() {
    return _arr[_front%_capacity];
}
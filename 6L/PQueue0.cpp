#include "PQueue0.h"

/**
 * CS515 Lab 6
 * File: PQueue0.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: March 21, 2021
 * Collaboration Declaration: none
 *  Assistance received from online resources
 *      none
 */

PQueue::PQueue() {
    _size = 0;
}

PQueue::PQueue(int* items, int size) {
    _size = size < MAX_SIZE+1 ? size : MAX_SIZE+1;
    for (int i = 1; i <= size; i++) {  //transfer items from input array to local array
        _array[i] = items[i-1];
    }
    buildHeap();    //build from local array
}

void PQueue::insert(T item) {
    if (_size < MAX_SIZE) {
        _size++;
        _array[_size] = item;   //insert item
        moveUp();               //place item correctly
    }
}

T PQueue::findMin() {
    return _array[1];   //min is always at root
}

void PQueue::deleteMin() {
    if (_size > 0) {
        _array[1] = _array[_size];
        _size--;
        moveDown(1);    //fix the tree and find the new root
    }
}

bool PQueue::isEmpty() {
    return _size == 0;
}

int PQueue::size() {
    return _size;
}

void PQueue::buildHeap() {
    int i = _size;                              //start at right edge
    while (i > 1) {
        if (_array[i] < _array[i/2]) {          //if item i < left child, swap
            int j = i;                          //keep i intact
            while (_array[j] < _array[j/2]) {   //keep swapping item until correct position
                T temp = _array[j/2];
                _array[j/2] = _array[j];
                _array[j] = temp;
                j = j/2;
            }
        } else i--;                             //when item does not need to move, check next item
    }
}

void PQueue::moveDown(int i) {

    bool swapping = true;
    while (swapping) {          //if a swap was preformed the last time through, continue
        if (i*2 > _size)        //is i a leaf?
            break;
        swapping = false;       //default to false
        if (2*i+1 <= _size) {   //i has two children

            if (_array[2*i] < _array[2*i+1]) {  //left child < right child

                if (_array[2*i] < _array[i]) {  //left child < parent
                    T temp = _array[2*i];       //swap
                    _array[2*i] = _array[i];
                    _array[i] = temp;
                    i = 2*i;                    //follow parent
                    swapping = true;
                }

            } else if (_array[2*i+1] < _array[i]) { //right child < parent
                T temp = _array[2*i+1];             //swap
                _array[2*i+1] = _array[i];
                _array[i] = temp;
                i = 2*i+1;                          //follow parent
                swapping = true;
            }

        } else { //i has one child

            if (_array[2*i] < _array[i]) {  //left (only) child < parent
                T temp = _array[2*i];       //swap
                _array[2*i] = _array[i];
                _array[i] = temp;
                i = 2*i;                    //follow parent
                swapping = true;
            }
        }
    }
}

void PQueue::moveUp() {
    int i = _size;                      //right most element
    while (i > 1) {
        if (_array[i] < _array[i/2]) {  //i < parent
            T temp = _array[i/2];       //swap
            _array[i/2] = _array[i];
            _array[i] = temp;
            i = i/2;                    //follow i
        } else break;
    }
}

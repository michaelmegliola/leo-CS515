#include "charlist.h"
/**
 * CS515 Lab 5
 * File: charlist.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: March 14, 2021
 * Collaboration Declaration: none
 *  Assistance received from online resources
 *      stack overflow, C++ docs
 */

// insert char at the beginning of the list
void CharList::insertFront(char value){
    Elem *p = new Elem;  //new element
    p->info = value;
    p->next = head;      //insert at head of list
    head = p;
}

// insert char at the end of the list
void CharList::insertRear(char value){
    Elem *p, *cur = head;
    if (head==0){                   //empty list
        insertFront(value);         //if list is empty, insert at head
    } else {
        while ( cur->next != 0 )    //else find last element
            cur = cur->next;
        p = new Elem;               //new element
        p->info = value;
        p->next = 0;                //insert at tail
        cur->next = p;
    }
}

// convert to string
string CharList::toStr(){
    Elem * cur = head;
    string s;
    while (cur != 0) {
        s += cur->info;
        cur = cur->next;
    }
    return s;
}

// common copy code
void CharList::copyCode(const CharList & v){
    Elem *a1, *b1, *b2;
    head = 0;
    a1 = v.head;
    while (a1 != 0) {          //while source is not at end
        b1 = new Elem;         //new element
        if (head == 0)         //if empty, insert at head
            head = b1;
        b1->info = a1->info;
        b1->next = 0;
        b2 = b1;
        a1 = a1->next;         //next element
        if (b2 != 0)           //else insert at end
            b2->next = b1;
    }
}

// common code for deallocation 
void CharList::destructCode(){
    Elem* p = head;
    while (p != 0) {         //iterate through elements
        Elem* q = p->next;   //delete elements
        delete p;
        p = q;
    }
    head = 0;
}

// overloaded output operator
ostream& operator<<(ostream& out, CharList c){
    out << c.toStr();
    return out;
}
// Do not modify this file
#include <iostream>
#include <cstdlib>
#include <cassert>

#define MAX_CAP 10
using namespace std;

class queue{
private:
    int item[MAX_CAP];  // array for queue items
    int rear;       // index to rear of queue
    int front;      // index to front of queue
public:
	// default constructor 
    queue();        
	
	// add an element to the end of queue
	// precondition: queue is not full 
    void enqueue(const int); 
	
	// remove an element from the front of queue 
	// precondition: queue is not empty
    int dequeue();
	
	// output queue elements to ostream 
    void dump(ostream &os); 
	
	// return the number of elements currently in the queue
    int size();         
	
	// return true if the queue is empty, false otherwise
    bool empty();  
	
	// return true if the queue is full, false otherwise    
    bool full(); 
};

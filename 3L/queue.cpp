#include "queue.h"

// circular array implementation of queue
queue::queue(){
    rear = 0;   // rear used as the count of queue items
    front = 0;  // front points to queue front
	for(int i=0; i<MAX_CAP; i++)    //initializes queue with all 0s
		item[i]=0;
}

void queue::enqueue(int data) {     //places item at back of queue
    item[rear % MAX_CAP] = data;
    rear++;
}

int queue::dequeue(){               //removes item from front of queue
    int n = item[front % MAX_CAP];
    front++;
    return n;
}

void queue::dump(ostream &os){      //sends items to an output stream
    for(int i = front; i <= rear-1; i++)
        os << item[i%MAX_CAP] << endl;
}

int queue::size(){                  //return size
    return (rear - front);
}

bool queue::empty(){                //return true if empty
    return (front == rear);
}

bool queue::full(){                 //return true if full
    return (size() >= MAX_CAP);
}
/* This is to test the queue for lab 3. These should be the simplest test cases */

#include "queue.h"
#include <cassert>

int main()
{
    int tmp;
    queue q;
    cout << "testing empty queue" << endl;
    assert( q.size() == 0);
    assert(q.empty() == true);
    assert( q.full() == false);

    cout << "correct" << endl << "testing enqueues" << endl;

    for( int i = 0; i < 10; i++ )
    {
	assert(q.size() == i);
	q.enqueue( i * 10 );
    }

    assert( q.size() == 10);
    assert(q.full() == true);
    assert( q.empty() == false);    

    cout << "looking at output should be 0,10,20,30,40,50,60,70,80,90" << endl;
    q.dump(cout);
    cout << "done" << endl << "testing dequeues" << endl;

    for( int i = 0; i < 10; i++ )
    {
	assert(q.size() == 10 - i);
	assert( q.empty() == false);
	assert( q.dequeue() == i * 10 );
	assert(q.full() == false);
    }

    cout << "dump of empty queue" << endl;
    q.dump(cout);

}

/* second test for queue lab 3 */

#include "queue.h"
#include <cassert>

int main()
{
	queue q;
    cout << "testing enqueues and dequeues" << endl;
 	cout << "there should be no outputs" << endl;
	
	for( int i=0; i < 1000; i++ )
	{
		assert( q.empty() == true);
		assert( q.full() == false);
    	q.enqueue(i);
		assert(q.size() == 1 );
 		assert( q.dequeue() == i);
		q.dump(cout);
		assert( q.empty() == true);
	}
}

/* This is third test case for queue.cpp, tests queue being filled cases */

#include "queue.h"
#include <cassert>

int main()
{
	queue q;
    cout << "testing queueing and dequeueing on almost full queue" << endl;
	
	for( int i = 0; i < 10; i++)
	{
		q.enqueue( 0 );
		assert(q.size() == i + 1 );
	}
	cout << "should be all zero's" << endl;	
	q.dump(cout);

	assert( q.full() == true );

  	for( int i = 0; i < 10000; i++ )
	{
		assert(q.full() == true);
  		q.dequeue();
		q.enqueue(i);
		assert(q.full() == true);		

	}
	cout << "output should be 9990,9991,9992,9993,9994,9995,9996,9997,9998,9999" << endl;
	q.dump(cout);



}

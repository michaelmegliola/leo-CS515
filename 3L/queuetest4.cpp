/*This is the fourth test for the queue.cpp for lab3 */

#include "queue.h"
#include <cassert>

int main()
{
	queue q;
	cout << "testing mildly filled queue" << endl;

	for( int i = 0;  i < 4; i++ )
	{
		q.enqueue(i);
		assert(q.size() == i + 1);
	}

	for( int i = 4; i < 11111; i++ )
	{
		assert( q.size() == 4 );
		q.enqueue( i );
		assert( q.size() == 5 );
		assert(q.dequeue() == i - 4 );
		assert( q.size() == 4 );

	}
	
	cout << "should output 11107 to 11110" << endl;
	q.dump(cout );
	
	for( int i = 0; i < 4; i++ )
	{
		assert(q.size() == 4 - i);
		assert(q.dequeue() == 11110- (3-i));
	}
	
	cout << "nothing should be output after here" << endl;
	q.dump(cout );
}

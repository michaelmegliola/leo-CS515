/* second test for stack */

#include "stack.h"
#include <cassert>

int main()
{
	stack * s = new stack( 10 );

	assert( s->empty() == true );
	assert(s->capacity() == 10 );

	for( int i =0; i < 1000; i++ )
	{
		assert( s->size() == 0 );
		s->push(i);
		assert( s->capacity() == 10 );
		assert( s->top() == i );
		s->pop();
	}

	for( int i = 0; i < 10; i++ )
	{
		s->push(i);
		assert( s->size() == i + 1 );

	}

	assert( s->capacity() == 10 );
	assert( s->size() == 10 );

	try
	{
		s->push(10);
		s->push(11);
		s->push(12);

	}
	catch ( FullStackException e )
	{
		cout << "exception caught" << endl;
	}
	assert( s->size() == 10 );
	assert( s->top() == 9 );
	for( int i = 0; i < 10; i++ )
	{
		s->pop();
	}

	assert( s->size() == 0 );
	assert( s->empty() == true );

	try 
	{
		for( int i = 0; i < 1000; i++)
		{
			s->pop();
		}
 	}
	catch ( EmptyStackException e )
	{
		cout << "exception caught" << endl;
	}

    delete s; 


}

/* this test is set up to work on copy constructor */

#include "stack.h"
#include <cassert>

int main()
{
	stack * s = new stack(15);
	assert( s->size() == 0 );
	assert( s->empty() == true);
	assert(s->capacity() == 15 );

	for( int i = 0; i < 15; i++ )
	{
		s->push(i);
	}

	assert( s->size() == 15 );
	assert( s->empty() == false );
	assert( s->capacity() == 15);

	stack * s2 = new stack(*s );

	assert( s2->size() == 15 );
	assert( s2->capacity() ==15 );
	assert( s2->empty() == false );

	for( int i = 0; i < 15; i++ )
	{
		assert( s2->top() == s->top() );
		s2->pop();
		s->pop();

	}

	assert( s2->size() == 0 );
	assert( s2->empty() == true);
	assert( s2->capacity() == 15);

	delete s2;
	delete s;
	cout << "test done" << endl;
}


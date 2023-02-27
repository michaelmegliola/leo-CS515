/*basic test of stack */

#include "stack.h"
#include <cassert>

int main()
{
	//testing default constructor
	
	stack * s = new stack();

	//testing pushing and popping
	assert( s->empty() == true );
	assert( s->capacity() == 8 );

	for( int i = 0; i < 8; i++ )
	{
		assert( s->size() == i);
		s->push(i);
		assert( s->top() == i);		

	}

	for( int i = 7; i >= 0; i--)
	{
		s->pop();
		assert(s->size() == i);
	}
	
	assert( s->empty() == true );
	
	delete s; 
	
}

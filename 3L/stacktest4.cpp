/* This test is to test assignment operator */

#include "stack.h"
#include <cassert>

int main() 
{

	stack s(100);
	assert( s.capacity() == 100 );

	for( int i = 0; i < 100; i++ )
	{
		s.push(i);
		assert(s.size() == i + 1 );
	}

	assert( s.size() == 100 );
	assert( s.top() == 99 );

	stack s2 = s;

	assert( s2.capacity() == 100 );
	assert( s2.size() == 100 );
	assert( s2.top() == 99 );

	for( int i = 0; i <100 ; i++ )
	{
		assert( s2.top() == s.top());
		s.pop();
		s2.pop();
		assert( s.size() == s2.size() );
	}

	assert( s.empty() == true );
	assert( s2.empty() == true );

	cout << "testing done" << endl;

}

/*
  This test tests move constructor and move assignment operator
*/

#include "stack.h"
#include <cassert>

stack makeStack();
stack fillStack(stack s);
stack* fillStack(stack* s);

int main() 
{

	// ------ TEST CASTING OF STACKS TO R- AND X-VALUES -------

	cout << "TESTING CAST MOVES" << endl << endl;

	stack* s = new stack(100);

	// check initial stack state
	assert(s->capacity() == 100);
	assert(s->empty() == true);
	assert(s->size() == 0);

	// push 100 ints onto stack
	for (int i = 0; i < 100; i++)
	{
		s->push(i);
		assert(s->size() == i + 1);
		assert(s->top() == i);
	}

	// cast s to rval, move values to t
	cout << "Testing move constructor" << endl;
	stack t(std::move(*s));
	cout << "Tested move constructor" << endl << endl;
	
	assert(s->size() == 0 && s->empty());

	delete s;

	// test move constructor of t
	assert(t.capacity() == 100);
	assert(t.empty() == false);
	assert(t.size() == 100);
	assert(t.top() == 99);

	t.pop();
	t.pop();
	t.top()--;

	// test move assignment operator
	stack q;
	cout << "Testing move assignment" << endl;
	q = std::move(t);
	cout << "Tested move assignment" << endl << endl;
	assert(q.capacity() == 100);
	assert(q.empty() == false);
	assert(q.size() == 98);
	assert(q.top() == 96);

	q.pop();

	assert(q.top() == 96);

	assert(t.size() == 0 && t.empty());

	while (!q.empty())
	{
		q.pop();
	}

	assert(q.empty() == true);
	assert(q.capacity() == 100);
	assert(q.size() == 0);	
	
	// ------- TEST MOVING RETURNED LOCAL STACK (The function call is the r-value) ---------

	cout << "TESTING makeStack() MOVES" << endl << endl;

	// Test move assignment operator
	stack s2;
	cout << "Testing move assignment" << endl;
	s2 = makeStack();
	cout << "Tested move assignment" << endl<< endl;

	assert(s2.capacity() == 100);
	assert(s2.empty() == false);
	assert(s2.size() == 100);
	assert(s2.top() == 99);

	for (int i = 100; i > 0; i--)
	{
		assert(s2.top() == i - 1);
		assert(s2.empty() == false);
		s2.pop();
	}

	assert(s2.empty() == true);

	// ------- TEST MOVING RETURNED LOCAL STACK (The function call is the r-value) ---------

	cout << "TESTING fillStack() MOVES" << endl << endl;

	// Test move constructor
	cout << "Testing move constructor" << endl;
	stack s3(fillStack(s2));
	cout << "Tested move constructor" << endl << endl;

	assert(s3.capacity() == 100);
	assert(s3.empty() == false);
	assert(s3.size() == 100);
	assert(s3.top() == 99);

	for (int i = 100; i > 0; i--)
	{
		assert(s3.top() == i - 1);
		assert(s3.empty() == false);
		s3.pop();
	}

	assert(s3.empty() == true);

	// Test move assignment operator
	stack s4;
	cout << "Testing move assignment" << endl;
	s4 = fillStack(s2);
	cout << "Tested move assignment" << endl << endl;

	assert(s4.capacity() == 100);
	assert(s4.empty() == false);
	assert(s4.size() == 100);
	assert(s4.top() == 99);

	for (int i = 100; i > 0; i--)
	{
		assert(s4.top() == i - 1);
		assert(s4.empty() == false);
		s4.pop();
	}

	assert(s4.empty() == true);

	// Test move assignment operator
	stack* dyns = new stack(100);
	stack s5;
	cout << "Testing move assignment" << endl;
	s5 = std::move(*(fillStack(dyns)));
	cout << "Tested move assignment" << endl << endl;

	assert(s5.capacity() == 100);
	assert(s5.empty() == false);
	assert(s5.size() == 100);
	assert(s5.top() == 99);

	assert(dyns->size() == 0 && dyns->empty());

	for (int i = 100; i > 0; i--)
	{
		assert(s5.top() == i - 1);
		assert(s5.empty() == false);
		s5.pop();
	}

	assert(s5.empty() == true);

	delete dyns;

	cout << "test done\n";
}

stack makeStack()
{
	// make a stack
	stack s(100);

	// push 100 ints onto stack
	for (int i = 0; i < 100; i++)
	{
		s.push(i);
	}

	// return the newly created stack
	return s;
}

stack fillStack(stack s)
{
	// push 100 ints onto stack
	for (int i = 0; i < 100; i++)
	{
		s.push(i);
	}

	// return the stack that has been filled
	return s;
}

stack* fillStack(stack* s)
{
	// push 100 ints onto stack
	for (int i = 0; i < 100; i++)
	{
		s->push(i);
	}

	// return the stack that has been filled
	return s;
}
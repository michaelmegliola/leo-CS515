CXX=g++

all: queue.o stack.o

queue.o: queue.cpp queue.h
	$(CXX) -c queue.cpp

stack.o: stack.cpp stack.h
	$(CXX) -c stack.cpp

tests: queuetest stacktest

queuetest: queuetest.cpp queue.cpp queue.h
	$(CXX) queuetest.cpp queue.cpp -o queuetest


stacktest: stacktest.cpp stack.cpp stack.h
	$(CXX) stacktest.cpp stack.cpp -o stacktest


clean: 
	rm -f queuetest stacktest queue.o stack.o
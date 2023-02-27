CXX=g++

all: PQueue0.o testPQ

PQueue0.o: PQueue0.h PQueue0.cpp
	$(CXX) -c PQueue0.cpp 	

testPQ0: PQueue0.h PQueue0.cpp testPQ0.cpp
	$(CXX)  testPQ0.cpp PQueue0.cpp -o testPQ0

testPQ: PQueue.h PQueue.cpp testPQ.cpp
	$(CXX)  testPQ.cpp -o testPQ

clean:
	rm -f *.o testPQ0 testPQ  
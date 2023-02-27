CXX=g++

all: connectChecker DStest 

connectChecker: connectChecker.cpp 
	$(CXX) -DDEBUG_PRINT  connectChecker.cpp -o connectChecker

DStest: DisjointSet.h  DStest.cpp
	$(CXX)  DStest.cpp -o DStest

clean:
	rm -f *.o  DStest connectChecker
CXX=g++

all: set.o

set.o: set.cpp  set.h
	$(CXX) -c set.cpp

setTest: setTest.cpp  set.o set.h
	$(CXX) setTest.cpp set.o -lgtest -lpthread -o setTest

clean:
	rm -f *.o  setTest 

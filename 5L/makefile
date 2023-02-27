CXX=g++

all: charlist.o set.o 

charlist.o: charlist.cpp charlist.h
	$(CXX) -c charlist.cpp 

jumble: jumble.cpp charlist.o
	$(CXX) jumble.cpp  charlist.o -o jumble

set.o: set.cpp set.h
	$(CXX) -c set.cpp

setTest: setTest.cpp set.o set.h
	$(CXX) setTest.cpp set.o -lgtest -lpthread -o setTest

clean:
	rm -f *.o settest jumble

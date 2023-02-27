CXX=g++

all: HuffTree.o HuffmanCoder

HuffTree.o: PQueue.h PQueue.cpp HuffTree.cpp HuffTree.h
	$(CXX) -c HuffTree.cpp 

HuffmanCoder: HuffmanCoder.cpp HuffTree.o
	$(CXX) HuffmanCoder.cpp HuffTree.o -o HuffmanCoder

clean:
	rm -f *.o HuffTree.o HuffmanCoder
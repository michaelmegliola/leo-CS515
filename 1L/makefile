CXX=g++

all: hello addUp results.txt

hello: hello.cpp
	$(CXX)  hello.cpp -o hello

addUp: addUp.cpp
	$(CXX)  addUp.cpp -o addUp

results.txt: addUp
	./addUp < myNumbers > results.txt

clean:
	rm -f *.o hello
CXX=g++

all: debug1 debug2 sampletests testdriver

debug1: debug1.cpp
	$(CXX) debug1.cpp -o debug1

debug2: debug2.cpp
	$(CXX) -g debug2.cpp -o debug2
	
sampletests: myfun.cpp sampletests.cpp
	$(CXX) myfun.cpp sampletests.cpp -o sampletests

testdriver: myfun.cpp testdriver.cpp
	$(CXX) myfun.cpp testdriver.cpp -o testdriver

clean:
	rm -f debug1 debug2 testdriver

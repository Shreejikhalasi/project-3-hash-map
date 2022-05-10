
CXX = g++ -std=c++17 -Wall

all: run_test

run_test: hashing_test
	./hashing_test

headers: rubrictest.hpp ItemPallet.hpp

hashing_test: headers ItemPallet.cpp main.cpp
	${CXX} ItemPallet.cpp main.cpp -o hashing_test

clean:
	rm -f hashing_test

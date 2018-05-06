all: fileWordCounter test

fileWordCounter: main.o fileWordCounter.o 
	g++ -g -Wall -std=c++11 $^ -o $@ 

test: fileWordCounter.o testFileWordCounter.o
	g++ -g -Wall -std=c++11 $^ -o $@ 

fileWordCounter.o: fileWordCounter.cpp fileWordCounter.hpp
	g++ -g -c -Wall -std=c++11 $< -o $@

testFileWordCounter.o: testFileWordCounter.cpp fileWordCounter.hpp catch.hpp 
	g++ -g -c -Wall -std=c++11 $< -o $@

main.o: main.cpp fileWordCounter.hpp
	g++ -g -c -Wall -std=c++11 $< -o $@

.PHONY: clean
clean:
	rm -f test fileWordCounter *.o

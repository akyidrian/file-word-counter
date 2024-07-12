fileWordCounter: fileWordCounter.cpp fileWordCounter.hpp main.cpp
	g++ -Wall -std=c++11 -o $@ $^

test: testFileWordCounter.cpp catch.hpp fileWordCounter.cpp fileWordCounter.hpp
	g++ -Wall -std=c++11 -o $@ $^

clean:
	rm -f test fileWordCounter

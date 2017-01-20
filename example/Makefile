.PHONY: all clean

CXX_FLAGS=-Wall -Wextra -pedantic -Wsign-conversion

all: example exampled

clean:
	rm -rf bin

exampled: bin example.cpp
	$(CXX) $(CXX_FLAGS) -DEXAMPLE_DEBUG example.cpp -o bin/exampled

example: bin example.cpp
	$(CXX) $(CXX_FLAGS) -O3 -DNDEBUG example.cpp -o bin/example

bin:
	mkdir bin

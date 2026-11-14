CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

.PHONY: all test clean

all: test

build/tests: tests/tests.cpp $(wildcard include/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude tests/tests.cpp -o $@

test: build/tests
	./build/tests

clean:
	rm -rf build

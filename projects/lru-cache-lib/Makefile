CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
LDFLAGS  ?= -pthread

.PHONY: all test clean

all: test

build/tests: tests/tests.cpp $(wildcard include/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude tests/tests.cpp -o $@ $(LDFLAGS)

test: build/tests
	./build/tests

clean:
	rm -rf build

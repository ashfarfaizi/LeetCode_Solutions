CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
SRC      := $(filter-out src/main.cpp,$(wildcard src/*.cpp))

.PHONY: all test clean

all: build/calc test

build/calc: src/main.cpp $(SRC) $(wildcard src/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc src/main.cpp $(SRC) -o $@

build/tests: tests/tests.cpp $(SRC) $(wildcard src/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc tests/tests.cpp $(SRC) -o $@

test: build/tests
	./build/tests

clean:
	rm -rf build

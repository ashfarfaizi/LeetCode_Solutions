CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
SRC      := $(filter-out src/main.cpp,$(wildcard src/*.cpp))

.PHONY: all test clean

all: build/todo test

build/todo: src/main.cpp $(SRC) $(wildcard src/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc src/main.cpp $(SRC) -o $@

build/tests: tests/tests.cpp $(SRC) $(wildcard src/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc tests/tests.cpp $(SRC) -o $@

test: build/tests build/todo
	./build/tests
	sh tests/cli.sh build/todo

clean:
	rm -rf build

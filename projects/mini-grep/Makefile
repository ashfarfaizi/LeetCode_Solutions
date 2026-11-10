CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
SRC      := $(filter-out src/main.cpp,$(wildcard src/*.cpp))

.PHONY: all test clean

all: build/mgrep test

build/mgrep: src/main.cpp $(SRC) $(wildcard src/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc src/main.cpp $(SRC) -o $@

build/tests: tests/tests.cpp $(SRC) $(wildcard src/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc tests/tests.cpp $(SRC) -o $@

test: build/tests build/mgrep
	./build/tests
	sh tests/cli.sh build/mgrep

clean:
	rm -rf build

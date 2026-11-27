CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

.PHONY: all test cli-test clean

all: build/jtok test

build/tests: tests/tests.cpp $(wildcard include/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude tests/tests.cpp -o $@

build/jtok: src/jtok.cpp $(wildcard include/*.hpp)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude src/jtok.cpp -o $@

test: build/tests cli-test
	./build/tests

# Smoke tests for the command-line tool.
cli-test: build/jtok
	@printf '{"a": [1, "x\\ny"]}' | ./build/jtok | diff - tests/cli_expected.txt
	@printf '[1, 2]' | ./build/jtok --check
	@! printf '[1,]' | ./build/jtok --check 2>/dev/null
	@printf '[1,]' | ./build/jtok --check 2>&1 | grep -q '^<stdin>:1:4: error:'
	@test "$$(printf '{ "a" : [ 1 , "x\\ty" ] }' | ./build/jtok --minify)" = '{"a":[1,"x\ty"]}'
	@printf '{"a":[1,{}]}' | ./build/jtok --pretty=4 | diff - tests/cli_pretty_expected.txt
	@! printf '[1 2]' | ./build/jtok --minify 2>/dev/null
	@printf '1' | ./build/jtok --check --minify 2>/dev/null; test $$? -eq 2
	@printf '1' | ./build/jtok --pretty=x 2>/dev/null; test $$? -eq 2
	@echo "cli tests passed"

clean:
	rm -rf build

CXX ?= g++
CXXFLAGS ?= -std=c++20 -O2 -Wall -Wextra -fsanitize=address,undefined -Ilib

.PHONY: test clean
test: tests/test_all
	./tests/test_all
	./tests/standalone.sh
	python3 tests/examples.py

tests/test_all: tests/test_all.cpp $(wildcard lib/*/*.hpp)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f tests/test_all

CXX=g++
CXXFLAGS=-c -Wall -std=c++11
SOURCES=$(wildcard *.h)
OBJECTS=$(SOURCES:.h=.o)

all: $(OBJECTS) tests

%.o: %.h
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY : clean tests

clean:
	rm -f *.o
	$(MAKE) -C test clean

tests:
	@echo Making tests
	$(MAKE) -C test

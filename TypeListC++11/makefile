CXX=g++
CXXFLAGS=-c -Wall -std=c++11
LXXDFLAGS=-std=c++11
SOURCES=$(wildcard *.h)
OBJECTS=$(SOURCES:.h=.o)

all: $(OBJECTS)

%.o: %.h
	$(CXX) $(CXXFLAGS) $< -o $@
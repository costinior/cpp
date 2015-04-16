CXX=g++
IDIR=..
CXXFLAGS=-c -Wall -std=c++11 -I$(IDIR)
LXXDFLAGS=-std=c++11
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
SOURCE_OBJECTS=$(addprefix ../, $(wildcard *.o) )
PROGRAMS=$(SOURCES:.cpp=_test)

all: $(OBJECTS) $(PROGRAMS)
	@echo $(PROGRAMS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(PROGRAMS):
	$(CXX) $(LXXDFLAGS) $(OBJECTS) $(SOURCE_OBJECTS) -o $<

.PHONY = clean

clean:
	rm -f *.o
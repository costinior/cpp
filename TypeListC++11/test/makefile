CXX=g++
IDIR=../
OBJDIR=build
CXXFLAGS=-c -Wall -std=c++11 -I$(IDIR)
SOURCES=$(wildcard *.cpp)
OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o) )
SOURCE_OBJECTS=$(addprefix ../, $(wildcard *.o) )
TESTS=$(SOURCES:.cpp=)

all: $(OBJECTS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
	rm $@

.PHONY = $(OBJDIR) $(TESTS)

$(TESTS):
	$(MAKE) $@.o

$(OBJDIR):
	mkdir -p $@

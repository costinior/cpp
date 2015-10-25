CXX=g++
OBJDIR=build
CXXFLAGS=-c -Wall -std=c++11
SOURCES=$(wildcard *.h)
OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.h=.o) )

all: $(OBJECTS) tests

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY : clean source tests

source: $(OBJECTS)

clean:
	rm -rf $(OBJDIR)

tests:
	$(MAKE) -C test

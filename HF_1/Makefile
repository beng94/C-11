BINARY = OUT
OBJECTS = mystring.o test.o
HEADERS = mystring.h

CXX = g++
CXXFLAGS = -std=c++11 -O0 -Wall -pedantic -DDEBUG
LDFLAGS = -DDEBUG

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BINARY) $(OBJECTS)

.PHONY: all clean

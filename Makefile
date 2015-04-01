# Variable Declarations

CXX=g++
INCDIR = ./
CXXFLAGS=-c -g -std=c++11 -Wall -I$(INCDIR)
#HEADERS = definitions.h parser.h
LDFLAGS=
EXECUTABLE=lispInt
SRCS=lispInt.cpp parser.cpp expressions.cpp userdefines.cpp primitivefunctions.cpp primitives.cpp
OBJS=$(SRCS:.cpp=.o)
RM = rm 
# end

all:clean $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ 

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(EXECUTABLE)

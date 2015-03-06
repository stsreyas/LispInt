# Variable Declarations

CXX=g++
INCDIR = ./
CXXFLAGS=-c -Wall -I$(INCDIR)
#HEADERS = definitions.h parser.h
LDFLAGS=
EXECUTABLE=lispInt
SRCS=lispInt.cpp parser.cpp
OBJS=$(SRCS:.cpp=.o)
RM = rm 
# end

all:$(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ 

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(EXECUTABLE)

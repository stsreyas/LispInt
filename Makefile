# Variable Declarations

CXX = g++
INCDIR = ./
CXXFLAGS = -g -I$(INCDIR)
HEADERS = definitions.h
LDFLAGS = 
PROG = lispInt
SRCS = lispInt.cpp
OBJS = lispInt.o
RM = rm 
# end

all:$(PROG)

$(PROG):$(OBJS)
	$(CXX) $(CFLAGS) $(HEADERS) $(SRCS) -o $(OBJS) 

clean: $(OBJS)
	rm -rf $(OBJS) $(PROG)

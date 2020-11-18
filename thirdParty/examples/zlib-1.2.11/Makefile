CC = gcc
CXX = g++
D = 

SRCS     += $(wildcard *.cpp)
OBJS     += $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  += $(SRCS:%.cpp=%)

INCLUDE +=	-I$(PWD)/../../zlib-1.2.11/include

LIB_PATH += -L$(PWD)/../../zlib-1.2.11/lib

LIB_LINK += -lz

CFLAGS += -g -Wall -std=c++11

all:$(TARGETS)
$(TARGETS):%:%.o
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
	# @rm -rf $(OBJS)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	@rm -rf $(TARGETS) $(OBJS)

D:
	gcc $(demo) -o $(demo) $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
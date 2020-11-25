CC = gcc
CXX = g++
D = 

SRCS     += $(wildcard *.cpp)
OBJS     += $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  += $(SRCS:%.cpp=%)

INCLUDE +=	-I$(PWD)/../../boost-1.74.0/include

LIB_PATH = -L$(PWD)/../../boost-1.74.0/lib

LIB_LINK += -lpthread -lboost_regex -lboost_thread -lrt -lboost_filesystem -lboost_serialization

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
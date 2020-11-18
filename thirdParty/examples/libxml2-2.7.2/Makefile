CC = gcc
CXX = g++
D = 

SRCS     += $(wildcard *.cpp)
OBJS     += $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  += $(SRCS:%.cpp=%)

INCLUDE +=	-I$(PWD)/../../libxml2-2.7.2/include/libxml2

LIB_PATH += -L$(PWD)/../../libxml2-2.7.2/lib

LIB_LINK += -lxml2

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
	$(CC) $(demo) -o $(demo) $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
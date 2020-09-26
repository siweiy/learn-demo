CC = gcc
CXX = g++

SRCS     := $(wildcard *.cpp */*.cpp)
OBJS     := $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  := $(SRCS:%.cpp=%)

INCLUDE := 
LIB_PATH := 
LIB_LINK := -lzmq
CFLAGS := -g -Wall

all:$(TARGETS)
$(TARGETS):%:%.o
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
	# @rm -rf $(OBJS)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	@rm -rf $(TARGETS) $(OBJS)
CC = gcc
CXX = g++
D = 

SRCS     += $(wildcard *.cpp)
OBJS     += $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  += $(SRCS:%.cpp=%)

INCLUDE +=	-I$(PWD)/../../tinyxml2-8.0.0/include

LIB_PATH += -L$(PWD)/../../tinyxml2-8.0.0/lib

LIB_LINK += -ltinyxml2

CFLAGS += -g -Wall -std=c++11

all:$(TARGETS)
$(TARGETS):%:%.o
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
	# @rm -rf $(OBJS)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	@rm -rf $(TARGETS) $(OBJS) *.xml

D:
	$(CC) $(demo) -o $(demo) $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
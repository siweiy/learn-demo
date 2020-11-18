CC = gcc
CXX = g++
D = 

SRCS     += $(wildcard *.cpp)
OBJS     += $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  += $(SRCS:%.cpp=%)

INCLUDE +=	-I$(PWD)/../../gflags/include \
			-I$(PWD)/../../glog/include \
			-I$(PWD)/../../googletest/include

LIB_PATH += -L$(PWD)/../../gflags/lib \
			-L$(PWD)/../../glog/lib \
			-L$(PWD)/../../googletest/lib

LIB_LINK += -lgflags -lgflags_nothreads -lglog -lgtest -lgmock -lgtest_main -lpthread

CFLAGS += -g -Wall -std=c++11

all:$(TARGETS)
$(TARGETS):%:%.o
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
	# @rm -rf $(OBJS)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	@rm -rf $(TARGETS) $(OBJS) gflags_test.INFO  log-*

D:
	gcc $(demo) -o $(demo) $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
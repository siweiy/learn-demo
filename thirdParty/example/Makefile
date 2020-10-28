CC = gcc
CXX = g++

SRCS     += $(wildcard *.cpp)
OBJS     += $(patsubst %.cpp, %.o, $(SRCS))
TARGETS  += $(SRCS:%.cpp=%)

INCLUDE +=	-I$(PWD)/../gflags/include \
			-I$(PWD)/../glog/include

LIB_PATH += -L$(PWD)/../gflags/lib \
			-L$(PWD)/../glog/lib

LIB_LINK += -lgflags -lgflags_nothreads -lglog

CFLAGS += -g -Wall

all:$(TARGETS)
$(TARGETS):%:%.o
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
	# @rm -rf $(OBJS)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	@rm -rf $(TARGETS) $(OBJS) gflags_test.INFO  log-*
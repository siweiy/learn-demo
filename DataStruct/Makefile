CC = gcc
CXX = g++

SRCS     := $(wildcard *.c)
OBJS     := $(patsubst %.c, %.o, $(SRCS))
TARGETS  := $(SRCS:%.c=%)

INCLUDE := 
LIB_PATH := 
LIB_LINK := -ldl
CFLAGS := -g -Wall

all:$(TARGETS)
$(TARGETS):%:%.o
	$(CC) $^ -o $@ $(INCLUDE) $(LIB_PATH) $(LIB_LINK) $(CFLAGS)
	# @rm -rf $(OBJS)

%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	rm -rf $(TARGETS) $(OBJS)
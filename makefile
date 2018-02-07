CC = gcc
CFLAGS = -Wall -g -Iinclude

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	CCFLAGS += -std=gnu11 
endif
ifeq ($(UNAME), Darwin)
	CCFLAGS += -std=c11
endif

program:  
	$(CC)  $(CFLAGS) src/*.c  -o bin/run

run:
	./bin/run

valgrind:
	valgrind -v --leak-check=full ./bin/run

clean:
	rm bin/*

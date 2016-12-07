CC=g++
STD=-std=c++14

all: clean sim

sim: main.o cache.o memory.o
	$(CC) -o $@ $^ $(STD) -w

main.o: storage.h

cache.o: cache.h def.h 

memory.o: memory.h memory.cc 

.PHONY: clean

clean:
	rm -rf sim *.o

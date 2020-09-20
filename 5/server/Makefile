CC = gcc

CFLAGS=-c

all: main

main: main.o server.o convert.o
	$(CC) main.o server.o convert.o -o main

main.o: main.c
	$(CC) $(CFLAGS) main.c

server.o: server.c
	$(CC) $(CFLAGS) server.c

convert.o: convert.c
	$(CC) $(CFLAGS) convert.c

clean:
	rm -rf *.o main
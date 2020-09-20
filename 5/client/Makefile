CC = gcc

CFLAGS=-c

all: main

main: main.o client.o
	$(CC) main.o client.o -o main

main.o: main.c
	$(CC) $(CFLAGS) main.c

client.o: client.c
	$(CC) $(CFLAGS) client.c

clean:
	rm -rf *.o main
	CC=gcc
	CFLAGS=-Wall -I./include
	
all: main.c
	$(CC) $(CFLAGS) main.c src/clnt.c

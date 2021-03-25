CC = gcc
CFLAGS = -std=c17 -Wpedantic -lpthread

make: phil

phil: philosophers.c a3_1.h
	$(CC) -o phil philosophers.c $(CFLAGS)

clean:
	rm phil
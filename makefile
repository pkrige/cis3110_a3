CC = gcc
CFLAGS = -std=gnu18 -Wpedantic -lpthread

make: phil

phil: philosophers.c a3_1.h
	$(CC) -o phil philosophers.c a3_1.h $(CFLAGS)
CC = gcc
CFLAGS = -pthread


all:
	$(CC) $(CFLAGS)  scheduler.c MinHeap.c MinHeap.h -o scheduler
	

clean:
	rm  *scheduler

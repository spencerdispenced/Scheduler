#ifndef MinHeap_h
#define MinHeap_h

#include <stdio.h>
#include <string.h>
#define __USE_XOPEN
#define _GNU_SOURCE
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


typedef int (*Comparator)( const void *, const void * );

typedef struct MinHeap {
	Comparator	comparator;
	void *		block;		// extensible block, moveable.
	void *		temp;		// temp space for swap()
	unsigned int	elemsize;	
	unsigned int	elemcount;
} MinHeap;


static void printHeap( MinHeap * minHeap );
int parseTime(char *timestamp);
int	initializeMinHeap( MinHeap *, Comparator, unsigned int elemsize );
int	addElement( MinHeap *, void * );
void *	removeMin( MinHeap *, void * buffer );
void *	getMin( MinHeap * );
void	destroyMinHeap( MinHeap * );

#endif

#include "MinHeap.h"

int now;
int wait;
MinHeap		minHeap;
pthread_mutex_t lock_unlock = PTHREAD_MUTEX_INITIALIZER;



void *reader()
{

    pthread_mutex_lock(&lock_unlock);

    char line[100];
    int line_count = 0;
    int x = 0;

    char *line_array[100];

    while (fgets(line, sizeof(line), stdin) != NULL) 
    {
        line_count++;
        addElement(&minHeap, line);
        x++;
     }
     
    pthread_mutex_unlock(&lock_unlock);
}

void *sequencer()
{
    char *p;

    int wait;        

    pthread_mutex_lock(&lock_unlock);

     while(1)
     { 
     
	    if (removeMin( &minHeap, &p) == 0 )
	    {
		     printf( "All events completed.\n" );
		     break;
	         
	    }

	    wait = parseTime((char*) &p) - now;

	    printf("%d seconds until next action\n", wait);

	    if (wait < 0) // skips items scheduled before initial startingtime
	    {
	    	printf("Event scheduled in the  past, time travel isnt possible\n");
	    	continue;
	    }

		now = parseTime((char*) &p);

	    sleep(wait);

	    
	    printf("%s\n", (char*) &p);

     }

     
     pthread_mutex_unlock(&lock_unlock);


	exit(1);
}




static int stringCompare( const void * p1, const void * p2 )
{
	 const char *s1 = p1;
	 const char *s2 = p2;

	 return strcmp(s1, s2);
}

 void printHeap( MinHeap * minHeap )
{
	unsigned int	i, limit;
	int		x;

	limit = minHeap->elemcount;
	printf( "[ " );
	for ( i = 0 ; i < limit ; i++ )
	{
		x = *((int *)(minHeap->block + i * sizeof(long)));
		printf( "%d ", x );
	}
	printf( "]\n" );
}




int parseTime(char *timestamp)
{

    int yyyy,ddd,hh,mm,ss;

    sscanf(timestamp,"%d/%d/%d/%d/%d", &yyyy,&ddd,&hh,&mm,&ss);

    int time = (yyyy * 31536000) + (ddd * 86400) + (hh * 3600) +
    			(mm * 60) + (ss * 1);

    return time;



}




int main(int argc, char **argv)
{

	if (argc < 2)
	{
		fprintf(stderr, "Need a initial command line argument.\n");
		return 0;
	}
    

    time_t timer;
    struct tm* tm_info;

	 now = parseTime(argv[1]); 

	initializeMinHeap(&minHeap, stringCompare, sizeof(long) * 20);


	pthread_t reader_thread, sequencer_thread;

	if(pthread_create(&reader_thread, NULL, reader, NULL))
	{
		fprintf(stderr, "Error creating thread\n");
		return -1;
	}

	if(pthread_join(reader_thread,NULL))
	{
		fprintf(stderr, "Error joining thread\n");
		return -1;
	}

	if(pthread_create(&sequencer_thread, NULL, sequencer,NULL))
	{
		fprintf(stderr, "Error creating thread\n");
		return -1;
	}

	if(pthread_join(sequencer_thread, NULL))
	{
		fprintf(stderr, "Error joining thread\n");
		return -1;
	}
 

   destroyMinHeap(&minHeap);
    
	return 0;	
}
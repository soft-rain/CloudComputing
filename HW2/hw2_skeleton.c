//
// 2021 Fall - Cloud Computing (01)
// Homework #2: Pthread Programming
//
// Copyright (c) Prof. Jaehyeong Sim
// Department of Computer Science and Engineering, Ewha Womans University
//

#include <stdio.h>
#include <pthread.h>

#define STR_SIZE 128

char original_string[STR_SIZE] = "Computer, Ewha";

void* get_str(void *data) //data : threadid, (void*)data = target_string
{
	long tid = (long) data;	
	const char * str = (void*)data;
	//printf(str);
	printf("%d\n", sizeof(str));
	int t;
	//printf((void*)data);
	//printf("\n");
	//printf(data);
	//printf("\n");
	pthread_mutex_t mutexstr = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mutexstr, NULL);
	pthread_mutex_lock(&mutexstr);

	for(t=0; t<12; t++)
	{
		pthread_self();
		if(str[t]!='\0')
		{
			printf("Iteration %d\t thread %ld\t got %c\t from\t %s\n", t, tid, str[t], original_string);
		}
	pthread_mutex_unlock(&mutexstr);

	}
	printf("*** Thread %ld made a string : %s\n", tid, (void*)data);	

	pthread_exit(NULL);
}


int main() {

	char target_string1[STR_SIZE] = "Ewha";
	char target_string2[STR_SIZE] = "Computer";

	printf("*** The initial original string:\t\t%s\n", original_string);
		
	int NUM_THREADS = 2;
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	int i;

	
	pthread_t thread1,thread2;
	pthread_create(&threads[0], NULL, get_str, (void*)target_string1);
	pthread_create(&threads[1], NULL, get_str, (void*)target_string2);
	for(i=0; i<NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	


	printf("*** Final original string:\t\t\t%s\n", original_string);

	return 0;

}

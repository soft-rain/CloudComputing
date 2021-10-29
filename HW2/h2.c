//
// 2021 Fall - Cloud Computing (01)
// Homework #2: Pthread Programming
//
// Copyright (c) Prof. Jaehyeong Sim
// Department of Computer Science and Engineering, Ewha Womans University
//

#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define STR_SIZE 128

char original_string[STR_SIZE] = "Computer, Ewha";

void* get_str(void *data)
{
	////////////////////////
	char* str = (char*) data;
	char str2[STR_SIZE];
	strcpy(str2, str);

	int t;

	for(t=0; t<12;)
	{
		if(str[t]!='\0')
		{
			
			printf("Iteration %d\t thread %d\tgot %c\t from\t%s\n", t, pthread_self(),str[t], str );
			str[t] = '_';
			t++;
		}
		else{
			break;
		}
	}
	printf("*** Thread %d made a string: %s\n", pthread_self(), str2);
	pthread_exit(NULL);

	////////////////////////
}


int main() {

	char target_string1[STR_SIZE] = "Ewha";
	char target_string2[STR_SIZE] = "Computer";

	printf("*** The initial original string:\t\t%s\n", original_string);

	////////////////////////
	
	int NUM_THREADS = 2;
	pthread_t threads[NUM_THREADS];
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	
	pthread_create(&threads[0], NULL, get_str, target_string1);
	pthread_create(&threads[1], NULL, get_str, target_string2);

	//pthread_mutex_lock(&mutex);

	//printf("Created thread %d\n", threads[0]);
	pthread_join(threads[0], NULL);

	//pthread_mutex_unlock(&mutex);

	pthread_join(threads[1], NULL);


	////////////////////////

	printf("*** Final original string:\t\t\t%s\n", original_string);
	return 0;

}

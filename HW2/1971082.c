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
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

char original_string[STR_SIZE] = "Computer, Ewha";

void* get_str(void *data)
{
	////////////////////////
	char* str = (char*) data;

	int t=0;
	char orgstr[STR_SIZE];
	strcpy(orgstr, original_string);

	while(str[t]!='\0')
	{

		pthread_mutex_lock(&mutex);
		char currstr[STR_SIZE];

		strcpy(currstr, original_string);
		printf("Iteration %d\t thread %d\tgot %c\t from\t%s\n", t, pthread_self(),str[t], currstr );
		for (int i = 0; i < 100000; i++);

		for (int i = 0; i < strlen(original_string); i++){
			if (currstr[i]==str[t]){
				currstr[i]='_';
			}
		}

		for (int i = 0; i < 100000; i++);
		strcpy(original_string, currstr);

		t++;
		pthread_mutex_unlock(&mutex);
		

	}		

	printf("*** Thread %d made a string: %s\n", pthread_self(), str);
	for (int i = 0; i < 100000; i++);

	strcpy(original_string, orgstr);
	for (int i = 0; i < 100000; i++);

	pthread_exit(NULL);

	////////////////////////
}


int main() {

	char target_string1[STR_SIZE] = "Ewha";
	char target_string2[STR_SIZE] = "Computer";

	printf("*** The initial original string:\t\t%s\n", original_string);

	////////////////////////
	//pthread_mutex_init(&mutex, NULL);
	int NUM_THREADS = 2;
	
	int rc;

	pthread_t threads[NUM_THREADS];
	
	pthread_mutex_init(&mutex,NULL);
	
	rc = pthread_create(&threads[0], NULL, get_str, (void*)target_string1);
	
	if(rc) {
   		printf("ERROR; return code from pthread_create( ) is %d\n", rc);
   		pthread_exit(NULL);
  	}
	
	rc = pthread_create(&threads[1], NULL, get_str, (void*)target_string2);
	
	if(rc) {
   		printf("ERROR; return code from pthread_create( ) is %d\n", rc);
   		pthread_exit(NULL);
  	}
	

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	////////////////////////

	printf("*** Final original string:\t\t\t%s\n", original_string);
	return 0;

}

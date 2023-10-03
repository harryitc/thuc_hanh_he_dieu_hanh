#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char message[] = "Hello World";

void* do_thread (void* data)
{
	printf ("Thread function is executing ... \n");
	printf ("Thread data is %s\n", (char*) message);
	sleep  (3);
	strcpy (message, "Bye !");
	pthread_exit ("Thank you for using my thread");
}

int main()
{
	int res;
	pthread_t a_thread;
	void* thread_result;
	res = pthread_create (&a_thread, NULL, do_thread, (void*) message);
	if (res != 0)
	{
		perror ("Thread wait error\n");
		exit (EXIT_FAILURE);
	}
	printf ("Waiting for thread to finish ...\n");
	res = pthread_join (a_thread, &thread_result);
	if (res != 0)
	{
		perror ("Thread wait error.\n");
		exit(EXIT_FAILURE); 
	}
	printf ("Thread compeled, it returned %s \n", (char*) thread_result);
	printf ("Message is now %s \n", message);
	return 0;
}

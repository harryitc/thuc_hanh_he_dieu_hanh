#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int global_var;
pthread_mutex_t a_mutex;

void* do_thread1 (void* data);
void* do_thread2 (void* data);

int main()
{
	int res;
	int i;
	pthread_t p_thread1;
	pthread_t p_thread2;

	res = pthread_mutex_init (&a_mutex, NULL);

	if (res != 0)
	{
		perror ("Mutex create error");
		exit (EXIT_FAILURE);
	}

	res = pthread_create (&p_thread1, NULL, do_thread1, NULL);

	if (res != 0)
	{
		perror ("Thread create error");
		exit (EXIT_FAILURE);
	}

	res = pthread_create (&p_thread2, NULL, do_thread2, NULL);

	if (res != 0)
	{
		perror ("Thread create error");
		exit (EXIT_FAILURE);
	}

	for (i = 0; i < 20; i++)
	{
		printf ("Main thread waiting %d second ... \n", i);
		sleep(1);
	}
	return 0;
}

void* do_thread1 (void* data)
{
	int i;
	pthread_mutex_lock (&a_mutex);
	for (i = 1; i <= 5; i++)
	{
		printf ("Thread 1 count: %d with global value %d \n", i, global_var++);
		sleep(1);
	}
	pthread_mutex_unlock (&a_mutex);
	printf ("Thread 1 completed !\n");
}

void* do_thread2 (void* data)
{
	int i;
	pthread_mutex_lock (&a_mutex);
	for (i = 1; i <= 5; i++)
	{
		printf ("Thread 2 count: %d with global value %d \n", i, global_var--);
		sleep(2);
	}
	pthread_mutex_unlock (&a_mutex);
	printf ("Thread 2 completed !\n");
}

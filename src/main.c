#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define HAVE_STRUCT_TIMESPEC //prevent redefinition of timespec
#include <pthread.h>

int main(void)
{
	pthread_t threadShell;
	pthread_t threadLed;

	//create 2 threads:
	//1 to manage the shell and 1 to update led state
	pthread_create (&threadShell, NULL, threadUpdateShell, (void*)NULL);
	pthread_create (&threadLed, NULL, threadUpdateLEDState, (void*)NULL);

	pthread_join (threadShell, NULL);
	pthread_join (threadLed, NULL);

	return 0;
}


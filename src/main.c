#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(void)
{
    char command[255];
    char first[255];
    char second[255];
    char third[255];

    printf("Hello and welcome to the shell made in C langage!\n");
    printf("Type help to see all the available command!\n");

    while (1)
    {
        printf("C:\\test\\fornow>");
        readInput(command, first, second, third, 255);
    	if (strcmp(first, "help") == 0)
    	{
    		commandHelp();
    	}
    	else if (strcmp(first, "version") == 0)
    	{
    		commandVersion();
    	}
    	else if (strcmp(first, "led") == 0)
    	{
    		commandLed(second, third);
    	}
    	else if (strcmp(command, "\n") == 0)
    	{
    		//do nothing
    	}
    	else
    	{
    		printf("%s is not a correct command, type help to list all the available commands!\n", first);
    	}
    }
    return 0;
}


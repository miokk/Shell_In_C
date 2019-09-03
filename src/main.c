#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(void)
{
    char command[255];
    float version = 0.0;

    printf("Hello and welcome to the shell made in C langage!\n");
    printf("Type help to see all the available command!\n");

    while (1)
    {
        printf("C:\\test\\fornow>");
        readInput(command, 255);
    	if (strcmp(command, "help") == 0)
    	{
    		printf("You type the help command!\n");
    		printf("That is fantastic!\n");
    		printf("Dont worry, you will get soon the list of all available commands!\n");
    		printf("Until now, just play with the 'version' command!\n");
    	}
    	else if (strcmp(command, "version") == 0)
    	{
    		version = VERSION;
    		printf("Shell version %.2f!\n", version);
    	}
    	else
    	{
    		printf("command not available, type help to see all the available command!\n");
    	}
    }
    return 0;
}


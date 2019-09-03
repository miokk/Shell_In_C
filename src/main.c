#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 0.1

int main(void)
{
    char command[255];
    float version = 0.0;

    printf("Hello and welcome to the shell made in C langage!\n");
    printf("Type help to see all the available command!\n");

    while (1)
    {
        printf("C:\\test\\fornow>");
    	scanf("%s", command);
    	if (strcmp(command, "help") == 0)
    	{
    		printf("Vous avez tape la commande help!\n");
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


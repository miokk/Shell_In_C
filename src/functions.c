#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// get the input from keyboard and remove the \0 at the and of the string
int readInput(char *command, int length)
{
    char *inputIndex = NULL;

    if (fgets(command, length, stdin) != NULL)
    {
        inputIndex = strchr(command, '\n');
        if (inputIndex != NULL)
        {
            *inputIndex = '\0';
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

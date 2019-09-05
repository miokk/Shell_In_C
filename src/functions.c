#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

//
int Mask_led = 0;

int readInput(char *Command, char *FirstWord, char *SecondWord, char *ThirdWord, int Length)
{
	char *tab = malloc(sizeof(char) * strlen(Command));
	int returnValue;

	// get the input from the user
	if (fgets(Command, Length, stdin) != NULL)
	{
		//don't do anything when the user press enter without command
		if (strcmp(Command, "\n") != 0)
		{
			//remove the \n at the end.
			tab = strchr(Command, '\n');
			if (tab != NULL)
			{
				*tab = '\0';
			}
			//get the word of the command and separate it by detecting space between word
			if (Command != NULL)
			{
				tab = strtok(Command, " ");
				strcpy(FirstWord, tab);

				tab = strtok(NULL, " ");
				if (tab!=NULL)
				{
					strcpy(SecondWord, tab);

					tab = strtok(NULL, " ");
					if (tab!=NULL)
					{
						strcpy(ThirdWord, tab);
					}
				}
			}
		}
		returnValue = 1;
	}
	else
	{
		returnValue = 0;
	}

	//liberate the allocation memory
	free(tab);

	return returnValue;
}

void commandHelp(void)
{
	printf("You type the help command!\n");
	printf("That is fantastic!\n");
	printf("Dont worry, you will get soon the list of all available commands!\n");
	printf("Until now, just play with the 'version' command!\n");
}

void commandVersion(void)
{
	float version = VERSION;
	printf("Shell version %.2f!\n", version);
}

void commandLed(char *SecondWord, char *ThirdWord)
{
	int i;
	int mask;
	if (strcmp(SecondWord, "on") == 0)
	{
		//enable led X
		Mask_led |= 1<<atoi(ThirdWord);
		printf("LED%d is ON\n", atoi(ThirdWord));
	}
	else if (strcmp(SecondWord, "off") == 0)
	{
		//disable led X
		Mask_led &= (int)~(1<<atoi(ThirdWord));
		printf("LED%d is OFF\n", atoi(ThirdWord));
	}
	else if (strcmp(SecondWord, "status") == 0)
	{
		//show all the led status
		for(i=0; i<16; i++)
		{
			mask = (Mask_led & (1<<i))>>i;
			printf("LED%d is %d\n", i, mask);
		}
	}
	else
	{
		printf("Problem, \'%s\' is incorrect. Type help to list all the available commands\n", SecondWord);
	}
}


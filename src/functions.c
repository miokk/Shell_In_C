#include "functions.h"

//16 LEDs
Ledstatus LedStatus[16];

int readInput(char *Command, char *FirstWord, char *SecondWord, char *ThirdWord, char *FourthWord, int Length)
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

						tab = strtok(NULL, " ");
						if (tab!=NULL)
						{
							strcpy(FourthWord, tab);
						}
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

void commandLed(char *SecondWord, char *ThirdWord, char *FourthWord)
{
	int i;

	if (strcmp(SecondWord, "on") == 0)
	{
		//enable led X
		LedStatus[atoi(ThirdWord)].ledState = LED_ON;
		printf("LED%d is ON\n", atoi(ThirdWord));
	}
	else if (strcmp(SecondWord, "off") == 0)
	{
		//disable led X
		LedStatus[atoi(ThirdWord)].ledState = LED_OFF;
		printf("LED%d is OFF\n", atoi(ThirdWord));
	}
	else if (strcmp(SecondWord, "start-blink") == 0)
	{
		//Activate Blink mode for X
		LedStatus[atoi(ThirdWord)].blinkState = 1;
		//get the start timer
		LedStatus[atoi(ThirdWord)].startTimer = clock();
		//Get the blink delay
		LedStatus[atoi(ThirdWord)].blinkDelay_ms = atoi(FourthWord);
	}
	else if (strcmp(SecondWord, "status") == 0)
	{
		//show all the led status
		for(i=0; i<16; i++)
		{
			printf("LED%d is %d\n", i, LedStatus[i].ledState);
		}
	}
	else
	{
		printf("Problem, \'%s\' is incorrect. Type help to list all the available commands\n", SecondWord);
	}
}

void reverseLedState(int LedID)
{
	LedStatus[LedID].ledState=~LedStatus[LedID].ledState;
	printf("LED%d changed to %d\n", LedID, LedStatus[LedID].ledState);
}

void test(void)
{
	clock_t start = clock(), diff;
	reverseLedState(3);
	diff = clock() - start;

	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
}

void updateLEDState(void)
{
	int i;
	clock_t diff;

	for(i=0; i<16; i++)
	{
		//check if blink mode is active
		if (LedStatus[i].blinkState==1)
		{
			printf("active\n");
			diff = clock() - LedStatus[i].startTimer;
			diff = diff * 1000 / CLOCKS_PER_SEC;
			printf("delay %d\n", LedStatus[i].blinkDelay_ms);
			printf("startimer %d\n", (int)LedStatus[i].startTimer);
			printf("clock() %d\n", (int)clock());

			if(diff>LedStatus[i].blinkDelay_ms)
			{
				reverseLedState(i);
				LedStatus[i].startTimer = clock();
			}
		}
	}
}

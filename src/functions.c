#include "functions.h"

//LEDs status
Ledstatus LedStatus[NUMBER_LED];

//debug
int DebugEnable = 0;

////////////////////////////////////////////////////////////////////
/////////////////////Manage the user commands'//////////////////////
////////////////////////////////////////////////////////////////////
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
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
//////////////////function for the command 'help'///////////////////
////////////////////////////////////////////////////////////////////
void commandHelp(void)
{
	printf("You type the help command!\n");
	printf("That is fantastic!\n");
	printf("Dont worry, you will get soon the list of all available commands!\n");
	printf("Until now, just play with the 'version' command!\n");
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
////////////////function for the command 'version'//////////////////
////////////////////////////////////////////////////////////////////
void commandVersion(void)
{
	float version = VERSION;
	printf("Shell version %.2f!\n", version);
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
/////////////////function for the command 'led + X'////////////////
////////////////////////////////////////////////////////////////////
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
	else if (strcmp(SecondWord, "stop-blink") == 0)
	{
		//Activate Blink mode for X
		LedStatus[atoi(ThirdWord)].blinkState = 0;
	}
	else if (strcmp(SecondWord, "status") == 0)
	{
		//show all the led status
		for(i=0; i<NUMBER_LED; i++)
		{
			printf("LED%d is %d\n", i, LedStatus[i].ledState);
		}
	}
	else
	{
		printf("Problem, \'%s\' is incorrect. Type help to list all the available commands\n", SecondWord);
	}
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
////////////////////function to activate the debug//////////////////
////////////////////////////////////////////////////////////////////
void commandDebug(char *SecondWord)
{
	if (strcmp(SecondWord, "on") == 0)
	{
		//enable led X
		DebugEnable = 1;
		printf("Debug is now activated\n");
	}
	else
	{
		DebugEnable = 0;
		printf("Debug is now deactivated\n");
	}
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
//////////////function to reverse the state of the LED//////////////
////////////////////////////////////////////////////////////////////
void reverseLedState(int LedID)
{
	LedStatus[LedID].ledState=!LedStatus[LedID].ledState;
	if (DebugEnable==1)
	{
		printf("LED%d changed to %d\n", LedID, LedStatus[LedID].ledState);
	}
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
///////////////////////function for the shell///////////////////////
////////////////////////////////////////////////////////////////////
void* threadUpdateShell (void* arg)
{
	char command[255];
	char first[255];
	char second[255];
	char third[255];
	char fourth[255];

	printf("Hello and welcome to the shell made in C langage!\n");
	printf("Type help to see all the available command!\n");

	while (1)
	{
		printf("C:\\test\\fornow>");
		readInput(command, first, second, third, fourth, 255);
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
			commandLed(second, third, fourth);
		}
		else if (strcmp(first, "debug") == 0)
		{
			commandDebug(second);
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
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
//////////////function which update all the LEDs state//////////////
////////////////////////////////////////////////////////////////////
void* threadUpdateLEDState (void* arg)
{
	int i;
	clock_t diff;
	while(1)
	{
		//loop on all LED.
		for(i=0; i<NUMBER_LED; i++)
		{
			//check if blink mode is active
			if (LedStatus[i].blinkState==1)
			{
				diff = clock() - LedStatus[i].startTimer;
				diff = diff * 1000 / CLOCKS_PER_SEC;

				if(diff>LedStatus[i].blinkDelay_ms)
				{
					reverseLedState(i);
					LedStatus[i].startTimer = clock();
				}
			}
		}
	}
}
/////////////////////////////////END////////////////////////////////

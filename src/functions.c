#include "functions.h"

//LEDs status
Ledstatus LedStatus[NUMBER_LED];

//debug ON/OFF
int DebugEnable = 1;

//structure with all commands
CommandeDef *InputCommand[NUMBER_COMMAND];

//string contain separate words of the command put by user
char CommandWords[MAX_WORDS][MAX_LENGTH];

////////////////////////////////////////////////////////////////////
////////////This function initialize all the different//////////////
////////////with their help instruction/////////////////////////////
////////////////////////////////////////////////////////////////////
void initCommand(void)
{
	int i;

	for (i=0; i<NUMBER_COMMAND; i++)
	{
		InputCommand[i] = malloc(sizeof(CommandeDef));
	}

	////////////HELP////////////
	InputCommand[0]->command = "help";
	InputCommand[0]->commandhelp = "This command show all the available commands with the documentation.";
	InputCommand[0]->function = commandHelp;

	////////////VERSION////////////
	InputCommand[1]->command = "version";
	InputCommand[1]->commandhelp = "This command display the actual version of the software.";
	InputCommand[1]->function = commandVersion;

	////////////LED////////////
	InputCommand[2]->command = "led";
	InputCommand[2]->commandhelp = "This command needs to have argument(s):\n"
			"        led on <led_id> => turn ON the LED ID X\n"
			"        led off <led_id> => turn OFF the LED ID X\n"
			"        led start-blink <led_id> <delay>: Blink led <led_id> with a <delay> in ms between on and off\n"
			"        led stop-blink <led_id>: Stop the blinking led <led_id>\n"
			"        led stop-blink all: Stop all the blinking leds";
	InputCommand[2]->function = commandLed;

	////////////PWD////////////
	InputCommand[3]->command = "pwd";
	InputCommand[3]->commandhelp = "This command shows the current working directory";
	InputCommand[3]->function = commandPwd;

	////////////DEBUG////////////
	InputCommand[4]->command = "debug";
	InputCommand[4]->commandhelp = "turn on/off the debug:\n"
			"          debug on / debug off";
	InputCommand[4]->function = commandDebug;
}

////////////////////////////////////////////////////////////////////
/////////////////////Manage the user commands'//////////////////////
////////////////////////////////////////////////////////////////////
int readInput(char *Command, int Length)
{
	char *tab = malloc(sizeof(char) * strlen(Command));
	int returnValue;
	int i = 0;

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
				strcpy(CommandWords[0], tab);
				tab = strtok(NULL, " ");
				while(tab!=NULL)
				{
					i++;
					strcpy(CommandWords[i], tab);
					tab = strtok(NULL, " ");
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
	int i;
	printf("This is all the available commands:\n");
	for (i=0; i<NUMBER_COMMAND; i++)
	{
		printf("- %s : %s\n", InputCommand[i]->command, InputCommand[i]->commandhelp);
	}
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
void commandLed(void)
{
	int i;

	//"led on" command
	if (strcmp(CommandWords[1], "on") == 0)
	{
		//enable led X
		LedStatus[atoi(CommandWords[2])].ledState = LED_ON;
		printf("LED%d is ON\n", atoi(CommandWords[2]));
	}
	//"led off" command
	else if (strcmp(CommandWords[1], "off") == 0)
	{
		//disable led X
		LedStatus[atoi(CommandWords[2])].ledState = LED_OFF;
		printf("LED%d is OFF\n", atoi(CommandWords[2]));
	}
	//"led start-blink" command
	else if (strcmp(CommandWords[1], "start-blink") == 0)
	{
		if (((atoi(CommandWords[2])>0) && (atoi(CommandWords[2])<NUMBER_LED)) ||
				(strcmp(CommandWords[2], "0") == 0))
		{
			//Activate Blink mode for X
			LedStatus[atoi(CommandWords[2])].blinkState = 1;
			//get the start timer
			LedStatus[atoi(CommandWords[2])].startTimer = clock();
			if ((atoi(CommandWords[3])>0) && (atoi(CommandWords[3])<100000))
			{
				//Get the blink delay
				LedStatus[atoi(CommandWords[2])].blinkDelay_ms = atoi(CommandWords[3]);
			}
		}
		else
		{
			printf("Problem, \'%s\' is incorrect. Type help to list all the available commands\n", CommandWords[2]);
		}
	}
	else if (strcmp(CommandWords[1], "stop-blink") == 0)
	{
		if (strcmp(CommandWords[2], "all") == 0)
		{
			//disable all blink led
			for(i=0; i<NUMBER_LED; i++)
			{
				LedStatus[i].blinkState = 0;
			}
		}
		else
		{
			//Activate Blink mode for X
			LedStatus[atoi(CommandWords[2])].blinkState = 0;
		}
	}
	else if (strcmp(CommandWords[1], "status") == 0)
	{
		//show all the led status
		for(i=0; i<NUMBER_LED; i++)
		{
			printf("LED%d is %d\n", i, LedStatus[i].ledState);
		}
	}
	else
	{
		printf("Problem, \'%s\' is incorrect. Type help to list all the available commands\n", CommandWords[1]);
	}
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
//////////////function which display current directory//////////////
////////////////////////////////////////////////////////////////////
void commandPwd(void)
{
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	printf("Current working directory: %s\n", cwd);
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
///////////////////function for not valid command///////////////////
////////////////////////////////////////////////////////////////////
void commandotValid(void)
{
	printf("%s is not a correct command, type help to list all the available commands!\n", CommandWords[0]);
}
/////////////////////////////////END////////////////////////////////

////////////////////////////////////////////////////////////////////
////////////////////function to activate the debug//////////////////
////////////////////////////////////////////////////////////////////
void commandDebug(void)
{
	if (strcmp(CommandWords[1], "on") == 0)
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
	//print the state change when debug is enable
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
	char cwd[PATH_MAX];
	char command[255];
	int i;
	int isCommandFound = 0;//flag indicate if the command provided by the user is correct or not

	//initialize all the commands
	initCommand();

	printf("Hello and welcome to the shell made in C language!\n");
	printf("Type help to see all the available command!\n");

	while (1)
	{
		//reset isCommandFound
		isCommandFound = 0;

		getcwd(cwd, sizeof(cwd));
		printf("%s>", cwd);

		*CommandWords[0] = 0;
		readInput(command, 255);

		//loop on all commands
		for (i=0; i<NUMBER_COMMAND; i++)
		{
			if (strcmp(CommandWords[0], InputCommand[i]->command) == 0)
			{
				InputCommand[i]->function();
				isCommandFound = 1;
			}
			else if (strcmp(CommandWords[0], "") == 0)
			{
				isCommandFound = 1;
			}
		}

		if (isCommandFound==0)
		{
			//command not found
			commandotValid();
		}

	}

	//never called for now
	free(InputCommand);
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

				//reverse the state when timer > delay
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


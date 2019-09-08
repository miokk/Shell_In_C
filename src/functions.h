#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#define VERSION			0.51

#define NUMBER_COMMAND 	5
#define MAX_WORDS		20
#define MAX_LENGTH		255

#define NUMBER_LED		16
#define LED_ON			1
#define LED_OFF			0


//structure for the LED status
typedef struct Ledstatus Ledstatus;
struct Ledstatus
{
    int ledState; // state of the LED (ON/OFF)
    int blinkState; //blink activated or not (ON/OFF)
    clock_t startTimer; // start timer when state is reverse
    int blinkDelay_ms;//delay for the blink (set by user)
};

typedef struct CommandeDef CommandeDef;
struct CommandeDef
{
	char *command;
	char *commandhelp;
	void (*function) (void);
};

//functions definitions
void initCommand(void);
void* threadUpdateShell (void* arg);
void* threadUpdateLEDState (void* arg);
int readInput(char *Command, int Length);
void commandHelp(void);
void commandVersion(void);
void commandLed(void);
void commandPwd(void);
void commandDebug(void);
void commandNotValid(void);
void reverseLedState(int LedID);

#endif

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VERSION			0.4

#define NUMBER_LED		10
#define LED_ON			(int)1
#define LED_OFF			(int)0

typedef struct Ledstatus Ledstatus;
struct Ledstatus
{
    int ledState;
    int blinkState;
    clock_t startTimer;
    int blinkDelay_ms;//set by user
};

//functions definitions
int readInput(char *Command, char *FirstWord, char *SecondWord, char *ThirdWord, char *FourthWord, int Length);
void commandHelp(void);
void commandVersion(void);
void commandLed(char *SecondWord, char *ThirdWord, char *FourthWord);
void reverseLedState(int LedID);
void test(void);
void updateLEDState(void);

//struct
//typedef void (*TpDFSM_StateFunc)(void);
//typedef struct
//{
//	unsigned char u8State;
//	TpDFSM_StateFunc pfStateFunction;
//} TSTDFSM_State;
//
//typedef enum
//{
//	COMMAND1 = 0,
//	COMMAND2,
//	NBR_COMMAND,
//}AutoBRK_States;
//
//const TSTDFSM_State TstBRK_PBAState[NBR_COMMAND] = {
//		{	COMMAND1,							function1			},  //00
//		{	COMMAND2,							function2			}  	//01
//};




#endif

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#define VERSION		 0.3
#define NUMBER_LED	 10

typedef enum
{
	LED_ID_0,
	LED_ID_1,
	LED_ID_2,
	LED_ID_3,
	LED_ID_4,
	LED_ID_5,
	LED_ID_6,
	LED_ID_7,
	LED_ID_8,
	LED_ID_9,
	LED_ID_10,
	LED_ID_11,
	LED_ID_12,
	LED_ID_13,
	LED_ID_14,
	LED_ID_15,
}LedID;

//functions definitions
int readInput(char *command, char *firstWord, char *secondWord, char *thirdWord, int length);
void commandHelp(void);
void commandVersion(void);
void commandLed(char *SecondWord, char *ThirdWord);

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

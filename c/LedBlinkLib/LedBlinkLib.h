/*
 * LedBlinkLib.h
 *
 *  Created on: 2020Äê7ÔÂ6ÈÕ
 *      Author: 23864
 */

#ifndef SRC_LIB_LEDBLINKLIB_H_
#define SRC_LIB_LEDBLINKLIB_H_

typedef void (* LedBlinkSwitch)(void);

typedef struct
{
	LedBlinkSwitch on;
	LedBlinkSwitch off;
	unsigned char state;
	int onCnt;
	int offCnt;

	int onTimes;
	int offTimes;
}LedBlinkStruct;

void LedBlinkInit(LedBlinkStruct* led, LedBlinkSwitch on, LedBlinkSwitch off);
void LedBlinkConfig(LedBlinkStruct* led, int onTimes, int offTimes);

void LedBlinkAdd(LedBlinkStruct* led);
void LedBlink(void);

#endif /* SRC_LIB_LEDBLINKLIB_H_ */

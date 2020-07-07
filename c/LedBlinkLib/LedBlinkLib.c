/*
 * LedBlinkLib.c
 *
 *  Created on: 2020Äê7ÔÂ6ÈÕ
 *      Author: 23864
 */

#include "LedBlinkLib.h"

#define LED_BLINK_NUM		8

LedBlinkStruct *gLedBlinks[LED_BLINK_NUM];
int gLedBlinksNum = 0;

void LedBlinkInit(LedBlinkStruct* led, LedBlinkSwitch on, LedBlinkSwitch off)
{
	led->on = on;
	led->off = off;
	led->state = 0;
	led->onTimes = 0;
	led->offTimes = 0;
	led->onCnt = 0;
	led->offCnt = 0;
}

void LedBlinkConfig(LedBlinkStruct* led, int onTimes, int offTimes)
{
	led->onTimes = onTimes;
	led->offTimes = offTimes;
	led->onCnt = 0;
	led->offCnt = 0;
}

void LedBlinkAdd(LedBlinkStruct* led)
{
	if(gLedBlinksNum >= LED_BLINK_NUM)
		return;

	gLedBlinks[gLedBlinksNum] = led;
	gLedBlinksNum ++;
}

void LedBlink(void)
{
	for(int i=0; i<gLedBlinksNum; i++)
	{
		LedBlinkStruct* led = gLedBlinks[i];

		if(led->state == 0)
		{
			led->offCnt ++;
			if(led->offCnt >= led->offTimes)
			{
				led->offCnt = 0;
				if(led->onTimes > 0)
				{
					led->on();
					led->onCnt = 0;
					led->state = 1;
				}
			}
		}
		else
		{
			led->onCnt ++;
			if(led->onCnt >= led->onTimes)
			{
				led->onCnt = 0;
				if(led->offTimes > 0)
				{
					led->off();
					led->offCnt = 0;
					led->state = 0;
				}
			}
		}
	}
}

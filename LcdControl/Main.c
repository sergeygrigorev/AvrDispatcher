/*
* LcdControl.c
*
* Created: 15.02.2015 20:33:15
*  Author: Odmin
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Lcd.h"
#include "OneWire.h"
#include <stdlib.h>
#include <stdio.h>
#include "DS18S20.h"
#include "Dispatcher.h"

void t0();
void t1();
void t2();
void t3();

void t0()
{
	LcdSetCursor(0,0);
	LcdWrite("0");
	DspAddTimerTask(&t1,500);
}

void t1()
{
	LcdSetCursor(0,0);
	LcdWrite("1");
	DspAddTimerTask(&t0,500);
}

void t2()
{
	LcdSetCursor(1,0);
	LcdWrite("0");
	DspAddTimerTask(&t3,3000);
}

void t3()
{
	LcdSetCursor(1,0);
	LcdWrite("1");
	DspAddTimerTask(&t2,3000);
}

void supatask()
{
	LcdSetCursor(2,0);
	LcdWrite("0");
	DspDelayMs(1000);
	LcdSetCursor(2,0);
	LcdWrite("1");
	DspAddTimerTask(&supatask, 1000);
}

int main(void)
{
	LcdInit();
	DDRD = 0xff;
	PORTD = 0;
	DspAddTask(&t0);
	DspAddTask(&t2);
	DspAddTask(&supatask);
	DspInit();
}
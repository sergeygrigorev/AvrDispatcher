/*
* LcdControl.c
*
* Created: 15.02.2015 20:33:15
*  Author: Odmin
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "Lcd.h"
#include "OneWire.h"
#include <stdlib.h>
#include <stdio.h>
#include "DS18S20.h"
#include "Dispatcher.h"


uint8_t h = 0, m = 0, s = 0, temp = 0, tempDigit = 0;

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

void crash()
{
	DspDelayMs(10);
	DspAddTask(&crash);
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


void UpdateLcd()
{
	LcdSetCursor(3, 0);
	char str[21];
	sprintf(str, "%d.%d C      %02d:%02d:%02d", temp, tempDigit, h, m, s);
	LcdWrite(str);
}

void termRead()
{
	temp = TermRead();
	tempDigit = 5*(temp&1);
	temp >>= 1;
	DspAddTask(&UpdateLcd);
}

void termConv()
{
	TermConvert();
	DspAddTimerTask(&termRead, 780);
	DspAddTimerTask(&termConv, 2000);
}

void termometer()
{
	DspAddTask(&termConv);
}

void clock()
{ 
	DspAddTimerTask(&clock, 1000);
	s++;
	if (s == 60)
	{
		s = 0;
		m++;
	}
	if (m == 60)
	{
		m = 0;
		h++;
	}
	DspAddTask(&UpdateLcd);
}

void wdreset()
{
	wdt_reset();
	DspAddTimerTask(&wdreset, 100);
}

int main(void)
{
	LcdInit();
	LcdWrite("********************");
	LcdSetCursor(1, 0);
	LcdWrite("*     LALKA OS     *");
	LcdSetCursor(2, 0);
	LcdWrite("********************");
	_delay_ms(1000);
	LcdClear();
	TermInit();
	DDRD = 0xff;
	PORTD = 0;
	DspAddTask(&t0);
	DspAddTask(&t2);
	DspAddTask(&supatask);
	DspAddTask(&termometer);
	DspAddTask(&clock);
	//DspAddTimerTask(&crash, 5000);
	DspAddTask(&wdreset);
	WDTCR = 0x1f;
	DspInit();
}
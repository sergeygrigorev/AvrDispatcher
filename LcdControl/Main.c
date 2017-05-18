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
#include "Can.h"
#include "SevenSeg.h"


uint8_t temp = 0, tempDigit = 0, idx = 16;
uint8_t data[8];

void d3()
{
	SevenSegWrite(tempDigit, 0);
	DspAddTimerTask(SevenSegClear, 500);
}

void d2()
{
	SevenSegWrite(temp % 10, 0);
	DspAddTimerTask(d3, 500);
}

void d1()
{
	SevenSegWrite(temp / 10, 0);
	DspAddTimerTask(d2, 500);
}

void d0()
{
	SevenSegWriteChar('T', 0);
	DspAddTimerTask(d1, 500);
}

void quad()
{
	uint8_t i, j;
	idx--;
	i = idx >> 1;
	j = idx & 1;
	
	SevenSegWrite((data[7-i] >> (4 * j)) & 0xf, idx & 1);
	if (idx)
		DspAddTimerTask(quad, 500);
	else {
		DspAddTimerTask(SevenSegClear, 500);
		DspAddTimerTask(quad, 1000);
		idx = 16;
	}
}

void termRead()
{
	temp = TermReadTemp();
	tempDigit = 5*(temp&1);
	temp >>= 1;
	DspAddTask(d0);
}

void termConv()
{
	TermConvert();
	DspAddTimerTask(termRead, 780);
	DspAddTimerTask(termConv, 3500);
}

void termometer()
{
	DspAddTask(termConv);
}

void wdreset()
{
	wdt_reset();
	DspAddTimerTask(&wdreset, 100);
}

uint8_t onError()
{
	SevenSegWrite(8, 1);
	while(1);
}

int main(void)
{
	//uint8_t i = 0;
	
	//LcdInit();
	//LcdWrite("********************");
	//LcdSetCursor(1, 0);
	//LcdWrite("*     LALKA OS     *");
	//LcdSetCursor(2, 0);
	//LcdWrite("********************");
	//_delay_ms(1000);
	//LcdClear();
	//TermInit();
	//DDRD = 0xff;
	//PORTD = 0;
	//
	//UCSRB |= (1<<RXEN)|(1<<TXEN)|(0<<RXCIE)|(0<<TXCIE)|(0<<UDRIE);
	//UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	//UBRRL = 51;
	//UBRRH = 0;
	
	//DDRC = 255;
	//PORTC = 254;
		
	SevenSegInit();
	TermInit();
		
	//TermReadROM(data);
	
	//DspAddTask(quad);
	
		
	//SevenSegWriteChar('D', 0);
		
	DspInit(onError);
	termometer();
	//WDTCR = 0x1f;
	DspStart();
		
	//DspAddTask(&t0);
	//DspAddTask(&t2);
	//DspAddTask(&supatask);
	//DspAddTask(&termometer);
	//DspAddTask(&clock);
	////DspAddTimerTask(&crash, 5000);
	//DspAddTask(&wdreset);
	
	//DspInit();
}
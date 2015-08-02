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

uint8_t f = 0;

uint8_t h = 0, m = 0, t = 0;

ISR(INT0_vect)
{
	f = (PIND>>2)&1;
}

int main(void)
{
	DDRA |= 0b11111000;
	PORTA &= 0b111;
	
	DDRD = 0xff;
	PORTD = 0;
	
	MCUCR |= 1 << ISC00;
	MCUCR &= ~(1 << ISC01);
	GICR |= 1 << INT0;
	sei();
	LcdInit();
	TermInit();
	char s[10];
	while(1)
	{
		LcdClear();
		
		uint8_t x = 0;
		uint8_t temp = TermRead();
		x = temp;
		PORTD = temp > 50 ? 0xff : 0;
		sprintf(s,"%d",x/2);
		LcdWrite(s);
		if(x&1)
		{
			LcdWrite(temp & 1 ? ".5" : ".0");
		}
		LcdWrite(" C ");
		if (f == 1)
		LcdWrite("ALERT ");
		t++;
		if (t == 60)
		{m++;t=0;}
		if (m == 60)
		{h++;m=0;}
		sprintf(s,"%02d:%02d:%02d",h,m,t);
		LcdWrite(s);
		uint8_t p = PIND;
		sprintf(s,"%02x",p);
		LcdWrite(" ");
		LcdWrite(s);
		_delay_ms(900);
		//f = 0;
	}
}
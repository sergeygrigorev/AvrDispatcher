/*
* LcdControl.c
*
* Created: 15.02.2015 20:33:15
*  Author: Odmin
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include "Lcd.h"
#include "OneWire.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	LcdInit();
	ow_init();
	
	while(1)
	{
		LcdClear();
		uint8_t x = ow_reset();
		ow_write(0xcc);
		ow_write(0x44);
		_delay_ms(100);
		x = ow_reset();
		ow_write(0xcc);
		ow_write(0xbe);
		x = ow_read();
		char s[2];
		sprintf(s,"%d",x/2);
		LcdWrite(s);
		if(x&1)
		LcdWrite(".5");
		LcdWrite(" C");
		_delay_ms(1000);
	}
}
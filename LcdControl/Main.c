/*
* LcdControl.c
*
* Created: 15.02.2015 20:33:15
*  Author: Odmin
*/

#include <avr/io.h>
#include "Lcd.h"
#include "OneWire.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	LcdInit();
	ow_init();
	uint8_t h = 0, m = 0, t = 0;
	char s[10];
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
		sprintf(s,"%d",x/2);
		LcdWrite(s);
		if(x&1)
		{
			LcdWrite(".5");
		}
		LcdWrite(" C ");
		t++;
		if (t == 60)
			{m++;t=0;}
		if (m == 60)
			{h++;m=0;}
		sprintf(s,"%02d:%02d:%02d",h,m,t);
		LcdWrite(s);
		_delay_ms(900);
	}
}
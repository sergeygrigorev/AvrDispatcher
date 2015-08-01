/*
 * Lcd.c
 *
 * Created: 15.02.2015 20:34:30
 *  Author: Odmin
 */ 
#include "Lcd.h"

uint8_t LcdReady()
{
	//_delay_ms(1);
	DDDR = 0;
	DPORT = 255;
	CDDR |= (1 << LCDE)|(1 << LCDRW)|(1 << LCDRS);
	CPORT &= ~((1 << LCDE)|(1 << LCDRS));
	CPORT |= 1 << LCDRW;
	_delay_ms(1);
	CPORT |= 1 << LCDE;
	_delay_ms(1);
	CPORT &= ~(1 << LCDE);
	//_delay_ms(2);
	return (DPIN&(1 << 7)) == 0 ? 1 : 0;
// 	if ((DPIN & (1 << 7)) == 0)
// 	return 1;
// 	return 0;
}

void LcdWriteData(uint8_t cmd)
{
	while(LcdReady() == 0);
	//_delay_ms(1);
	DDDR = 255;
	CDDR |= (1 << LCDE)|(1 << LCDRW)|(1 << LCDRS);
	CPORT &= ~((1 << LCDE)|(1 << LCDRW));
	CPORT |= 1 << LCDRS;
	_delay_ms(1);
	CPORT |= 1 << LCDE;
	//_delay_ms(1);
	DPORT = cmd;
	_delay_ms(1);
	CPORT &= ~(1 << LCDE);
	//_delay_ms(1);
}

void LcdWriteCmd(uint8_t cmd)
{
	while(LcdReady() == 0);
	//_delay_ms(1);
	DDDR = 255;
	CDDR |= (1 << LCDE)|(1 << LCDRW)|(1 << LCDRS);
	CPORT &= ~((1 << LCDE)|(1 << LCDRW)|(1 << LCDRS));
	_delay_ms(1);
	CPORT |= 1 << LCDE;
	//_delay_ms(1);
	DPORT = cmd;
	_delay_ms(1);
	CPORT &= ~(1 << LCDE);
	//_delay_ms(1);
}

void LcdInit()
{
	_delay_ms(100);
	LcdWriteCmd(0b00111000); // 8-bit, 2 lines, 5x8
	LcdWriteCmd(0b00000010); // Start position
	LcdWriteCmd(0b00000001); // Clear
	LcdWriteCmd(0b00001100); // Enable, no cursor
}

void LcdWriteChar(char c)
{
	uint8_t cc = c;
	LcdWriteData(cc);
}

void LcdWrite(char * s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		LcdWriteChar(s[i]);
		i++;
	}
}

void LcdSetCursor(int row, int col)
{
	
}

void LcdClear()
{
	LcdWriteCmd(0b00000010);
	LcdWriteCmd(0b00000001);
}

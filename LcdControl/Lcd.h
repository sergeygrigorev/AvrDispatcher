/*
 * Lcd.h
 *
 * Created: 15.02.2015 22:26:24
 *  Author: Odmin
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCDE 0 // E pin
#define LCDRS 1 // RS pin
#define LCDRW 2 // RW pin
#define CPORT PORTA // Command port
#define DPORT PORTC // Data port
#define CDDR DDRA // Command DDR
#define DDDR DDRC // Data DDR
#define DPIN PINC // Data PIN

#include <avr/io.h>
#include <util/delay.h>

uint8_t LcdReady();
void LcdWriteData(uint8_t cmd);
void LcdWriteCmd(uint8_t cmd);
void LcdInit();
void LcdWriteChar(char c);
void LcdWrite(char * s);
void LcdSetCursor(int row, int col);
void LcdClear();

#endif /* LCD_H_ */
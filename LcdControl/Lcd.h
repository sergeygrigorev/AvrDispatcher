#ifndef LCD_H_
#define LCD_H_

#define LCDRS 5 // RS pin
#define LCDRW 6 // RW pin
#define LCDE 7 // E pin
#define CPORT PORTD // Command port
#define CDDR DDRD // Command DDR

#define DPORT PORTC // Data port
#define DDDR DDRC // Data DDR
#define DPIN PINC // Data PIN

#include <avr/io.h>
#include <util/delay.h>

void LcdWriteData(uint8_t cmd);
void LcdWriteCmd(uint8_t cmd);
void LcdInit();
void LcdWriteChar(char c);
void LcdWrite(char * s);
void LcdSetCursor(int row, int col);
void LcdClear();

#endif /* LCD_H_ */

#include "Lcd.h"

uint8_t lcd_ready()
{
	DDDR = 0;
	DPORT = 255;
	CPORT &= ~((1 << LCDE)|(1 << LCDRS));
	CPORT |= 1 << LCDRW;
	_delay_us(125);
	CPORT |= 1 << LCDE;
	_delay_us(125);
	CPORT &= ~(1 << LCDE);
	return (DPIN&(1 << 7)) == 0 ? 1 : 0;
}

void lcd_write_data(uint8_t cmd)
{
	while(lcd_ready() == 0);
	DDDR = 255;
	CPORT &= ~((1 << LCDE)|(1 << LCDRW));
	CPORT |= 1 << LCDRS;
	_delay_us(125);
	CPORT |= 1 << LCDE;
	DPORT = cmd;
	_delay_us(125);
	CPORT &= ~(1 << LCDE);
}

void lcd_write_cmd(uint8_t cmd)
{
	while(lcd_ready() == 0);
	DDDR = 255;
	CPORT &= ~((1 << LCDE)|(1 << LCDRW)|(1 << LCDRS));
	_delay_us(125);
	CPORT |= 1 << LCDE;
	DPORT = cmd;
	_delay_us(125);
	CPORT &= ~(1 << LCDE);
}

void lcd_init()
{
	CDDR |= (1 << LCDE)|(1 << LCDRW)|(1 << LCDRS);
	
	lcd_write_cmd(0b00111000); // 8-bit, 2 lines, 5x8
	lcd_write_cmd(0b00000010); // Start position
	lcd_write_cmd(0b00000001); // Clear
	lcd_write_cmd(0b00001100); // Enable, no cursor
}

void lcd_write_char(char c)
{
	lcd_write_data(c);
}

void lcd_write(char * s)
{
	int i = 0;
	while(s[i] != '\0')
		lcd_write_char(s[i++]);
}

void lcd_set_cursor(int row, int col)
{
	uint8_t i;
	lcd_write_cmd(0b00000010); // return home
	if(row == 1){
		row = 2;
	} else if(row == 2){
		row = 1;
	}
	for(i = 0; i < col + row * 20 ; i++){
		lcd_write_cmd(0b00010100); // move cursor right
	}	
}

void lcd_clear()
{
	lcd_write_cmd(0b00000010);
	lcd_write_cmd(0b00000001);
}

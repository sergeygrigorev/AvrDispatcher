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

void lcd_init();
void lcd_write_data(uint8_t cmd);
void lcd_write_cmd(uint8_t cmd);
void lcd_write_char(char c);
void lcd_write(char * s);
void lcd_set_cursor(int row, int col);
void lcd_clear();

#endif /* LCD_H_ */

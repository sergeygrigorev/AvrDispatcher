#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "Dispatcher.h"
#include "SevenSeg.h"
#include "Button.h"
#include "Lcd.h"
#include "UART.h"
#include "OneWire.h"
#include "DS18S20.h"

#define PORT_LEFT PORTD
#define PORT_RIGHT PORTA
#define DDR_LEFT DDRD
#define DDR_RIGHT DDRA
#define PN_LEFT 7
#define PN_RIGHT 7

uint8_t onError()
{
	lcd_write("Error");
	while(1);
	return 0;
}

uint8_t pos = 0, seg_light = 0, t = 0, x = 'a';
Button b;

uint8_t a1[] = {16, 213, 141, 158, 2, 8, 0, 62};
uint8_t a2[] = {16, 31, 177, 189, 2, 8, 0, 51};

void update_segment()
{
	PORT_LEFT &= ~(1 << PN_LEFT);
	PORT_RIGHT &= ~(1 << PN_RIGHT);
	
	if (seg_light)
	{
		seven_seg_write_number(pos % 16, t);
		PORT_RIGHT |= 1 << PN_RIGHT;
	}
	else 
	{
		seven_seg_write_number(pos / 16, t ^ 1);
		PORT_LEFT |= 1 << PN_LEFT;
	}
	seg_light ^= 1;
	DspAddTimerTask(update_segment, 1);
}

void tick()
{
	t ^= 1;
	DspAddTimerTask(tick, 1000);
}

void check_btn()
{
	if (BUTTON_CHECK_SHORT(b))
	{
		pos += (pos & 0xf) == 0xf ? -0xf : 1;
		BUTTON_CLEAR_SHORT(b);
	}
	if (BUTTON_CHECK_LONG(b))
	{
		pos += 0x10;
		BUTTON_CLEAR_LONG(b);
	}
	DspAddTimerTask(check_btn, 200);
}

void init_buttons()
{
	b.port = &PORTA;
	b.pin = &PINA;
	b.ddr = &DDRA;
	b.bit = 0;
	b.state = 0;
	DDRA &= 0b11111110;
	PORTA &= 0b11111110;
	Button ** bs = (Button **) malloc(sizeof(Button*));
	bs[0] = &b;
	button_init(bs, 1);
}

void init()
{
	//SevenSegInit();
	//DDR_LEFT |= 1 << 7;
	//DDR_RIGHT |= 1 << 7;
	//PORT_LEFT |= 1 << 7;
		
	uart_init();
	term_init();
	lcd_init();
	DspInit(onError);
		
	//init_buttons();
}

void a()
{
	if (x > 'z')
		x = 'a';
	lcd_write_char(x);
	uart_write(x);
	x++;
	DspAddTimerTask(a, 200);
}

void ab()
{
	uint8_t xxx = uart_read();
	switch(xxx)
	{
		case 'c':
			lcd_clear();
			break;
		case 'n':
			lcd_write("NIGGA");
			break;
		default:
			lcd_write_char(xxx);
	}
	
	//LcdClear();
	//LcdWriteChar(xxx);
	//UartWrite(xxx);
	//UartWrite('\n');
	DspAddTimerTask(ab, 0);
}

void term1();
void term2();
void term3(uint8_t* aaa);

void term1()
{
	term_convert(a1);
	term_convert(a2);
	DspAddTimerTask(term2, 1000);
}

void term2()
{
	lcd_clear();
	term3(a1);
	lcd_set_cursor(1, 0);
	term3(a2);
	DspAddTimerTask(term1, 1000);
}

void term3(uint8_t* aaa)
{	
	uint8_t x = term_read_temp(aaa);
	uint8_t y = x & 1;
	char* buf = (char *) malloc(sizeof(char) * 4);
	itoa(x >> 1, buf, 10);
	lcd_write(buf);
	if (y)
		lcd_write(".5");
}

void readrom()
{
	uint8_t * addr = (uint8_t *) malloc(sizeof(uint8_t) * 8);
	uint8_t i;
	ow_read_rom(addr);
	char * sss = (char *) malloc(sizeof(char) * 2);
	for (i=0;i<8;i++)
	{
		itoa(addr[i], sss, 16);
		lcd_write(sss);
	}
}

void searchrom()
{
	uint8_t * addr = (uint8_t *) malloc(sizeof(uint8_t) * 8);
	uint8_t i=0, j=0;
	char * sss = (char *) malloc(sizeof(char) * 2);
	uint8_t res = 0;
	
	do {
		res = ow_search_once(addr, res, 0xF0);
		for (i=0;i<8;i++)
		{
			itoa(addr[i], sss, 16);
			if (addr[i] <= 0xf)
				lcd_write_char('0');
			lcd_write(sss);
			uart_write(addr[i]);
		}
		lcd_write_char(' ');
		lcd_write_char(res == 0 ? 'L' : 'N');
		lcd_set_cursor(++j,0);
	} while (res != 0);
}

int main(void)
{
	init();
	
	//searchrom();
	
	//_delay_ms(2000);
	
	//DspAddTask(ab);
	DspAddTask(term1);
	
	DspStart();
	
	while(1)
	{
		a();
		_delay_ms(200);
	}		
}

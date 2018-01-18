#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "Dispatcher.h"
#include "SevenSeg.h"
#include "Button.h"
#include "Lcd.h"
#include "UART.h"

#define PORT_LEFT PORTD
#define PORT_RIGHT PORTA
#define DDR_LEFT DDRD
#define DDR_RIGHT DDRA
#define PN_LEFT 7
#define PN_RIGHT 7

uint8_t onError()
{
	LcdWrite("Error");
	while(1);
	return 0;
}

uint8_t pos = 0, seg_light = 0, t = 0, x = 'a';
Button b;

void update_segment()
{
	PORT_LEFT &= ~(1 << PN_LEFT);
	PORT_RIGHT &= ~(1 << PN_RIGHT);
	
	if (seg_light)
	{
		SevenSegWrite(pos % 16, t);
		PORT_RIGHT |= 1 << PN_RIGHT;
	}
	else 
	{
		SevenSegWrite(pos / 16, t ^ 1);
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
		
	UartInit();
	LcdInit();
	DspInit(onError);
		
	//init_buttons();
}

void a()
{
	if (x > 'z')
		x = 'a';
	LcdWriteChar(x);
	UartWrite(x);
	x++;
	DspAddTimerTask(a, 200);
}

void ab()
{
	uint8_t xxx = UartRead();
	switch(xxx)
	{
		case 'c':
			LcdClear();
			break;
		case 'n':
			LcdWrite("NIGGA");
			break;
		default:
			LcdWriteChar(xxx);
	}
	
	//LcdClear();
	//LcdWriteChar(xxx);
	//UartWrite(xxx);
	//UartWrite('\n');
	DspAddTimerTask(ab, 0);
}

int main(void)
{
	init();
		
	//LcdWrite("Hello");
	//LcdWrite("World");
	
	//_delay_ms(300);
	LcdWrite("1234567890");
	LcdSetCursor(1, 0);
	//LcdWrite("1234567890");
	//LcdSetCursor(2, 0);
	//LcdWrite("1234567890");
	//LcdSetCursor(3, 0);
	//LcdWrite("1234567890");
	//_delay_ms(500);
	
	DspAddTask(ab);
	
	DspStart();
	
	while(1)
	{
		a();
		_delay_ms(200);
	}		
}

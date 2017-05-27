#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <stdio.h>
#include "Dispatcher.h"
#include "SevenSeg.h"
#include "Button.h"

#define PORT_LEFT PORTD
#define PORT_RIGHT PORTA
#define DDR_LEFT DDRD
#define DDR_RIGHT DDRA
#define PN_LEFT 7
#define PN_RIGHT 7

uint8_t onError()
{
	SevenSegWrite(8, 1);
	while(1);
}

uint8_t pos = 0, seg_light = 0, t = 0;
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
	SevenSegInit();
	DDR_LEFT |= 1 << 7;
	DDR_RIGHT |= 1 << 7;
	PORT_LEFT |= 1 << 7;
	
	DspInit(onError);
	
	init_buttons();
}

int main(void)
{
	init();
	
	DspAddTask(button_check);
	DspAddTask(update_segment);
	DspAddTask(tick);
	DspAddTask(check_btn);
		
	DspStart();
}

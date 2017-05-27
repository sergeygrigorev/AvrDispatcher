#include "Button.h"

Button** buttons;
uint8_t length;

void button_init(Button** btns, uint8_t len)
{
	buttons = btns;
	length = len;
}

void button_check()
{
	uint8_t i;
	for (i = 0; i < length; i++)
	{
		Button* b = *buttons;
		uint8_t r = (((*(b->pin)) >> b->bit) & 1) ^ 1;
		r |= (b->state & 0b1100) >> 1;
		
		switch(r)
		{
			case 0:
			{
				if ((b->state >> 4) == BUTTON_LONG_PRESS_INTERVALS)
					b->state |= 2;
				else if ((b->state >> 4) > 0)
					b->state |= 1;
				b->state &= 0xf;
				break;
			}
			case 2:
			{
				b->state &= 0b11110011;
				break;
			}
			case 1:
			{
				b->state &= 0b11110111;
				b->state |= 0b00000100;
				break;
			}
			case 4:
			{
				b->state &= 0b11110111;
				b->state |= 0b00000100;
				break;
			}
			case 3:
			{
				b->state &= 0b11111011;
				b->state |= 0b00001000;
				break;
			}
			case 5:
			{
				if ((b->state >> 4) < BUTTON_LONG_PRESS_INTERVALS)
					b->state += 0b00010000;
				break;
			}
			default: break;
		}
	}
	
	DspAddTimerTask(button_check, 50);
}

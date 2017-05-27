#include "Encoder.h"

void encoder_check()
{
	//uint8_t state = ((PIND >> 2) & 1) | ((PIND >> 2) & 2);
	//
	//if (state != (encoder_state & 3))
		//encoder_state = (encoder_state << 2) | state;
	//if (encoder_state == 0b10000111)
	//{
		//pos += 1 + 15 * (seg_select & 1);
		//encoder_state = 0;
	//}
	//if (encoder_state == 0b01001011)
	//{
		//pos -= 1 + 15 * (seg_select & 1);
		//encoder_state = 0;
	//}
	//
	//DspAddTimerTask(encoder_check, 1);
}

#include "SevenSeg.h"

uint8_t letters[] = {119, 124, 57, 94, 121, 113, 61, 118, 48, 30, 0, 56, 0, 0, 63, 115, 103, 80, 109, 120, 62, 28, 0, 0, 110, 91};

uint8_t numbers[] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113};

uint8_t swapper[] = {A, B, C, D, E, F, G};

void seven_seg_init()
{
	SEVEN_SEG_DDR = 255;
	seven_seg_clear();
}

void _seven_seg_write(uint8_t val, uint8_t write_dot, uint8_t* map)
{
	uint8_t res = 0;
	uint8_t i;
	for (i = 0; i < 7; i++)
		res |= ((map[val]&(1<<i)) >> i) << swapper[i];
	if (write_dot)
		res |= 1 << DP;
	if (COMMON_ANODE)
		res = ~res;
	SEVEN_SEG_PORT = res;
}

void seven_seg_clear()
{
	SEVEN_SEG_PORT = COMMON_ANODE ? 255 : 0;
}

void seven_seg_write_number(uint8_t val, uint8_t write_dot)
{
	_seven_seg_write(val, write_dot, numbers);
}

void seven_seg_write_char(uint8_t val, uint8_t write_dot)
{
	_seven_seg_write(val - 'A', write_dot, letters);
}

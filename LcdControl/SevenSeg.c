#include "SevenSeg.h"

uint8_t letters[] = {119, 124, 57, 94, 121, 113, 61, 118, 48, 30, 0, 56, 0, 0, 63, 115, 103, 80, 109, 120, 62, 28, 0, 0, 110, 91};

uint8_t mapper[] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};

uint8_t swapper[] = {A, B, C, D, E, F, G};

void SevenSegInit()
{
	DDR = 255;
}

void write(uint8_t val, uint8_t write_dot, uint8_t* map)
{
	uint8_t res = 0;
	uint8_t i;
	for (i = 0; i < 7; i++)
		res |= ((map[val]&(1<<i)) >> i) << swapper[i];
	if (write_dot)
		res |= 1 << DP;
	if (COMMON_ANODE)
		res = ~res;
	PORT = res;
}

void SevenSegWrite(uint8_t val, uint8_t write_dot)
{
	write(val, write_dot, mapper);
}

void SevenSegWriteChar(uint8_t val, uint8_t write_dot)
{
	write(val - 'A', write_dot, letters);
}

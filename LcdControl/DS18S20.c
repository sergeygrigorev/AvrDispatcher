#include "OneWire.h"

#define CMD_CONVERT 0x44
#define CMD_SKIP_ROM 0xcc
#define CMD_READ_SCRATCHPAD 0xbe

void TermInit(void)
{
	ow_init();
}

void TermConvert()
{
	cli();
	ow_reset();
	ow_write(CMD_SKIP_ROM);
	ow_write(CMD_CONVERT);
	sei();
}

// To be rewritten

uint8_t TermRead(void)
{
	cli();
	ow_reset();
	ow_write(CMD_SKIP_ROM);
	ow_write(CMD_READ_SCRATCHPAD);
	return ow_read();
	sei();
}

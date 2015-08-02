#include "OneWire.h"

#define CMD_CONVERT 0x44
#define CMD_SKIP_ROM 0xcc
#define CMD_READ_SCRATCHPAD 0xbe

void TermInit(void)
{
	ow_init();
}


uint8_t TermRead(void)
{
	ow_reset();
	ow_write(CMD_SKIP_ROM);
	ow_write(CMD_CONVERT);
	_delay_ms(100);
	ow_reset();
	ow_write(CMD_SKIP_ROM);
	ow_write(CMD_READ_SCRATCHPAD);
	return ow_read();
}

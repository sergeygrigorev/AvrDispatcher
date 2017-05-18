#include "OneWire.h"

#define MAX_CMD_LENGTH 16

// ROM commands
#define CMD_SKIP_ROM 0xCC
#define CMD_READ_ROM 0x33
#define CMD_MATCH_ROM 0x55
#define CMD_SEARCH_ROM 0xF0
#define CMD_ALARM_SEARCH 0xEC

// Convert
#define CMD_CONVERT 0x44

// Scratch pad commands
#define CMD_READ_SCRATCHPAD 0xBE
#define CMD_WRITE_SCRATCHPAD 0x4E
#define CMD_COPY_SCRATCHPAD 0x48

// Unused commands
#define CMD_RECALL_E2 0xB8
#define CMD_READ_POWER_SUPPLY 0xB4

uint8_t arr[MAX_CMD_LENGTH];

void TermInit(void)
{
	ow_init();
}

void TermConvert()
{
	ow_reset();
	ow_write_byte(CMD_SKIP_ROM);
	ow_write_byte(CMD_CONVERT);
}

void TermReadROM(uint8_t* buf)
{
	ow_reset();
	ow_write_byte(CMD_READ_ROM);
	ow_read_bytes(buf, 8);
}

uint8_t TermReadTemp()
{
	ow_reset();
	ow_write_byte(CMD_SKIP_ROM);
	ow_write_byte(CMD_READ_SCRATCHPAD);
	ow_read_bytes(arr, 9);
	return arr[0];
}

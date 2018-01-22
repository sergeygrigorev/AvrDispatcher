#include "OneWire.h"

#define ONEWIRE_READ()		((ONEWIRE_PIN & _BV(ONEWIRE_BIT)) >> ONEWIRE_BIT)
#define ONEWIRE_PULL_LOW()	{ ONEWIRE_DDR |= _BV(ONEWIRE_BIT); }
#define ONEWIRE_LISTEN()	{ ONEWIRE_DDR &= ~_BV(ONEWIRE_BIT); }

// Setup of the one-wire pin
void ow_init(void)
{
	ONEWIRE_PORT &= ~_BV(ONEWIRE_BIT);
	ONEWIRE_LISTEN()
}

// Returns 0 if the sensor is present, 1 otherwise

uint8_t ow_reset(void)
{
	uint8_t status;
	ONEWIRE_PULL_LOW()
	_delay_us(480);
	ONEWIRE_LISTEN()
	_delay_us(60);
	status = ONEWIRE_READ();
	_delay_us(410);
	return status;
}

// Read Bit Function
uint8_t ow_read_bit(void)
{
	uint8_t bit;
	ONEWIRE_PULL_LOW()
	_delay_us(3);
	ONEWIRE_LISTEN()
	_delay_us(10);
	bit = ONEWIRE_READ();
	_delay_us(53);
	return bit;
}

// Write bit Function
void ow_write_bit(uint8_t bit)
{
	ONEWIRE_PULL_LOW()
	if (bit)
		_delay_us(10);
	else
		_delay_us(55);
	ONEWIRE_LISTEN()
	if (bit)
		_delay_us(60);
	else
		_delay_us(5);
}

// Read BYTE Function
uint8_t ow_read_byte(void)
{
	uint8_t byte = 0;
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		byte >>= 1;
		if (ow_read_bit())
			byte |= 0x80;
	}
	return byte;
}

// Write BYTE Function
void ow_write_byte(uint8_t byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		ow_write_bit(byte & 1);
		byte >>= 1;
	}
}

// Read n bytes to buf
void ow_read_bytes(uint8_t* buf, uint8_t n)
{
	uint8_t i;	
	for (i = 0; i < n; i++)
		buf[i] = ow_read_byte();	
}

// search procedure
uint8_t ow_search_once(uint8_t* addr, uint8_t last_descrepancy, uint8_t command)
{
	uint8_t last_zero = 0;
	uint8_t i, j, pos, input, output;
	
	ow_reset();
	ow_write_byte(command);
	
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
		{
			pos = i * 8 + j + 1;
			input = (ow_read_bit() << 1) | ow_read_bit();
			switch(input)
			{
				case 0:
					if (pos > last_descrepancy)
						output = 0;
					else if (pos < last_descrepancy)
						output = (addr[i] >> j) & 1;
					else
						output = 1;
					if (output == 0)
						last_zero = pos;
					break;
				case 1:
					output = 0;
					break;
				case 2:
					output = 1;
					break;
				default:
					return OW_SEARCH_ERROR;
			}
			if (output == 1)
			{
				ow_write_bit(1);
				addr[i] |= 1 << j;
			}
			else
			{
				ow_write_bit(0);
				addr[i] &= ~(1 << j);
			}
		}
		
	return last_zero;
}

uint8_t ow_read_rom(uint8_t* addr)
{
	ow_reset();
	ow_write_byte(0x33);
	ow_read_bytes(addr, 8);
	return 0;
}

uint8_t ow_match_rom(uint8_t* addr)
{
	uint8_t i;
	
	ow_write_byte(0x55);
	for (i = 0; i < 8; i++)
		ow_write_byte(addr[i]);
	return 0;
}


#include "OneWire.h"

#define ONEWIRE_READ()			((ONEWIRE_PIN & _BV(ONEWIRE_BIT)) >> ONEWIRE_BIT)
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
uint8_t ow_search(uint8_t* addr, uint8_t last_descrepancy)
{
	return last_descrepancy;
}

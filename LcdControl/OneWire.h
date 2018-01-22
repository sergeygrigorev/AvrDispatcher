#ifndef OneWire_h
#define OneWire_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ONEWIRE_PORT		PORTB
#define ONEWIRE_PIN			PINB
#define ONEWIRE_DDR			DDRB
#define ONEWIRE_BIT			0

#define OW_END_OF_SEARCH 127
#define OW_SEARCH_ERROR 255

// Init port (set to zero)
void ow_init(void);

// Perform a 1-Wire reset cycle
uint8_t ow_reset(void);

// Read a bit
uint8_t ow_read_bit(void);

// Write a bit
void ow_write_bit(uint8_t bit);

// Read a byte
uint8_t ow_read_byte(void);

// Write a byte
void ow_write_byte(uint8_t byte);

// Read n bytes
void ow_read_bytes(uint8_t* buf, uint8_t n);

// search devices
uint8_t ow_search_once(uint8_t* addr, uint8_t last_descrepancy, uint8_t command);

// read ROM of single device on the bus
uint8_t ow_read_rom(uint8_t* addr);

// matches ROM before command
uint8_t ow_match_rom(uint8_t* addr);

#endif

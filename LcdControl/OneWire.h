#ifndef OneWire_h
#define OneWire_h

#define ONEWIRE_PORT		PORTB
#define ONEWIRE_PIN			PINB
#define ONEWIRE_DDR			DDRB
#define ONEWIRE_PN			0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Init port (set to zero)
void ow_init(void);

// Perform a 1-Wire reset cycle
uint8_t ow_reset(void);

// Read a bit
uint8_t ow_read_bit(void);

// Write a bit
void ow_write_bit(uint8_t bit);

// Read a byte
uint8_t ow_read(void);

// Write a byte
void ow_write(uint8_t byte);

#endif
#ifndef DS18S20_H_
#define DS18S20_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void term_init(void);

void term_convert(uint8_t* addr);

uint8_t term_read_temp(uint8_t* addr);

#endif /* DS18S20_H_ */

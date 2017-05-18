#ifndef DS18S20_H_
#define DS18S20_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void TermInit(void);

void TermConvert();

void TermReadROM(uint8_t* buf);

uint8_t TermReadTemp();

#endif /* DS18S20_H_ */

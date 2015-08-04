#ifndef DS18S20_H_
#define DS18S20_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void TermInit(void);

uint8_t TermRead(void);

void TermConvert();

#endif /* DS18S20_H_ */
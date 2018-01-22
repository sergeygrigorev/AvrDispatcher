#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include <avr/io.h>

#define COMMON_ANODE 1

#define SEVEN_SEG_PORT PORTC
#define SEVEN_SEG_DDR DDRC

#define A 0
#define B 1
#define C 2
#define D 6
#define E 3
#define F 4
#define G 7
#define DP 5

void seven_seg_init();
void seven_seg_clear();
void seven_seg_write_number(uint8_t val, uint8_t write_dot);
void seven_seg_write_char(uint8_t val, uint8_t write_dot);

#endif /* SEVENSEG_H_ */

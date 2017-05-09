/*
 * SevenSeg.h
 *
 * Created: 09.05.2017 20:16:02
 *  Author: Odmin
 */ 


#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include <avr/io.h>

#define COMMON_ANODE 1

#define PORT PORTC
#define DDR DDRC

#define A 3
#define B 4
#define C 6
#define D 5
#define E 2
#define F 1
#define G 0
#define DP 7 

void SevenSegInit();
void write(uint8_t val, uint8_t write_dot, uint8_t* map);
void SevenSegWrite(uint8_t val, uint8_t write_dot);
void SevenSegWriteChar(uint8_t val, uint8_t write_dot);

#endif /* SEVENSEG_H_ */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>
#include <stdlib.h>
#include "Dispatcher.h"

#define BUTTON_CHECK_INTERVAL 50 // milliseconds
#define BUTTON_LONG_PRESS_INTERVALS 0xF // 0xF maximum

typedef struct {
	volatile uint8_t* port;
	volatile uint8_t* ddr;
	volatile uint8_t* pin;
	uint8_t bit;
	uint8_t state;
} Button;

#define BUTTON_CHECK_SHORT(btn) (btn.state & 1)
#define BUTTON_CHECK_LONG(btn) (btn.state & 2)
#define BUTTON_CLEAR_SHORT(btn) { btn.state &= ~1; }
#define BUTTON_CLEAR_LONG(btn) { btn.state &= ~2; }

void button_check();
void button_init(Button** btns, uint8_t len);

#endif /* BUTTON_H_ */

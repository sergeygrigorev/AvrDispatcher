#ifndef ENCODER_H_
#define ENCODER_H_

#include "Dispatcher.h"

typedef struct {
	uint8_t state;
} Encoder;

void encoder_check();

#endif /* ENCODER_H_ */

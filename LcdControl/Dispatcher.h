#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define PRESCALER 64
#define TICKS_PER_SECOND 1000
#define TIMER_COMP_NUMBER (F_CPU/TICKS_PER_SECOND/PRESCALER)

#define QUEUE_SIZE 32
#define TIMER_QUEUE_SIZE 32

typedef void (*Task)(void);
typedef uint8_t (*ErrorHandler)(void);

void DspInit();
void DspStart();
void DspAddTask(Task t);
void DspClearQueue();
void DspAddTimerTask(Task t, uint16_t delay);
void DspClearTimerQueue();

#endif /* DISPATCHER_H_ */

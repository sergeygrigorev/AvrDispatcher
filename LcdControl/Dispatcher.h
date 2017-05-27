#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <stdlib.h>
#include <avr/io.h>

#define PRESCALER 64
#define TIMER_COMP_NUMBER (F_CPU/1000/PRESCALER) // 1000 because we need timer to interrupt once a millisecond = 1/1000 of the second

#define QUEUE_SIZE 128
#define TIMER_QUEUE_SIZE 64

typedef void (*Task)(void);
typedef uint8_t (*ErrorHandler)(void);

void DspInit();
void DspStart();
void DspAddTask(Task t);
void DspClearQueue();
void DspAddTimerTask(Task t, uint16_t delay);
void DspClearTimerQueue();

#endif /* DISPATCHER_H_ */

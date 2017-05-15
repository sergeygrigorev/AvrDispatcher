#ifndef DISPATCHER_H_
#define DISPATCHER_H_

// Configuration

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

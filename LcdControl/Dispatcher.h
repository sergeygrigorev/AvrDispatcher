#ifndef DISPATCHER_H_
#define DISPATCHER_H_

// Configuration

#define QUEUE_SIZE 128
#define TIMER_QUEUE_SIZE 64

typedef void (*Task)(void);

void DspInit();
void DspAddTask(Task t);
void DspClearQueue();
void DspAddTimerTask(Task t, uint16_t delay);
void DspClearTimerQueue();
void DspDelayMs(uint16_t delay);
void DspAllowTimerTasks();


#endif /* DISPATCHER_H_ */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Dispatcher.h"

#define PRESCALER 64

#define TIMER_COMP_NUMBER (F_CPU/1000/PRESCALER) // 1000 because we need timer to interrupt once a millisecond = 1/1000 of the second

typedef struct  
{
	Task task;
	uint16_t delay;
} TimerTask;

TimerTask timerQueue[TIMER_QUEUE_SIZE];
uint8_t timerQueueSize = 0;

Task queue[QUEUE_SIZE];
uint8_t queueStart = 0, queueEnd = 0;

uint16_t delay = 0, inDelay = 0;

uint8_t errorOccured = 0;

ISR(TIMER0_COMP_vect)
{
	uint8_t i;
	for(i=0;i<timerQueueSize;i++)
	{
		if(timerQueue[i].delay == 0)
		{
			DspAddTask(timerQueue[i].task);
			timerQueueSize--;
			timerQueue[i] = timerQueue[timerQueueSize];
			i--;
		}
		else timerQueue[i].delay--;
	}
	if (delay > 0 && inDelay)
		delay--;
}

void Idle()
{
	cli();
	while(1);
}

void Error()
{
	cli();
	errorOccured = 1;
	while(1);
}

void SetError()
{
	cli();
	DspClearQueue();
	DspAddTask(Error);
}

void TaskManager()
{
	if (queueEnd == queueStart)
	{
		return;
	}
	cli();
	Task t = queue[queueStart];
	queueStart = (queueStart+1)%QUEUE_SIZE;
	sei();
	(*t)();
}

void DspInit()
{
	// Setup timer
	OCR0 = TIMER_COMP_NUMBER;
	TIMSK |= _BV(OCIE0);
	TCCR0 = _BV(CS00) | _BV(CS01) | _BV(WGM01); // Prescaler = 64, CTC mode
	sei();
	// Start run procedure
	while(1)
		TaskManager();
}

void DspAddTask(Task t)
{
	cli();
	queue[queueEnd++] = t;
	queueEnd %= QUEUE_SIZE;
	if (queueEnd == queueStart)
		errorOccured = 1;
	sei();
}

void DspClearQueue()
{
	cli();
	queueStart = queueEnd = 0;
	sei();
}

void DspAddTimerTask(Task t, uint16_t delay)
{
	cli();
	if(timerQueueSize == TIMER_QUEUE_SIZE)
	{
		SetError();
		return;
	}
	timerQueue[timerQueueSize].task = t;
	timerQueue[timerQueueSize].delay = delay;
	timerQueueSize++;
	sei();
}

void DspClearTimerQueue()
{
	cli();
	timerQueueSize = 0;
	sei();
}

void DspDelayMs(uint16_t dl)
{
	if (inDelay)
	{
		SetError();
		return;
	}
	PORTD = 0xff;
	cli();
	delay = dl;
	inDelay = 1;
	sei();
	while(delay)
		TaskManager();
	inDelay = 0;
	PORTD = 0;
	return;
}

void DspAllowTimerTasks()
{
	
}

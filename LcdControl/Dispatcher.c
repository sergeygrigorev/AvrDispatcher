#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
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

ErrorHandler errorHandler;

uint16_t ticks = 0;

ISR(TIMER0_COMP_vect)
{
	ticks++;
}

void DecreaseCounters()
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
}

void TaskManager()
{
	wdt_reset();
	
	while (ticks)
	{
		DecreaseCounters();
		cli();
		ticks--;
		sei();
	}
	
	if (queueEnd == queueStart)
		return;
	
	Task t = queue[queueStart++];
	queueStart = queueStart % QUEUE_SIZE;
	t();
}

void DspInit(ErrorHandler onError)
{
	OCR0 = TIMER_COMP_NUMBER;
	TIMSK |= _BV(OCIE0);
	TCCR0 = _BV(CS00) | _BV(CS01) | _BV(WGM01); // Prescaler = 64, CTC mode
	
	errorHandler = onError;
	//WDTCR = 0x1f;
	
	sei();
}

void DspStart()
{
	while(1)
		TaskManager();
}

void DspAddTask(Task t)
{
	if ((queueEnd + 1) % QUEUE_SIZE == queueStart)
		if (errorHandler())
			return;
			
	queue[queueEnd++] = t;
	queueEnd %= QUEUE_SIZE;
}

void DspClearQueue()
{
	queueStart = queueEnd = 0;
}

void DspAddTimerTask(Task t, uint16_t delay)
{
	if(timerQueueSize == TIMER_QUEUE_SIZE)
		if (errorHandler())
			return;
	
	timerQueue[timerQueueSize].task = t;
	timerQueue[timerQueueSize].delay = delay;
	timerQueueSize++;
}

void DspClearTimerQueue()
{
	timerQueueSize = 0;
}

#include "Dispatcher.h"

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
		// maybe it is better to compare with 1
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
	#ifdef WATCHDOG
	wdt_reset();
	#endif
	
	while (ticks > 0)
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
	// put number into comparison register
	OCR0 = TIMER_COMP_NUMBER;
	
	// set bits according to selected prescaler
	//TCCR0 = (0 << CS02) | (0 << CS01) | (1 << CS00); // Prescaler = 1
	//TCCR0 = (0 << CS02) | (1 << CS01) | (0 << CS00); // Prescaler = 8
	TCCR0 = (0 << CS02) | (1 << CS01) | (1 << CS00); // Prescaler = 64
	//TCCR0 = (1 << CS02) | (0 << CS01) | (0 << CS00); // Prescaler = 256
	//TCCR0 = (1 << CS02) | (0 << CS01) | (1 << CS00); // Prescaler = 1024
	
	// CTC mode
	TCCR0 |= (1 << WGM01);
	
	// enable Timer0 interrupt
	TIMSK |= (1 << OCIE0);
	
	errorHandler = onError;
	
	#ifdef WATCHDOG
	// enable watchdog, tick each second
	WDTCR = 0xe;
	// to disable, or 0x18, then you have 4 cycles to and 0xf7
	#endif
}

void DspStart()
{
	sei();
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

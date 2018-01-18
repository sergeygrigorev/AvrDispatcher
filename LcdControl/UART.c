#include "UART.h"

void UartInit()
{
	UCSRA = 0;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	UBRRL = BAUD;
	UBRRH = BAUD >> 8;
}

void UartWrite(uint8_t bt)
{
	// Wait until last byte has been transmitted
	while( !(UCSRA & (1 << UDRE)) );

	// Transmit data
	UDR = bt;
}

uint8_t UartRead()
{
	// Wait for data to be received
	while ( !(UCSRA & (1 << RXC)) );
	// Get and return received data from buffer
	return UDR;
}

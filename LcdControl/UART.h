#ifndef UART_H_
#define UART_H_

#include <stdlib.h>
#include <avr/io.h>

#define BAUDRATE 9600

#define BAUD (F_CPU/16/BAUDRATE-1)

void UartInit();
void UartWrite(uint8_t byte);
uint8_t UartRead();

#endif /* UART_H_ */

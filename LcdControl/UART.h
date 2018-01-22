#ifndef UART_H_
#define UART_H_

#include <stdlib.h>
#include <avr/io.h>

#define BAUDRATE 9600

void uart_init();
void uart_write(uint8_t byte);
uint8_t uart_read();

#endif /* UART_H_ */

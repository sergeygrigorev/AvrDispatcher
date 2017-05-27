#ifndef VIRTUALPORT_H_
#define VIRTUALPORT_H_

#include <stdlib.h>
#include <avr/io.h>

typedef void (*VirtualPortWriter)(uint8_t, uint8_t);
typedef void (*VirtualPortReader)(void);

typedef struct {
	VirtualPortReader reader;
	VirtualPortWriter writer;
	uint8_t port;
	uint8_t ddr;
	uint8_t pin;
	uint8_t length;
	uint8_t** ports;
	uint8_t** ddrs;
	uint8_t** pins;
	uint8_t** bits;
} VirtualPort;

void vp_write(VirtualPort vp, uint8_t ddr, uint8_t port);
void vp_read(VirtualPort vp);

#endif /* VIRTUALPORT_H_ */

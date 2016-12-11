#include "Can.h"

void CanWrite(uint8_t x)
{
	UDR = x;
}
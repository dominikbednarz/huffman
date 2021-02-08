#include "types.h"

// ustawia konkretny bit danego bajtu
Byte setBit(Byte x, unsigned int index) {
	return x | (1 << index);
}

// otrzymanie bitu
bool getBit(Byte x, unsigned int index) {
	return (x & (1 << index)) != 0;
}
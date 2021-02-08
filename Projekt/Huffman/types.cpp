#include "types.h"

// format uzytych danych // ustawienie bitu
Byte setBit(Byte x, unsigned int index) {
	return x | (1 << index);
}

// otrzymanie bitu
bool getBit(Byte x, unsigned int index) {
	return (x & (1 << index)) != 0;
}
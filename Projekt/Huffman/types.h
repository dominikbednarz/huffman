#ifndef TYPES_H
#define TYPES_H

const bool bLeft = false;
const bool bRight = true;

typedef unsigned char Byte;

// ustawia konkretny bit danego bajtu
Byte setBit(Byte x, unsigned int index);

// otrzymanie bitu
bool getBit(Byte x, unsigned int index);

#endif
#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <iostream>

void compress(std::istream& input, std::ostream& output);

bool decompress(std::istream& input, std::ostream& output);

#endif

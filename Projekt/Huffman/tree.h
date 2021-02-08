#ifndef TREE_H
#define TREE_H

#include <vector>
#include <iostream>

#include "structure.h"

void tree_map(Node* root, std::vector<bool>* codes, std::vector<bool>& prefix);

void tree_map(Node* root, std::vector<bool>* codes);

void tree_save(Node* root, std::ostream& output, Byte& accu, unsigned int& bit_id);

bool tree_load(std::istream& input, Byte& accu, unsigned int& bit_id, Node* root);

#endif
#pragma once
#include "structure.h"
using namespace std;

void tree_map(Node* root, vector<bool>* codes, vector<bool>& prefix);

void tree_map(Node* root, vector<bool>* codes);

void tree_save(Node* root, ostream& output, Byte& accu, unsigned int& bit_id);

bool tree_load(istream& input, Byte& accu, unsigned int& bit_id, Node*& root);
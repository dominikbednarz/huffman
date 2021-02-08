#include "structure.h"
#include "tree.h"
#include "compression.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void compress(istream& input, ostream& output) {
	Byte buffer;
	istream::pos_type start = input.tellg();

	vector<Node*> nodes(256);
	for (unsigned int i = 0; i < 256; ++i) {
		nodes[i] = new Node(i);
	}

	// Przechodzimy po strumieniu wejœciowym, ¿eby policzyæ liczbê wyst¹pienia ka¿dego bajtu.
	while (input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
		++(nodes[buffer]->count);
	}

	// Tworzymy drzewo.
	sort(nodes.begin(), nodes.end(), Node::greater);
	while (nodes.size() > 1) {
		Node* a, * b, * c;
		a = nodes.back();
		nodes.pop_back();
		b = nodes.back();
		nodes.pop_back();
		c = new Node(0, a, b, a->count + b->count);
		nodes.insert(upper_bound(nodes.begin(), nodes.end(), c, Node::greater), c);
	}
	Node* root = nodes.back();
	nodes.clear();

	Byte accu = 0; // Akumulator bitów.
	unsigned int bit_id = 0; // Licznik bitów.

	tree_save(root, output, accu, bit_id); // Zapisujemy drzewo.

	// Dla usprawnienia dalszych operacji zapisujemy kody w tablicy.
	vector<bool> codes[256];
	tree_map(root, codes);

	Node::tree_remove(root); // Drzewo ju¿ nie jest potrzebne.

	// Wracamy na pocz¹tek strumienia danych.
	input.clear();
	input.seekg(start);

	while (input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
		for (vector<bool>::const_iterator i = codes[buffer].begin(); i != codes[buffer].end(); ++i) {
			if (*i) {
				accu = bit_set(accu, bit_id);
			}
			++bit_id;
			if (bit_id == 8) {
				output.write(reinterpret_cast<char*>(&accu), sizeof(accu));
				bit_id = 0;
				accu = 0;
			}
		}
	}
	if (bit_id > 0) {
		output.write(reinterpret_cast<char*>(&accu), sizeof(accu));
		bit_id = 0;
		accu = 0;
	}
}

bool decompress(istream& input, ostream& output) {
	Node* root = NULL;

	Byte accu = 0;
	unsigned int bit_id = 8;

	// Wczytujemy drzewo.
	if (!tree_load(input, accu, bit_id, root)) {
		return false;
	}

	Node* current = root;
	while (true) {
		// Sprawdzamy czy nie ma b³êdu.
		if (current == NULL) {
			Node::tree_remove(root); // Sprz¹tanie.
			return false;
		}

		if (current->isLeaf()) {
			// Zapisujemy jeden bajt do wyniku.
			output.write(reinterpret_cast<char*>(&(current->byte)), sizeof(current->byte));
			current = root;
		}

		// Odczytujemy kolejny bajt.
		if (bit_id == 8) {
			if (!input.read(reinterpret_cast<char*>(&accu), sizeof(accu))) {
				break;
			}
			bit_id = 0;
		}

		// Odczytujemy jeden bit.
		bool bit = bit_get(accu, bit_id);
		++bit_id;
		if (bit == bLeft) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	Node::tree_remove(root); // Sprz¹tanie.

	return true;
}
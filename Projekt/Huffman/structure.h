#ifndef STRUCTURE_H
#define STRUCTURE_H

const bool bLeft = false;
const bool bRight = true;

typedef unsigned char Byte;

Byte bit_set(Byte x, unsigned int index);

bool bit_get(Byte x, unsigned int index);

class Node {
public:
	static bool greater(Node* a, Node* b);
	static bool less(Node* a, Node* b);
	static void tree_remove(Node* root);

	Node(Byte b, Node* l = nullptr, Node* r = nullptr, unsigned long c = 0);
	bool isLeaf() const;

	Node* left, * right;
	unsigned long count;
	Byte byte;
};

#endif
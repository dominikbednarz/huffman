#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const bool bLeft = false;
const bool bRight = true;

typedef unsigned char Byte;

Byte bit_set(Byte x, unsigned int index) {
	return x | (1 << index);
}

bool bit_get(Byte x, unsigned int index) {
	return (x & (1 << index)) != 0;
};

class Node {
public:
	static bool greater(Node* a, Node* b) {
		if (a != NULL && b != NULL) {
			return a->count > b->count;
		}
		else if (a != NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	static bool less(Node* a, Node* b) {
		if (a != NULL && b != NULL) {
			return a->count < b->count;
		}
		else if (b != NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	static void removeTree(Node* root) {
		if (root == NULL) {
			return;
		}
		removeTree(root->left);
		removeTree(root->right);
		delete root;
	}

	Node(Byte b, Node* l = NULL, Node* r = NULL, unsigned long c = 0) : left(l), right(r), count(c), byte(b) {
	}

	bool isLeaf() const {
		return this->left == NULL && this->right == NULL;
	}

	Node* left, * right;
	unsigned long count;
	Byte byte;
};
#include "structure.h"

Byte bit_set(Byte x, unsigned int index) {
	return x | (1 << index);
}

bool bit_get(Byte x, unsigned int index) {
	return (x & (1 << index)) != 0;
}

bool Node::greater(Node* a, Node* b) {
	if (a != nullptr && b != nullptr) {
		return a->count > b->count;
	}
	else if (a != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

bool Node::less(Node* a, Node* b) {
	if (a != nullptr && b != nullptr) {
		return a->count < b->count;
	}
	else if (b != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void Node::tree_remove(Node* root) {
	if (root == nullptr) {
		return;
	}
	tree_remove(root->left);
	tree_remove(root->right);
	delete root;
}

Node::Node(Byte b, Node* l, Node* r, unsigned long c) : left(l), right(r), count(c), byte(b) {}

bool Node::isLeaf() const {
	return this->left == nullptr && this->right == nullptr;
}
#include "tree.h"

// konstruktor
Node::Node(Byte b, Node* l, Node* r, unsigned long c) : left(l), right(r), count(c), byte(b) {}

// funkcja porownujaca
bool Node::greaterThan(Node* a, Node* b) {
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

// funkcja porownujaca
bool Node::lessThan(Node* a, Node* b) {
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

// usuniecie drzewa
void Node::removeTree(Node* root) {
	if (root == nullptr) {
		return;
	}
	removeTree(root->left);
	removeTree(root->right);
	delete root;
}

// sprawdza czy to list
bool Node::isLeaf() const {
	return this->left == nullptr && this->right == nullptr;
}

// Wyznacza kod dla każdego liścia w danym drzewie
void mapTree(Node* root, std::vector<bool>* codes, std::vector<bool>& prefix) {
	if (root == nullptr) {
		return;
	}

	if (root->left == nullptr && root->right == nullptr) {
		// Jesteśmy w liściu. Znaleźliśmy kod jednego bajtu.
		codes[root->byte] = prefix;
	}

	if (root->left != nullptr) {
		prefix.push_back(bLeft);
		mapTree(root->left, codes, prefix);
		prefix.pop_back();
	}
	if (root->right != nullptr) {
		prefix.push_back(bRight);
		mapTree(root->right, codes, prefix);
		prefix.pop_back();
	}
}

void mapTree(Node* root, std::vector<bool>* codes) {
	std::vector<bool> prefiks;
	mapTree(root, codes, prefiks);
}

// Zapisuje drzewo do strumienia danych
void saveTree(Node* root, std::ostream& output, Byte& accumulator, unsigned int& bitIndex) {
	if (root == nullptr) {
		return;
	}
	if (bitIndex == 8) {
		output.write(reinterpret_cast<char*>(&accumulator), sizeof(accumulator));
		accumulator = 0;
		bitIndex = 0;
	}
	if (root->isLeaf()) {
		accumulator = setBit(accumulator, bitIndex);
		++bitIndex;
		if (bitIndex == 8) {
			output.write(reinterpret_cast<char*>(&accumulator), sizeof(accumulator));
			accumulator = 0;
			bitIndex = 0;
		}
		for (unsigned int i = 0; i < 8; ++i) {
			if (getBit(root->byte, i)) {
				accumulator = setBit(accumulator, bitIndex);
			}
			++bitIndex;
			if (bitIndex == 8) {
				output.write(reinterpret_cast<char*>(&accumulator), sizeof(accumulator));
				accumulator = 0;
				bitIndex = 0;
			}
		}
	}
	else {
		++bitIndex;
		if (bitIndex == 8) {
			output.write(reinterpret_cast<char*>(&accumulator), sizeof(accumulator));
			accumulator = 0;
			bitIndex = 0;
		}
		saveTree(root->left, output, accumulator, bitIndex);
		saveTree(root->right, output, accumulator, bitIndex);
	}
}

// Wczytuje drzewo ze strumienia danych
bool loadTree(std::istream& input, Byte& accumulator, unsigned int& bitIndex, Node*& root) {
	if (bitIndex == 8) {
		if (!input.read(reinterpret_cast<char*>(&accumulator), sizeof(accumulator))) {
			return false;
		}
		bitIndex = 0;
	}
	root = new Node(0);
	bool bit = getBit(accumulator, bitIndex);
	++bitIndex;
	if (bit) {
		for (unsigned int i = 0; i < 8; ++i) {
			if (bitIndex == 8) {
				if (!input.read(reinterpret_cast<char*>(&accumulator), sizeof(accumulator))) {
					delete root;
					root = nullptr;
					return false;
				}
				bitIndex = 0;
			}
			if (getBit(accumulator, bitIndex)) {
				root->byte = setBit(root->byte, i);
			}
			++bitIndex;
		}
	}
	else {
		if (!loadTree(input, accumulator, bitIndex, root->left)) {
			delete root;
			root = nullptr;
			return false;
		}
		if (!loadTree(input, accumulator, bitIndex, root->right)) {
			Node::removeTree(root);
			root = nullptr;
			return false;
		}
	}
	return true;
}
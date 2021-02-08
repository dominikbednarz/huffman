#include "structure.h"
#include "tree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Wyzncza kod dla kazdego liscia w danym drzewie
void tree_map(Node* root, vector<bool>* codes, vector<bool>& prefix) {
	if (root == NULL) {
		return;
	}

	if (root->left == NULL && root->right == NULL) {
		// Jestesmy w lisciu. Znalezlismy kod jednego bajtu.
		codes[root->byte] = prefix;
	}

	if (root->left != NULL) {
		prefix.push_back(bLeft);
		tree_map(root->left, codes, prefix);
		prefix.pop_back();
	}
	if (root->right != NULL) {
		prefix.push_back(bRight);
		tree_map(root->right, codes, prefix);
		prefix.pop_back();
	}
}

void tree_map(Node* root, vector<bool>* codes) {
	vector<bool> prefiks;
	tree_map(root, codes, prefiks);
}

// Zapisuje drzewo do strumienia danych.
void tree_save(Node* root, ostream& output, Byte& accu, unsigned int& bit_id) {
	if (root == NULL) {
		return;
	}
	if (bit_id == 8) {
		output.write(reinterpret_cast<char*>(&accu), sizeof(accu));
		accu = 0;
		bit_id = 0;
	}
	if (root->isLeaf()) {
		accu = bit_set(accu, bit_id);
		++bit_id;
		if (bit_id == 8) {
			output.write(reinterpret_cast<char*>(&accu), sizeof(accu));
			accu = 0;
			bit_id = 0;
		}
		for (unsigned int i = 0; i < 8; ++i) {
			if (bit_get(root->byte, i)) {
				accu = bit_set(accu, bit_id);
			}
			++bit_id;
			if (bit_id == 8) {
				output.write(reinterpret_cast<char*>(&accu), sizeof(accu));
				accu = 0;
				bit_id = 0;
			}
		}
	}
	else {
		++bit_id;
		if (bit_id == 8) {
			output.write(reinterpret_cast<char*>(&accu), sizeof(accu));
			accu = 0;
			bit_id = 0;
		}
		tree_save(root->left, output, accu, bit_id);
		tree_save(root->right, output, accu, bit_id);
	}
}

// Wczytuje drzewo ze strumienia danych.
bool tree_load(istream& input, Byte& accu, unsigned int& bit_id, Node* root) {
	if (bit_id == 8) {
		if (!input.read(reinterpret_cast<char*>(&accu), sizeof(accu))) {
			return false;
		}
		bit_id = 0;
	}
	root = new Node(0);
	bool bit = bit_get(accu, bit_id);
	++bit_id;
	if (bit) {
		for (unsigned int i = 0; i < 8; ++i) {
			if (bit_id == 8) {
				if (!input.read(reinterpret_cast<char*>(&accu), sizeof(accu))) {
					delete root; // chyba powinno byc Node::tree_remove(root);
					root = NULL;
					return false;
				}
				bit_id = 0;
			}
			if (bit_get(accu, bit_id)) {
				root->byte = bit_set(root->byte, i);
			}
			++bit_id;
		}
	}
	else {
		if (!tree_load(input, accu, bit_id, root->left)) {
			delete root; // chyba powinno byc Node::tree_remove(root);
			root = NULL;
			return false;
		}
		if (!tree_load(input, accu, bit_id, root->right)) {
			Node::tree_remove(root);
			root = NULL;
			return false;
		}
	}
	return true;
}
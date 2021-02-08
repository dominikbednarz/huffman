#ifndef TREE_H
#define TREE_H

#include "types.h"
#include <iostream>
#include <vector>

// struktura uzyta do stworzenia drzewa
class Node {
public:
	Node* left, * right;
	unsigned long count;
	Byte byte;

	// konstruktor
	Node(Byte b, Node* l = nullptr, Node* r = nullptr, unsigned long c = 0);

	// funkcja porownujaca
	static bool greaterThan(Node* a, Node* b);

	// funkcja porownujaca
	static bool lessThan(Node* a, Node* b);

	// usuniecie drzewa
	static void removeTree(Node* root);

	// sprawdza czy to list
	bool isLeaf() const;


};

// Wyznacza kod dla ka¿dego liœcia w danym drzewie
void mapTree(Node* root, std::vector<bool>* codes, std::vector<bool>& prefix);
void mapTree(Node* root, std::vector<bool>* codes);

// Zapisuje drzewo do strumienia danych
void saveTree(Node* root, std::ostream& output, Byte& accumulator, unsigned int& bitIndex);

// Wczytuje drzewo ze strumienia danych
bool loadTree(std::istream& input, Byte& accumulator, unsigned int& bitIndex, Node*& root);

#endif


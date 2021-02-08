#include "operator.h"
#include "tree.h"
#include "types.h"
#include <algorithm>
#include <fstream>
#include <vector>

// konstruktor
Compressor::Compressor(std::unique_ptr<std::ifstream> input, std::unique_ptr<std::ofstream> output) :
	input_(std::move(input)), output_(std::move(output)) {};

// funkcja uruchamiajaca kompresje
void Compressor::run() {
	Compressor::compress(*input_, *output_);
}

// sprzatanie -> zamkniecie plikow
void Compressor::clean_up() {
	input_->close();
	output_->close();
}

// funkcja realizuja kompresje
void Compressor::compress(std::ifstream& input, std::ofstream& output) {
	Byte buffer;
	std::istream::pos_type start = input.tellg();

	std::vector<Node*> nodes(256);
	for (unsigned int i = 0; i < 256; ++i) {
		nodes[i] = new Node(i);
	}

	// Przechodzimy po strumieniu wejœciowym, ¿eby policzyæ liczbê wyst¹pienia ka¿dego bajtu
	while (input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
		++(nodes[buffer]->count);
	}

	// Tworzymy drzewo
	std::sort(nodes.begin(), nodes.end(), Node::greaterThan);
	while (nodes.size() > 1) {
		Node* a, * b, * c;
		a = nodes.back();
		nodes.pop_back();
		b = nodes.back();
		nodes.pop_back();
		c = new Node(0, a, b, a->count + b->count);
		nodes.insert(std::upper_bound(nodes.begin(), nodes.end(), c, Node::greaterThan), c);
	}
	Node* root = nodes.back();
	nodes.clear();

	Byte accumulator = 0; // Akumulator bitów
	unsigned int bitIndex = 0; // Licznik bitów

	saveTree(root, output, accumulator, bitIndex); // Zapisujemy drzewo

	// Dla usprawnienia dalszych operacji zapisujemy kody w tablicy
	std::vector<bool> codes[256];
	mapTree(root, codes);

	Node::removeTree(root); // Drzewo ju¿ nie jest potrzebne

	// Wracamy na pocz¹tek strumienia danych
	input.clear();
	input.seekg(start);

	while (input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
		for (std::vector<bool>::const_iterator i = codes[buffer].begin(); i != codes[buffer].end(); ++i) {
			if (*i) {
				accumulator = setBit(accumulator, bitIndex);
			}
			++bitIndex;
			if (bitIndex == 8) {
				output.write(reinterpret_cast<char*>(&accumulator), sizeof(accumulator));
				bitIndex = 0;
				accumulator = 0;
			}
		}
	}
	if (bitIndex > 0) {
		output.write(reinterpret_cast<char*>(&accumulator), sizeof(accumulator));
		bitIndex = 0;
		accumulator = 0;
	}
}

// konstruktor
Decompressor::Decompressor(std::unique_ptr<std::ifstream> input, std::unique_ptr<std::ofstream> output) :
	input_(std::move(input)), output_(std::move(output)) {};

// funkcja uruchamiajaca dekompresje
void Decompressor::run() {
	decompress(*input_, *output_);
}

// sprzatanie -> zamkniecie plikow
void Decompressor::clean_up() {
	input_->close();
	output_->close();
}

// funkcja realizuja dekompresje
void Decompressor::decompress(std::ifstream& input, std::ofstream& output) {
	Node* root = nullptr;

	Byte accumulator = 0;
	unsigned int bitIndex = 8;

	// Wczytujemy drzewo
	if (!loadTree(input, accumulator, bitIndex, root)) {
		throw "blad wczytywania drzewa z pliku";
	}

	Node* current = root;
	while (true) {
		// Sprawdzamy czy nie ma bledu
		if (current == nullptr) {
			Node::removeTree(root); // Sprz¹tanie
			throw "nieoczekiwany blad przy dekompresji";
		}

		if (current->isLeaf()) {
			// Zapisujemy jeden bajt do wyniku
			output.write(reinterpret_cast<char*>(&(current->byte)), sizeof(current->byte));
			current = root;
		}

		// Odczytujemy kolejny bajt
		if (bitIndex == 8) {
			if (!input.read(reinterpret_cast<char*>(&accumulator), sizeof(accumulator))) {
				break;
			}
			bitIndex = 0;
		}

		// Odczytujemy jeden bit
		bool bit = getBit(accumulator, bitIndex);
		++bitIndex;
		if (bit == bLeft) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	Node::removeTree(root); // Sprzatanie
}

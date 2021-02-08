#include "operator.h"
#include "types.h"
#include "tree.h"
#include <fstream>
#include <iostream>
#include <memory>

static constexpr char OUTPUT_COMPRESSED_FILE[] = "plik_skompresowany";
static constexpr char OUTPUT_DECOMPRESSED_FILE[] = "plik_zdekompresowany.txt";

// struktura do obslugi parametrow
struct ProgramParameters {
	std::string option_;
	std::string file_;

	ProgramParameters(std::string option, std::string file) : option_(std::move(option)), file_(std::move(file)) {}; // konstruktor parametrow
};

// funkcja sprawdzajaca i wybierajaca parametry
ProgramParameters parseInput(int argc, char* argv[]) {
	std::string arg1 = argv[1];
	std::string arg2 = argv[2];

	if (arg1 == "-c" || arg1 == "-d") {
		return ProgramParameters(arg1, arg2);
	}
	return ProgramParameters(arg2, arg1);
}

// inteligentne wskazniki aby moc uzyc stream do przypisania na pole klasy
std::unique_ptr<Operator> buildOperatorFromInput(ProgramParameters parameters) {
	std::unique_ptr<std::ifstream> input = std::make_unique<std::ifstream>();
	std::unique_ptr<std::ofstream> output = std::make_unique<std::ofstream>();

	// sprawdzenie poprawnosci dla kompresji
	if (parameters.option_ == "-c") {
		input->open(parameters.file_, std::ios::binary);
		if (!input->is_open()) {
			throw std::string("nie udalo sie otworzyc pliku " + parameters.file_); // wyjatek
		}

		output->open(OUTPUT_COMPRESSED_FILE, std::ios::binary);
		if (!output->is_open()) {
			input->close();
			throw std::string("nie udalo sie otworzyc pliku " + std::string(OUTPUT_COMPRESSED_FILE));
		}
		return std::make_unique<Compressor>(std::move(input), std::move(output));
	}
	// sprawdzenie poprawnosci dla kompresji
	else if (parameters.option_ == "-d") {
		input->open(parameters.file_, std::ios::binary);
		if (!input->is_open()) {
			throw std::string("nie udalo sie otworzyc pliku " + std::string(parameters.file_));
		}

		output->open(OUTPUT_DECOMPRESSED_FILE, std::ios::binary);
		if (!output->is_open()) {
			input->close();
			throw std::string("nie udalo sie otworzyc pliku " + std::string(OUTPUT_DECOMPRESSED_FILE));
		}
		return std::make_unique<Decompressor>(std::move(input), std::move(output));
	}

	throw std::string("niepoprawny argument - oczekiwano -c lub -d");
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout <<
			"Niepoprawna liczba argumentow. Oczekiwana ilosc: 2.\n" <<
			"Przyklad poprawnego wywolania programu: ./huffman -c plik_do_skompresowania.txt" << std::endl;
		return 1;
	}
	std::unique_ptr<Operator> op;

	try {
		ProgramParameters parameters = parseInput(argc, argv); // stworzenie obiektu dla parametru
		op = buildOperatorFromInput(parameters); // stworzenie obiektu ktory wykona kompresje / dekompresje
	}
	catch (std::string msg) { // jesli blad
		std::cout << "Blad przy inicjalizacji: " << msg << "." << std::endl;
		return 1;
	}

	try {
		op->run(); // wykonanie programu
		std::cout << "Wykonanie programu zakonczone sukcesem.";
	}
	catch (std::string msg) { // jesli blad
		std::cout << "Blad w wykonywaniu programu: " << msg << "." << std::endl;
	}
	op->clean_up(); // czyszczenie

	return 0;
}

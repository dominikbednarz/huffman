#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;



pair<int, int> MostFrequent(const vector<int>& vector) {
	map<int, int> m;
	for (int i = 0; i < vector.size(); i++) {
		++m[vector[i]];     // <-- tutaj inkrementujemy liczbe wystapien
	};
	auto mm = m.begin();   
	int fv = mm->second;  // <-- liczba wystapien 
	int unique = 1;    // <-- unikalne
	mm++;

	while (mm != m.end()) {
		unique++;
		if (mm->second > fv) {			// <-- sprawdzamy czy inny element ma wiecej wystapien
			fv = mm->second;
		};
		mm++;
	};
	return pair<int, int>(unique, fv);
};

void Prepare(const string& file_name) {


	fstream file;
	file.open(file_name, ios::in);
	if (file.is_open())
	{
		unordered_map<int, set<string>> mapa;
		string linia;
		string wyraz;
		while (!file.eof())
		{
			getline(file, wyraz);
			if (47 < wyraz[6] < 58) { // sprawdza czy wyraz jest numerem lini
				linia = wyraz.substr(6, wyraz.length());    // wyciecie numeru lini ktory zaczyna sie od indeksu 6
				continue;
			}
			else
			mapa[atoi(linia.c_str())].insert(wyraz);
		};
		file.close();
	};
};

int main() {
	// zad 1
	vector<int> vector {1,5,15,7,3,1,1,1,1,1};
	pair<int, int> parka = MostFrequent(vector);
	cout << parka.first << "\t" << parka.second;

	// zad 2
	string data = "linie.txt";
	Prepare(data);

	return 0;
};



#include "data.h"
#include <iostream>

int main()
{
	data_structures::list <int> przyklad;
	przyklad.add(10);
	przyklad.add(20);
	przyklad.add(30);
	przyklad.add(40);

	std::cout << "poczatek: " << przyklad.count() << "\t";
	std::cout << "koniec: " << przyklad.count() << "\t";

	return 0;
}
#include <random>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;



int main() {	
	// ZAD 1
	default_random_engine gen;
	uniform_int_distribution<int> dist(0, 10);
	vector<int> A(100);
	generate(A.begin(), A.end(), [&dist, &gen]()->int {return dist(gen); });

	sort(A.begin(), A.end());

	cout << "Przed unique:" << endl;

	for (const int& i : A) 
		cout << i << "\t";

	unique(A.begin(), A.end());

	cout << endl << "Po unique:" << endl;
	for (const int& i : A)
		cout << i << "\t";

	sort(A.begin(), A.end());
	A.erase(unique(A.begin(), A.end()), A.end());

	cout << endl << "Tylko unikalne:" << endl;
	for (const int& i : A)
		cout << i << "\t";

	cout << endl << "===============================================" << endl;

	// ZAD 2
	reverse(A.begin(), A.end());

	cout << "Po reverse:" << endl;
	for (const int& i : A)
		cout << i << "\t";

	auto result1 = find(A.begin(), A.end(), 2);
	auto result2 = binary_search(A.begin(), A.end(), 2, [](int a, int b) -> bool {return a > b; });

	cout << endl;
	if (result1 != A.end())
		cout << "Find dziala" << endl;
	if (result2 == true)
		cout << "Binarka dziala" << endl;
	else
		cout << "Binarka nie dziala" << endl;

	cout << "===============================================" << endl;

	// ZAD 3
	vector<pair<int, int>> B(100);
	poisson_distribution<int> dist2(5.0);

	generate(B.begin(), B.end(), [&gen, &dist2]()->pair<int, int> {
		pair<int, int> parka(dist2(gen), dist2(gen));
		return parka; });

	cout << "Przed sortowaniem:" << endl;
	for (pair<int, int> parka : B)
		cout << parka.first << "\t" << parka.second << endl;

	// pierwsze sortowanie (drugi element malejaco)
	sort(B.begin(), B.end(), [](pair<int, int> a, pair<int, int> b)->bool {return a.second > b.second; });

	// drugie sortowanie (pierwszy rosnaco)
	stable_sort(B.begin(), B.end(), [](pair<int, int> a, pair<int, int> b)->bool {return a.first < b.first; });

	// zwykle sort przy drugim sortowaniu nie dzialal, bo zmienial takie same elementy

	cout << "Po sortowaniu:" << endl;
	for (pair<int, int> parka : B)
		cout << parka.first << "\t" << parka.second << endl;

	return 0;
};
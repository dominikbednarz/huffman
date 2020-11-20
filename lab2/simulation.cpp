#include "simulation.h"
#include <conio.h>
#include <iostream>
using namespace std;

void Simulation::Go()
{
	Init();
	safari.Commit();
	char choose;
	while (true)
	{
		cout << "****** Nastêpna chwila ¿ycia na safari ******\n";
		safari.ShowAll();
		safari.DoAll();

		Next();
		safari.Commit();
		cout << "*********************************************\n";
		cout << "Naciœnij 'e' aby zakoñczyæ symulacjê\n";
		choose = _getch(); //only windows

		if (choose == 'e')
			break;
	}
}
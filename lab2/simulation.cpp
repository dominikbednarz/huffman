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
		cout << "****** Nast�pna chwila �ycia na safari ******\n";
		safari.ShowAll();
		safari.DoAll();

		Next();
		safari.Commit();
		cout << "*********************************************\n";
		cout << "Naci�nij 'e' aby zako�czy� symulacj�\n";
		choose = _getch(); //only windows

		if (choose == 'e')
			break;
	}
}
#include <iostream>
#include "simple_simulation.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Polish");
	Simulation *sim = new SimpleSimulation;
	sim->Go();
	delete sim;
	return 0;
}
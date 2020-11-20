#pragma once
#include "simulation.h"

class SimpleSimulation: public Simulation
{
protected:
	void Next() override {};
	void Init() override {
		safari.Add(new Animal);
	
	};

};
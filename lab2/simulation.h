#pragma once
#include "safari.h"
#include "animal.h"
class Simulation
{
protected:
	virtual void Next() = 0;

	virtual void Init() = 0;

	Safari safari;

public:
	void Go();
	~Simulation() {}
};

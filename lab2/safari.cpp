#include "safari.h"
#include "animal.h"
using namespace std;
#define VS_2010

void Safari::Add(Animal* animal)
{
	to_add.insert(animal);
}

void Safari::Remove(Animal* animal)
{
	to_remove.insert(animal);
}

void Safari::free_mem(set<Animal*>& _data)
{
#ifndef VS_2010
	for (auto animal : _data)
		delete animal;
#else
	for (set<Animal*>::iterator it = _data.begin(); it != _data.end(); ++it)
		delete *it;
#endif
}

void Safari::Commit()
{
#ifndef VS_2010
	for (auto animal : to_remove)
	{
		auto it = animals.find(animal);
		delete *it;
		animals.erase(it);
	}
#else
	for (set<Animal*>::iterator it = to_remove.begin(); it != to_remove.end(); ++it)
	{
		set<Animal*>::iterator found_it = animals.find(*it);
		delete *found_it;
		animals.erase(found_it);
	}
#endif
	to_remove.clear();
	animals.insert(to_add.begin(), to_add.end());
	to_add.clear();

}

void Safari::ShowAll()
{
#ifndef VS_2010
	for (Animal* animal : animals)
		animal->Print();
#else
	for (set<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it)
		(*it)->Show();
#endif
}

void Safari::DoAll()
{
#ifndef VS_2010
	for (Animal* animal : animals)
		animal->Do(*this);
#else
	for (set<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it)
		(*it)->Do(*this);
#endif
}


Animal* Safari::FirstAnimal()
{
	return animals.size() ? *animals.begin() : NULL;
}

void Safari::NextAnimal(Animal*& animal)
{
	set<Animal*>::iterator found_it = animals.find(animal);
	if (found_it == animals.end() || ++found_it == animals.end())
	{
		animal = NULL;
		return;
	}

	animal = *found_it;	
}


Safari::~Safari()
{
	free_mem(animals);
	free_mem(to_add);
	free_mem(to_remove);
}
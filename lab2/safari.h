#pragma once
#include <set>
class Animal;
class Safari
{
	std::set<Animal*> animals, to_remove, to_add;
	void free_mem(std::set<Animal*>& _animals);
public:

	//////////////////////////////////////////////////////////////////////////
	//Przekazywane tutaj objekty musz� by� zaalokowane przez new!
	//Dodaje nowe zwierz� do safari
	//////////////////////////////////////////////////////////////////////////
	void Add(Animal* animal);

	//////////////////////////////////////////////////////////////////////////
	//Usuwa zwierz� z safari
	//Zapewnia r�wnie� zwolnienie zaalokowanej Pami�ci!
	//////////////////////////////////////////////////////////////////////////
	void Remove(Animal* animal);

	//////////////////////////////////////////////////////////////////////////
	//Dla ka�dego dodanego objektu wywo�uje metod� Show
	//////////////////////////////////////////////////////////////////////////
	void ShowAll();

	//////////////////////////////////////////////////////////////////////////
	//Dla ka�dego dodanego objektu wywo�uje metod� Do 
	//////////////////////////////////////////////////////////////////////////
	void DoAll();

	//////////////////////////////////////////////////////////////////////////
	//Zwraca pierwsze zwierze w safari, lub NULL je�eli nie ma �adnego
	//////////////////////////////////////////////////////////////////////////
	Animal* FirstAnimal();

	//////////////////////////////////////////////////////////////////////////
	//Zmienia zwierze przekazane przez parametr na nast�pne, lub NULL je�eli 
	//nie ma kolejnego
	//////////////////////////////////////////////////////////////////////////
	void NextAnimal(Animal*& animal);

	/***********************************************************************************
	Za pomoc� metod FirstAnimal i NextAnimal mo�na przegl�da� wszystkie zwierz�ta w 
	nast�puj�cy spos�b.

	for (Animal* animal = safari.FirstAnimal(); animal; safari.NextAnimal(animal))
	{
		
	}

	************************************************************************************/

	//////////////////////////////////////////////////////////////////////////
	//Znajduje najblizsze zwierze danego typu lub NULL jezeli takiego nie ma,
	//odleglosc do niego jest zwracana przez parametr:
	//Przyklad uzycia:
	//float distance;
	// o->GetClosest<Lion>(some_animal_pointer, distance);
	//////////////////////////////////////////////////////////////////////////
	template<typename ANIMAL_T>	ANIMAL_T* GetClosest(Animal* animal, float& min_dist);

	void Commit();
	~Safari();
};























template<typename ANIMAL_T>
ANIMAL_T* Safari::GetClosest(Animal* animal, float& min_dist)
{
	ANIMAL_T* res = NULL;
	min_dist = INFINITY;
	for (std::set<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it)
	{
		if (*it == animal) //skip self
			continue;

		ANIMAL_T* candidate = dynamic_cast<ANIMAL_T*>(*it);
		if (!candidate)
			continue;

		float dist = candidate->GetPos().dist(animal->GetPos());
		if (dist < min_dist)
		{
			res = candidate;
			min_dist = dist;
		}
	}
	return res;
}
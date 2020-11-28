#pragma once
#include "safari.h"
#include <iostream>
#include "vector.h"

class Animal
{
protected:
	Vector2D pozycja;
	Vector2D kierunek;
	float predkosc;

public:
	Vector2D getPos() const {
		return pozycja;
	};

	Animal() : pozycja(Vector2D()), kierunek(Vector2D()), predkosc(0.0) {};
	Animal(double X, double Y, double x, double y, float s) : pozycja(Vector2D(X, Y)), kierunek(Vector2D(x, y)), predkosc(s) { 
		pozycja.Vector2D::normalize();
	};

	virtual void Do() = 0;

	virtual void Show()
	{
		std::cout << "metoda Show klasy Animal\n";
		std::cout << "Pozycja: " << pozycja.X << "\t" << pozycja.Y << "\n";
		std::cout << "Kierunek: " << kierunek.X << "\t" << kierunek.Y << "\n";
		std::cout << "Predkosc: " << predkosc << "\n";
	};


	Animal& run() {
		pozycja += kierunek * predkosc;
		return *this;
	};
};


class Lion: public Animal {
public:
	Lion(double X, double Y, double x, double y) : Animal(X, Y, x, y, 10.0) {};
};

class Gnu: public Animal {
public:
	Gnu(double X, double Y, double x, double y) : Animal(X, Y, x, y, 5.0) {};
};

class Hyena: public Animal {
public:
	Hyena(double X, double Y, double x, double y) : Animal(X, Y, x, y, 1.0) {};
};

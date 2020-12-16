#pragma once
using namespace std;
#include <string>

class Geometry {
private:
	string name;

public:
	virtual double perimeter () const = 0;
	virtual double area() const = 0;
	string toString() const { return name + "\n Obwod: " + to_string(perimeter()) + "\n Pole: " + to_string(area());};
	virtual ~Geometry() {};

	Geometry(const string &name) : name(name) {}; // konstruktor parametryczny
	Geometry(const Geometry& other) : name(other.name) {}; // konstruktor kopiujacy
	Geometry(Geometry&& other) : name(move(other.name)) {}; // konstruktor przenoszacy

};

class Triangle : public Geometry {
private:
	double a;

public:
	double perimeter() const override { return 3 * a; };
	double area() const override {
		double p = perimeter() / 2;
		return sqrt(p * 3 * (p - a));
	};

	Triangle(double a) : Geometry("triangle"), a(a) {};
	Triangle(const Triangle& other) : Geometry(other), a(other.a) {};
	Triangle(Triangle&& other) : Geometry(move(other)), a(other.a) {};
};

class Circle : public Geometry {
private:	
	double r;

public:
	virtual double perimeter() const override { return 2 * 3.14 * r; };
	virtual double area() const override { return 3.14 * r * r; };

	Circle(double r) : Geometry("circle"), r(r) {};
	Circle(const Circle& other) : Geometry(other), r(other.r) {};
	Circle(Circle&& other) : Geometry(move(other)), r(other.r) {};
};

class Rectangle : public Geometry {
private:
	double a;
	double b;

public:
	virtual double perimeter() const override { return 2 * a + 2 * b; };
	virtual double area() const override { return a * b; };

	Rectangle(double a, double b) : Geometry("rectangle"), a(a), b(b) {};
	Rectangle(const Rectangle& other) : Geometry(other), a(other.a), b(other.b) {};
	Rectangle(Rectangle&& other) : Geometry(move(other)), a(other.a), b(other.b) {};
};

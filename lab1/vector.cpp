#include "vector.h"
#include <iostream>
using namespace std;
#include <math.h>

Vector::Vector(float A, float B, float C) : A(A), B(B), C(C) {};

Vector::Vector(const Vector& other) : A(other.A), B(other.B), C(other.C) {};

Vector add(const Vector& one, const Vector& other) {
	float A = one.getA() + other.getA();  float B = one.getB() + other.getB(); float C = one.getC() + other.getC();
	return Vector(A, B, C);
};

float dot(const Vector& one, const Vector& other) {
	return (one.getA() * other.getA() + one.getB() * other.getB() + one.getC() * other.getC());
};

Vector cross(const Vector& one, const Vector& other) {
	float A = (one.getB() *other.getC() - one.getC() * other.getB()); float B = -(one.getA() * other.getC() - one.getC() * other.getA()); float C = (one.getA() * other.getB() - one.getB() *other.getA());
	return Vector(A, B, C);
};


#pragma once
#include <iostream>
using namespace std;
#include <math.h>

class Vector {
private: 
	float A;
	float B;
	float C;

public:
	float getA() const { return A; };
	float getB() const { return B; };
	float getC() const { return C; };
	void setA(float A) { this->A = A; };
	void setB(float B) { this->B = B; };
	void setC(float C) { this->C = C; };

	Vector() : A(0.0), B(0.0), C(0.0) {};

	Vector(float A, float B, float C);
	Vector(const Vector& other);

	void print() {
		cout << A << "/n";
		cout << B << "/n";
		cout << C << "/n";
	};

	float module() {
		return abs(sqrt(A*A + B * B + C * C));
	}
};

Vector add(const Vector& one, const Vector& other);
float dot(const Vector& one, const Vector& other);
Vector cross(const Vector& one, const Vector& other);





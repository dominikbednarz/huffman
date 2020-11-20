#pragma once
using namespace std;
#include <iostream>

class Vector2D
{
public:
	double X;
	double Y;

	Vector2D() : X(0.00), Y(0.00) {};
	Vector2D(double X, double Y) : X(X), Y(Y) {};

	Vector2D operator-(const Vector2D& b) const {
		return Vector2D(X - b.X, Y - b.Y);
	};

	Vector2D operator-() const {
		return Vector2D(-X, -Y);
	};

	Vector2D& operator+=(const Vector2D& other) {
		X += other.X; Y += other.Y;
		return *this;
	}

	Vector2D operator*(double b) const {
		return Vector2D(X * b, Y * b);
	};
	
	Vector2D& normalize() {
		double tmp = sqrt(X * X + Y * Y);
		X / tmp; Y / tmp;
		return *this;
	};

	void show() {
		cout << X << "\n";
		cout << Y << "\n";
	};

	double dist(const Vector2D& other) {
		double x = X - other.X;
		double y = Y - other.Y;
		return sqrt(x * x + y * y);
	}
};
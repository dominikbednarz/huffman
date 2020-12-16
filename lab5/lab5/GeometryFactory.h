#pragma once
#include "Geometry.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class GeometryFactory {
public:
	static Geometry* create(string& txt) {

		double a, b;
		string figura;

		stringstream tmp;
		tmp << txt;
		tmp >> figura >> a >> b;

		if (figura == "triangle") {
			Geometry* ptr = new Triangle(a);
			return ptr;
		};
		
		if (figura == "circle") {
			Geometry* ptr = new Circle(a);
			return ptr;
		};

		if (figura == "rectangle") {
			Geometry* ptr = new Rectangle(a, b);
			return ptr;
		};
	};
};
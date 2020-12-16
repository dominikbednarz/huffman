#include <string>
#include "Geometry.h"
#include "GeometryFactory.h"


int main() {
	//ZAD 4
	Triangle trojkat1(2.0);
	Triangle trojkat2(trojkat1);
	Triangle* trojkat3 = new Triangle(move(trojkat2));

	Circle kolo1(2.0);
	Circle kolo2(kolo1);
	Circle* kolo3 = new Circle(move(kolo2));

	Rectangle prostokat1(2.0, 3.0);
	Rectangle prostokat2(prostokat1);
	Rectangle* prostokat3 = new Rectangle(move(prostokat2));

	// ZAD 5
	string f1 = "circle 5";
	string f2 = "triangle 2.4";
	string f3 = "rectangle 3 10";

	auto figura1 = GeometryFactory::create(f1);
	auto figura2 = GeometryFactory::create(f2);
	auto figura3 = GeometryFactory::create(f3);

	return 0;
};
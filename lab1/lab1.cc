#include "lab1.hh"
#include <cmath>
#include <iostream>

// Computes the area between 3 points using Heron's formula
double computeArea(Point &a, Point &b, Point &c) {
	// Compute the lengths of the sides
	double sideAB = a.distanceTo(b);
	double sideBC = b.distanceTo(c);
	double sideCA = c.distanceTo(a);

	// compute the "semiperimeter" and call it "s".  Heron's forumla says the
	// area is the square root of the product of the semiperimeter and the
	// difference between the semiperimter and the length of each of the 
	// 3 sides.
	double s = ((sideAB + sideBC + sideCA) / 2);
	double area = sqrt(s * (s - sideAB) * (s - sideBC) * (s - sideCA));
	return area;
}

// Ask the user to enter coordinates for 3 points, and compute the area
// between those points and display the result.
int main() {
	double x, y, z;
	std::cout << "Enter x, y, and z coordinates for Point 1: ";
	std::cin >> x >> y >> z;
	Point p1 = Point(x, y, z);

	std::cout << "Enter x, y, and z coordinates for Point 2: ";
	std::cin >> x >> y >> z;
	Point p2 = Point(x, y, z);

	std::cout << "Enter x, y, and z coordinates for Point 3: ";
	std::cin >> x >> y >> z;
	Point p3 = Point(x, y, z);

	double area = computeArea(p1, p2, p3);
	std::cout << "The area is: " << area << std::endl;
	return area;
}
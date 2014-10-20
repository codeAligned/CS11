#include "Point.hh"
#include <cmath>


// Default constructor:  initializes the point to (0, 0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

// Initializes the point to (x, y, z).
Point::Point(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
  z_coord = val;
}

// Accessors:

double Point::getX() {
  return x_coord;
}

double Point::getY() {
  return y_coord;
}

double Point::getZ() {
  return z_coord;
}

// Member functions;

// returns the distance to another Point
double Point::distanceTo(Point &p) {
	// compute with square root of the sum of the squares of the diferences
	// in each direction
	double distance = sqrt(pow((p.getX() - x_coord), 2) + 
		pow((p.getY() - y_coord), 2) + pow((p.getZ() - z_coord), 2));
	return distance;

}

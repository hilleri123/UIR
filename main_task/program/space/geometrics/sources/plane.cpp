
#include "plane.h"

Plane::Plane(Vector vector, Point point)
	: _norm(vector), _center(point)
{}

Plane::Plane(Point first, Point second, Point third)
{
	Vector a = Vector(first, second);
	Vector b = Vector(first, third);
	_center = first;
	_norm = a*b;
}


bool Plane::operator==(const Plane& plane) const { return _center == plane._center && _norm == plane._norm; }
bool Plane::operator!=(const Plane& plane) const { return !this->operator==(plane); }
bool Plane::operator==(Plane&& plane) const { return _center == plane._center && _norm == plane._norm; }
bool Plane::operator!=(Plane&& plane) const { return !this->operator==(plane); }

Plane Plane::operator!() const { return Plane(-1 * _norm, _center); }

bool Plane::operator&(const Point& point) const
{
	double first = _norm.x() * point.x() +  _norm.y() * point.y() +  _norm.z() * point.z();
	double second = _norm.x() * _center.x() +  _norm.y() * _center.y() +  _norm.z() * _center.z();
	return first == second;
}

bool Plane::operator&(Point&& point) const
{
	double first = _norm.x() * point.x() +  _norm.y() * point.y() +  _norm.z() * point.z();
	double second = _norm.x() * _center.x() +  _norm.y() * _center.y() +  _norm.z() * _center.z();
	return first == second;
}

bool Plane::operator&(const Vector& vector) const
{
	return (vector^_norm) == atan(1)*2;
}

bool Plane::operator&(Vector&& vector) const
{
	return (vector^_norm) == atan(1)*2;
}

bool Plane::init() const
{
	if (Vector::norm(_norm) == 0) {
		return false;
	} else {
		return true;
	}
}


Plane::~Plane()
{}

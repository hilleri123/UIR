
#include "circle.h"

Circle::Circle(Vector vector, Plane plane)
	: _vector(vector), _plane(plane)
{}

Point Circle::operator()(double alpha) const
{

	return Point();
}

bool Circle::init() const
{
	if (_plane.init() || (_plane & _vector)) {
		return false;
	} else {
		return true;
	}
}

bool operator&(const Plane& plane, const Circle& circle) { return (plane == circle._plane) && (plane == !circle._plane); }
bool operator&(const Plane& plane, Circle&& circle) { return (plane == circle._plane) && (plane == !circle._plane); }
bool operator&(Plane&& plane, const Circle& circle) { return (plane == circle._plane) && (plane == !circle._plane); }
bool operator&(Plane&& plane, Circle&& circle) { return (plane == circle._plane) && (plane == !circle._plane); }

Plane Circle::plane() const
{
	return _plane;
}

Vector Circle::vector() const
{
	return _vector;
}

Circle::~Circle()
{}


#include "point.h"



Point::Point(double x, double y, double z)
	: _x(x), _y(y), _z(z)
{}

double Point::operator[](std::size_t index) const {
	if (index == 0) {
		return _x;
	} else if (index == 1) {
		return _y;
	} else if (index == 2) {
		return _z;
	} else {
		throw std::out_of_range("point");
	}
}

double Point::x() const { return _x; }
double Point::y() const { return _y; }
double Point::z() const { return _z; }

bool Point::operator==(const Point& point) const
{
	for (std::size_t i = 0; i < 3; i++) {
		if (!equal(this->operator[](i), point[i]))
			return false;
	}
	return true;
}
bool Point::operator!=(const Point& point) const { return !this->operator==(point); }

bool Point::operator==(Point&& point) const
{
	for (std::size_t i = 0; i < 3; i++) {
		if (!equal(this->operator[](i), point[i]))
			return false;
	}
	return true;
}
bool Point::operator!=(Point&& point) const { return !this->operator==(point); }
	

std::ostream& operator<<(std::ostream& stream, const Point& point) {
	stream << "(" << point._x << " " << point._y << " " << point._z << ")";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, Point&& point) {
	stream << "(" << point._x << " " << point._y << " " << point._z << ")";
	return stream;
}


double Point::norm(const Point& first, const Point& second)
{
	return sqrt(pow(second.x() - first.x(), 2) + pow(second.y() - first.y(), 2) + pow(second.z() - first.z(), 2));
}

double Point::norm(Point&& first, const Point& second)
{
	return sqrt(pow(second.x() - first.x(), 2) + pow(second.y() - first.y(), 2) + pow(second.z() - first.z(), 2));
}

double Point::norm(const Point& first, Point&& second)
{
	return sqrt(pow(second.x() - first.x(), 2) + pow(second.y() - first.y(), 2) + pow(second.z() - first.z(), 2));
}

double Point::norm(Point&& first, Point&& second)
{
	return sqrt(pow(second.x() - first.x(), 2) + pow(second.y() - first.y(), 2) + pow(second.z() - first.z(), 2));
}

bool Point::check() const
{
	return !((_x!=_x)||(_y!=_y)||(_z!=_z));
}

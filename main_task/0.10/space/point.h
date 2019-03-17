
#pragma once

#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>

#include "metrics.h"



template <typename scalar>
class Point
{
public:
	explicit Point(scalar x = 0, scalar y = 0, scalar z = 0)
		: _x(x), _y(y), _z(z)
	{}
	Point(const Point<scalar>&) = default;
	Point(Point<scalar>&&) = default;
	Point<scalar>& operator=(const Point<scalar>&) = default;
	Point<scalar>& operator=(Point<scalar>&&) = default;

	scalar operator[](std::size_t index) const {
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

	scalar x() const { return _x; }
	scalar y() const { return _y; }
	scalar z() const { return _z; }

	bool operator==(const Point<scalar>& point) const
	{
		for (std::size_t i = 0; i < 3; i++) {
			if (!equal<scalar>(this->operator[](i), point[i]))
				return false;
		}
		return true;
	}
	bool operator!=(const Point<scalar>& point) const { return !this->operator==(point); }

	bool operator==(Point<scalar>&& point) const
	{
		for (std::size_t i = 0; i < 3; i++) {
			if (!equal<scalar>(this->operator[](i), point[i]))
				return false;
		}
		return true;
	}
	bool operator!=(Point<scalar>&& point) const { return !this->operator==(point); }
	

	friend std::ostream& operator<<(std::ostream& stream, const Point<scalar>& point) {
		stream << "(" << point._x << " " << point._y << " " << point._z << ")";
		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, Point<scalar>&& point) {
		stream << "(" << point._x << " " << point._y << " " << point._z << ")";
		return stream;
	}


	static scalar norm(const Point<scalar>& first, const Point<scalar>& second)
	{
		return sqrt(pow(second.x() - first.x(), 2) + pow(second.y() - first.y(), 2) + pow(second.z() - first.z(), 2));
	}

protected:
	scalar _x;
	scalar _y;
	scalar _z;
};


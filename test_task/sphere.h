
#pragma once

#include <functional>
#include <cmath>

#include "point.h"




template <typename scalar, typename degree>
class Sphere
{
public:
	explicit Sphere(const Point<scalar, degree>& point = Point<scalar, degree>(), scalar radius = 0)
		: _center(point), _radius(radius)
	{}

	Sphere(const Sphere<scalar, degree>& ) = default;
	Sphere(Sphere<scalar, degree>&& ) = default;
	Sphere<scalar, degree>& operator=(const Sphere<scalar, degree>& ) = default;
	Sphere<scalar, degree>& operator=(Sphere<scalar, degree>&& ) = default;

	Point<scalar, degree>& center() { return std::ref(_center);}
	const Point<scalar, degree>& center() const { return _center;}
	scalar& radius() { return std::ref(_radius);}
	const scalar& radius() const { return _radius;}

	Point<scalar, degree>& get_relative_point(degree p, degree q, scalar height = 0) const 
	{
		auto& result = *new Point<scalar, degree>();
		result.p() = p;
		result.q() = q;
		result.r() = _radius + height;		
		return result;
	}

	Point<scalar, degree>& getPoint(degree p, degree q, scalar height = 0) const 
	{
		//auto& result = *new Point<scalar, degree>();
		auto& result = get_relative_point(p, q, height);
		//result.p() = p;
		//result.q() = q;
		//result.r() = _radius;		
		result = result + _center;
		return result;
	}

	scalar distance(const Point<scalar, degree>& first, const Point<scalar, degree>& second, scalar min_height = 0, bool like_hands_on_clock = true) const
	{
		auto relative_first = first - _center;
		auto relative_second = second - _center;
		if (relative_first.r() < _radius + min_height) {
			throw "first need get high";
		} else if (relative_second.r() < _radius + min_height) {
			throw "second need get high";
		}
		degree alpha = acos(1 - pow(Point<scalar, degree>::distance(first, second) / _radius, 2)/2);
		if ((like_hands_on_clock && relative_first.p() > relative_second.p()) || (!like_hands_on_clock && relative_first.p() < relative_second.p())) {
			alpha = atan(1)*8 - alpha;			// 2pi - alpha
		}
		scalar distance = alpha * (_radius + min_height);
		return distance;
	}


protected:
	Point<scalar, degree> _center;
	scalar _radius;
};

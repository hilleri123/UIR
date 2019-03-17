
#pragma once

#include <utility>
#include <cmath>
#include <iostream>

#include "point.h"
#include "sphere.h"


#define test 0

template<typename scalar, typename degree>
struct Intersection
{
	Point<scalar, degree> first;
	Point<scalar, degree> second;
	bool exists;
};

template <typename scalar, typename degree>
std::ostream& operator<<(std::ostream& stream, Intersection<scalar, degree> a)
{
	if (a.exists) {
		stream << "first is " << a.first << " second is " << a.second << std::endl;
	} else {
		stream << "no intersection" << std::endl;
	}
	return stream;
}



template <typename scalar, typename degree>
class Plane
{
public:
	explicit Plane(Sphere<scalar, degree> earth = Sphere<scalar, degree>(),
			scalar height = 0, 
			/*std::pair<degree, degree> direction = std::make_pair(0, 0)*/ degree direction = 0,
			std::pair<degree, degree> earth_position = std::make_pair(0, 0), 
			scalar speed = 1)
		: _earth(earth), _height(height), _direction(direction), _speed(speed)
	{
		_position = _earth.getPoint(std::get<0>(earth_position), std::get<1>(earth_position), _height);
		//scalar r = (_position - _earth.center()).z() * sin(_direction);
		_relative_position = _earth.get_relative_point(std::get<0>(earth_position), std::get<1>(earth_position), _height);
		scalar r = _relative_position.z() * sin(_direction);
		//degree alpha = atan(1)*2 - _direction;
		_center = Point<scalar, degree>();
		//_center.z() = r * cos(alpha);
		_center.z() = r * sin(_direction);
		degree alpha = atan(1)*2 + _relative_position.p();          //!!!!!!!!!!! +- pi/2
		_center.x() = r * cos(_direction) * sin(alpha);
		_center.y() = r * cos(_direction) * cos(alpha);
		_center = _center + _earth.center();
		_radius = Point<scalar, degree>::distance(_center, _position);
		_like_hands_on_clock = static_cast<int>((atan(1) * 6 + _direction) / (atan(1) * 4)) & 1;			//!!! 0.1 to int 0 ???     !!! if diameter || 0z ???(_direction = 0)
	}


	//std::pair<Point<scalar, degree>, Point<scalar, degree>> intersection(const Sphere<scalar, degree> sphere) const
	Intersection<scalar, degree>& intersection(const Sphere<scalar, degree> sphere) const
	{
		// sphere.center() = A
		// _center = B
		// relative_center = C
		// ED _|_ BC = O
		// EC = CD = relative_radius
		// BE = BD = _radius
		auto& result = *new Intersection<scalar, degree>();

		Point<scalar, degree> relative_center = sphere.center() - _center;

		scalar AB = Point<scalar, degree>::distance(sphere.center(), _center);
		//scalar AC = Point<scalar, degree>::distance(sphere.center(), _center) * sin(2*atan(1) - relative_center.q() - _direction);
		//scalar AC = AB * sin(std::abs(2*atan(1) - relative_center.q() - _direction));
		//scalar BC = AB * cos(std::abs(2*atan(1) - relative_center.q() - _direction));
		scalar AC = AB * sin(std::abs(_direction - relative_center.q()));
		scalar BC = AB * cos(std::abs(_direction - relative_center.q()));
		//scalar AC = AB * sin(2*atan(1) - relative_center.q() - _direction);

#if test
		{
			std::cout << "AB = " << AB << std::endl;
			std::cout << "AC = " << AC << std::endl;
			std::cout << "BC = " << BC << std::endl;
		}
#endif

		if (AC > sphere.radius()) {
			result.exists = false;
			return result;
		}
		scalar relative_radius = sqrt(pow(sphere.radius(), 2) - pow(AC, 2));
		
		//scalar range_between_centers = Point<scalar, degree>::distance(sphere.center(), _center) * cos(2*atan(1) - relative_center.q() - _direction);
		//relative_center.r() = Point<scalar, degree>::distance(sphere.center(), _center) * cos(2*atan(1) - relative_center.q() - _direction);
		//relative_center.r() = AB * cos(2*atan(1) - relative_center.q() - _direction);
		relative_center.r() = BC;
		//relative_center.q() = 2*atan(1) - _direction;
		relative_center.q() = _direction;

		//scalar BC = Point<scalar, degree>::distance(_center, _center + relative_center);

#if test
		{
			std::cout << "A = " << sphere.center() << std::endl;
			std::cout << "B = " << _center << std::endl;
			std::cout << "C = " << _center + relative_center << std::endl;
		}
#endif

		//degree alpha = atang(1)*2
		//relative_center.z() = sphere.center().z() + Point<scalar, degree>::distance(sphere.center(), _center) * tan(alpha);
		if (relative_center.r() > relative_radius + _radius || relative_radius > relative_center.r() + _radius || _radius > relative_center.r() + relative_radius) {
			if (relative_radius > relative_center.r() + _radius) {
				result.exists = true;					//!!! always in range
			} else {
				result.exists = false;
			}
			return result;
		}

		//scalar OB = std::abs(pow(_radius, 2) - pow(BC, 2) - pow(relative_radius, 2)) / 2 / BC;     
		scalar OB = -(pow(_radius, 2) - pow(BC, 2) - pow(relative_radius, 2)) / 2 / BC;     

#if test
		{
			std::cout << "OB = " << OB << std::endl;
		}
#endif

		if (OB < 0) {
			OB = BC - OB;
		}

		Point<scalar, degree> O;
		for (int i = 0; i < 3; i++) {
			O[i] = relative_center[i] * OB / BC;
		}

		Point<scalar, degree> E = O;
		E.p() = O.p() - acos(OB / _radius);
		E.r() = _radius;

		Point<scalar, degree> D = O;
		D.p() = O.p() + acos(OB / _radius);
		D.r() = _radius;

#if test
		{
			std::cout << "O = " << O << std::endl;
			std::cout << "E = " << E << std::endl;
			std::cout << "D = " << D << std::endl;
			std::cout << "ZERO = " << _center << std::endl;
		}
#endif

		if (_like_hands_on_clock) {
			if (E.p() < D.p()) {
				result.first = E + _center;
				result.second = D + _center;
			} else {
				result.first = D + _center;
				result.second = E + _center;
			}
		} else {
			if (E.p() < D.p()) {
				result.first = D + _center;
				result.second = E + _center;
			} else {
				result.first = E + _center;
				result.second = D + _center;
			}
		}
		result.exists = true;

#if test
		{
			std::cout << "D + ZERO = " << D + _center << std::endl;
			std::cout << "E + ZERO = " << E + _center << std::endl;
			std::cout << result << std::endl;
		}
#endif

#if test
		{
			std::cout << "R = " << _radius << std::endl;
			std::cout << "BE = ";
			std::cout << Point<scalar, degree>::distance(_center, _center + E) << std::endl;
			std::cout << "BD = ";
			std::cout << Point<scalar, degree>::distance(_center, _center + D) << std::endl;
			std::cout << "r = " << relative_radius << std::endl;
			std::cout << "CE = ";
			std::cout << Point<scalar, degree>::distance(relative_center, E) << std::endl;
			std::cout << "CD = ";
			std::cout << Point<scalar, degree>::distance(relative_center, D) << std::endl;
		}
#endif
		

		return result;
	}


	void time(std::vector<Sphere<scalar, degree>>& radars)
	{
		for (auto i=radars.begin(); i<radars.end(); i++) {
			Intersection<scalar, degree>& result = intersection(*i);
			//std::cout << result << std::endl;
			std::cout << result << "   sphere center = " << i->center() << " radius = " << i->radius() << std::endl;
			if (result.exists) {
				Sphere<scalar, degree> space(_center, _radius);
				scalar to_first = space.distance(_position, result.first, -0.0001, _like_hands_on_clock);
				scalar to_second = space.distance(_position, result.second, -0.0001, _like_hands_on_clock);
				if (to_first <= to_second) {
					std::cout << "now invisible " << " become visible is " << to_first / _speed << " get cloacked in " << to_second / _speed << std::endl;
				} else {
					std::cout << "now visible " << " get cloacked in " << to_second / _speed << " become visible in " << to_first / _speed << std::endl;
				}
			}
			std::cout << std::endl;
		}
	}


	friend std::ostream& operator<<(std::ostream& stream, Plane<scalar, degree> a)
	{
		stream << std::endl;
		stream << "earth center = " << a._earth.center() << ", relative positon = " << a._relative_position << ", direction = " << a._direction << std::endl;
		stream << "position = " << a._position << ", center and radius = " << a._center << " " << a._radius << std::endl;
		stream << std::endl;
		return stream;
	}
protected:
	
	Sphere<scalar, degree> _earth;
	scalar _height;
	//std::pair<degree, degree> _direction;
	degree _direction;
	Point<scalar, degree> _position;
	Point<scalar, degree> _relative_position;
	Point<scalar, degree> _center;
	scalar _speed;
	scalar _radius;
	bool _like_hands_on_clock;
};

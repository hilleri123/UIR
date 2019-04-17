
#include "rotate.h"


Rotate::Rotate(Point first, Point second, Velocity v, Vector direction)
	: _begin(first), _end(second), _velocity(v), _direction(direction)
{
	// A - start point
	// a - start vector
	// B - end point
	// b - end vector
	// O - center
	// R - radius
	//std::cout << "!" << std::endl;
	auto a = direction;
	Point B = second;
	auto AB = Vector(first, B);
	//std::cout << "a^AB = " << (a^AB) << std::endl;
	if (false) {
		_err = true;
	} else if (is_null(Vector::norm(a)) || is_null(a^AB)) {
		//std::cout << "do nothing" << std::endl;
		_end_point = first;
		_end_rotate = 0;
		//std::cout << "end point " << _end_point << " end rotate " << _end_rotate << std::endl;
	} else {
		//Point B(second.x(), second.y(), first.z());
		double R = v.v() / v.max_rotate();
		//std::cout << "R " << R << " first " << first.z() << " " << B.z() << std::endl;

		//auto AO = a.rotate_z(copysign(2*atan(1), a.xy_angle(AB))) * (R / Vector::norm(a));
		Point x = a + Point(0,0,0);
		//std::cout << "a : " << x << std::endl;
		auto AO = a.rotate(AB, 2*atan(1)) * (R / Vector::norm(a));
		_center = AO + first;
		//std::cout << "center " << _center << " first " << first << " R " << R << std::endl;
		auto OB = Vector(_center, B);
		//double beta = copysign(acos(R / Vector::norm(OB)), cos(a^OB));
		_clocks_hand = copysign(1, cos(a^OB));
		double beta = acos(R / Vector::norm(OB)) * _clocks_hand;
		//std::cout << "beta " << beta << std::endl;
		auto OC = OB.rotate(-1 * AO, beta);
		//std::cout << "!" << std::endl;
		auto C = (OC * (R / Vector::norm(OC))) + _center;
	
		_end_point = C;
		//_end_rotate = ((2 * (4 * atan(1))) / v.max_rotate()) * ( (2 * (4 * atan(1)) ) / ((-1 * AO)^OC));
		_end_rotate = ((-1 * AO)^OC) / v.max_rotate();
		//std::cout << "end point " << _end_point << " end rotate " << _end_rotate << std::endl;
	}
}

bool Rotate::init() const
{
	if (_err || _velocity == 0) {
		//std::cout << "rotate init" << std::endl;
		return false;
	} else {
		return true;
	}
}

Point Rotate::operator()(double time) const 
{
	if (time > max_time()) {
		return _end_point;
	} else if (time < 0) {
		return _begin;
	}
	auto r_vector = Vector(_center, _begin);
	r_vector = r_vector.rotate(Vector(_center, _end), time * _velocity.max_rotate() * _clocks_hand);
	return r_vector + _center;
}

double Rotate::max_time() const 
{
	return _end_rotate;
}

Point Rotate::end_point() const
{
	return _end_point;
}

Rotate::~Rotate()
{}


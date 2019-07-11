
#include "rotate.h"


Rotate::Rotate(Point first, Point second, Velocity v, Vector direction, Point* center)
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
	//assert(AB.check());
	if (false) {
		_err = true;
	} else if (is_null(Vector::norm(a)) || is_null(a^AB)) {
		_end_point = first;
		_end_rotate = 0;
	} else {
		double R = v.v() / v.max_rotate();

		Vector AO;
		if (center == nullptr) {
			AO = a.rotate(AB, 2*atan(1)) * (R / Vector::norm(a));
			_center = AO + first;
		} else {
			_center = *center;
			AO = Vector(first, _center);
		}
		auto OB = Vector(_center, B);
		_clocks_hand = copysign(1, cos(a^OB));

		Vector OC;
		if (Vector::norm(OB) >= R) {
			_k = 0;
			double beta = acos(R / Vector::norm(OB)) * _clocks_hand;
			if (equal(fabs(cos(OB^AO)), 1)) {
		     		OC = OB.rotate(a, beta);
			} else {
		     		OC = OB.rotate(-1 * AO, beta);
			}
			//assert(OC.check());
			//std::cout << "OC " << (OC+Point()) << " OB " << (OB+Point()) << " OA " << (-1*AO+Point()) << " beta " << beta << std::endl;
			auto C = (OC * (R / Vector::norm(OC))) + _center;
		
			_end_point = C;
			//_end_rotate = ((2 * (4 * atan(1))) / v.max_rotate()) * ( (2 * (4 * atan(1)) ) / ((-1 * AO)^OC));
		} else {
			OC = Vector(_center, second);
			_end_point = second;
		}
		if ((a^OC) >= atan(1)*2) {
			_end_rotate = (atan(1)*8 - ((AO * -1)^OC)) / v.max_rotate();
		} else {
			_end_rotate = ((AO * -1)^OC) / v.max_rotate();
		}	
		
		//std::cout << "(a^OC) " << (a^OC) << std::endl;
		//std::cout << "cos(OC^AO) " << (equal(fabs(cos(OC^AO)), 1)) << std::endl;
		if ((a^OC) >= atan(1)*2) {
			if (!equal(fabs(cos(OC^AO)), 1)) {
				_direction = OC.rotate(AO, -2*atan(1));
			} else {
				_direction = a * (-cos(OC^AO));
			}
		} else {
			if (!equal(fabs(cos(OC^AO)), 1)) {
				_direction = OC.rotate(AO, 2*atan(1));
			} else {
				_direction = a * (-cos(OC^AO));
			}
		}

		if (Vector::norm(OB) < R) {
			_k = (v.v() - Vector::norm(OC)*v.max_rotate()) / _end_rotate;
		}
		//std::cout << "end point " << _end_point << " end rotate " << _end_rotate << " r " << _end_point.radius() << " center " << _center << " k " << _k << std::endl;
		std::cout << "end point " << _end_point << " end rotate " << _end_rotate << " center " << _center << " k " << _k << std::endl;
		std::cout << "center r " << _center.radius() << std::endl;
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
	auto r_vector = Vector(_center, _begin) * (1 - (_k * time) / (_velocity.v()));
	//std::cout << (1 - (_k * time) / (_velocity.v())) << std::endl;
	//std::cout << "rotate " << (time * _velocity.max_rotate() * _clocks_hand) << std::endl;
	auto c_e = Vector(_center, _end);
	if (equal(fabs(cos(c_e^r_vector)), 1)) {
		//std::cout << "cos " << cos(r_vector^_direction) << std::endl;
		r_vector = r_vector.rotate(_direction, time * _velocity.max_rotate() * _clocks_hand);
	} else {
		//std::cout << "cos " << cos(r_vector^c_e) << " ~ " << cos(c_e^r_vector)  << " " << equal(cos(r_vector^c_e), 1)  << std::endl;
		r_vector = r_vector.rotate(c_e, time * _velocity.max_rotate() * _clocks_hand);
	}
	//std::cout << Vector::norm(r_vector) << std::endl;
	return r_vector + _center;
}

double Rotate::max_time() const 
{
	return _end_rotate;
}

Vector Rotate::direction() const 
{
	return _direction;
}

Point Rotate::end_point() const
{
	return _end_point;
}

Rotate::~Rotate()
{}



#pragma once

#include <cmath>

#include "point.h"
#include "vector.h"
#include "part_of_function.h"
#include "velocity.h"


template <typename scalar, class velocity, typename t>
class Rotate : PartOfFunction<scalar, velocity, t>
{
public:
	explicit Rotate(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>),
		       	velocity v = velocity(), const Vector<scalar>& direction = *std::unique_ptr<Vector<scalar>>(new Vector<scalar>))
		: PartOfFunction<scalar, velocity, t>(first, second, v, direction)
	{
		// A - start point
		// a - start vector
		// B - end point
		// b - end vector
		// O - center
		// R - radius
		auto& a = v.direction().projection(Vector<scalar>(Point<scalar>(0, 0, 1)));
		Point<scalar>& B = *new Point<scalar>(second.x(), second.y(), first.z());		//!!!
		auto& AB = Vector<scalar>(first, B);
		double alpha = a^Vector<scalar>(Point<scalar>(1, 0, 0));
		auto& x = AB.rotate_z(alpha);
		_sign = 1;
		if ((AB + Point<scalar>(0, 0, 0)).y() < 0) {
			_sign = -1;
		}

		_R = v.v() / v.max_rotate();

		auto& AO = a.rotate_z(atan(1)*2*_sign);
		_center = AO + first;
		auto& OB = Vector<scalar>(_center, B);
		double beta = acos(_R / Vector<scalar>::norm(OB));
		auto& OC = OB.rotate_z(beta*(-_sign));
		auto& C = (OB * (_R / Vector<scalar>::norm(OB))) + _center;
		
		auto gamma = AO^OC;
		if (a^Vector<scalar>(first, C) > atan(1)*2) {
			gamma += atan(1)*2;
		} else {
			gamma = atan(1)*2 - gamma;
		}
		_end_rotate = (1 / v.max_rotate()) * ( gamma / ( atan(1) * 8));
		
		_end_part = PartOfFunction<scalar, velocity, t>(C, second, v);

		delete &B;
	}

	virtual bool init() const override
	{
		if (err || PartOfFunction<scalar, velocity, t>::init()) {
			return false;
		} else {
			return true;
		}
	}

	virtual Point<scalar> operator()(t time) const override
	{
		if (time > max_time()) {
			return PartOfFunction<scalar, velocity, t>::_end;
		} else if (time < 0) {
			return PartOfFunction<scalar, velocity, t>::_begin;
		}
		if (time > _end_rotate) {
			return _end_part(time - _end_rotate);
		} else {
			auto r_vector = Vector<scalar>(_center, PartOfFunction<scalar, velocity, t>::_begin);
			r_vector = r_vector.rotate_z(time * PartOfFunction<scalar, velocity, t>::_velocity.max_rotate() * _sign);
			return r_vector + _center;
		}
	}

	virtual t max_time() const override
	{
		return 1;
	}

	virtual ~Rotate() override
	{}
protected:
private:
	bool err = false;
	int _sign;
	t _end_rotate;
	scalar _R;
	PartOfFunction<scalar, velocity, t> _end_part;
	Point<scalar> _center;
}; 


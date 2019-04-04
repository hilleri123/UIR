
#pragma once

#include <cmath>
#include <iostream>

#include "point.h"
#include "vector.h"
#include "velocity.h"
#include "init.h"


template <typename scalar, class velocity, typename t>
class Rotate : base_init
{
public:
	explicit Rotate(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>),
		       	velocity v = velocity(), const Vector<scalar>& direction = *std::unique_ptr<Vector<scalar>>(new Vector<scalar>(Point<scalar>(0,0,0), Point<scalar>(1,0,0))))
		: _begin(first), _end(second), _velocity(v), _direction(direction)
	{
		// A - start point
		// a - start vector
		// B - end point
		// b - end vector
		// O - center
		// R - radius
		auto a = direction;
		if (Vector<scalar>::norm(a) == 0) {
			_err = true;
		} else {
			Point<scalar> B = second;
			auto AB = Vector<scalar>(first, B);

			scalar R = v.v() / v.max_rotate();

			std::cout << "R " << R << " first " << first.z() << " " << B.z() << std::endl;
	
			auto AO = a.rotate_z(copysign(2*atan(1), a.xy_angle(AB))) * (R / Vector<scalar>::norm(a));
			_center = AO + first;

			std::cout << "center " << _center.x() << " " << _center.y() << " " << _center.z() << std::endl;

			auto OB = Vector<scalar>(_center, B);
			double beta = acos(R / Vector<scalar>::norm(OB));
			auto OC = OB.rotate_z(copysign(beta, AB.xy_angle(a)));
			auto C = (OC * (R / Vector<scalar>::norm(OC))) + _center;
		
			_end_point = C;
			_end_rotate = (1 / v.max_rotate()) * ( (AO^OC) / ( atan(1) * 8));

			std::cout << "end point " << C.x() << " " << C.y() << " " << C.z() << std::endl;
		}
	}

	Rotate(const Rotate<scalar, velocity, t>&) = default;
	Rotate(Rotate<scalar, velocity, t>&&) = default;
	Rotate<scalar, velocity, t>& operator=(const Rotate<scalar, velocity, t>&) = default;
	Rotate<scalar, velocity, t>& operator=(Rotate<scalar, velocity, t>&&) = default;

	virtual bool init() const override
	{
		if (_err || _begin == _end || _velocity == 0) {
			return false;
		} else {
			return true;
		}
	}

	virtual Point<scalar> operator()(t time) const 
	{
		if (time > max_time()) {
			return _end_point;
		} else if (time < 0) {
			return _begin;
		}
		auto r_vector = Vector<scalar>(_center, _begin);
		r_vector = r_vector.rotate_z(copysign(time * _velocity.max_rotate(), r_vector.xy_angle(Vector<scalar>(_center, _end_point))));
		return r_vector + _center;
	}

	virtual t max_time() const 
	{
		return _end_rotate;
	}

	virtual Point<scalar> end_point() const
	{
		return _end_point;
	}

	virtual ~Rotate() override
	{}
protected:
private:
	bool _err = false;
	t _end_rotate;
	Point<scalar> _begin;
	Point<scalar> _end;
	Point<scalar> _end_point;
	Point<scalar> _center;
	velocity _velocity;
	Vector<scalar> _direction;
}; 


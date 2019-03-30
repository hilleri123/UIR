
#pragma once

#include <cmath>

#include "init.h"
#include "vector.h"

//template <typename scalar, typename angle>
template <typename scalar>
class Velocity : base_init
{
public:
	explicit Velocity(scalar velocity = 1, Vector<scalar> direction, double max_rotate = asin(1/2))
		: _velocity(velocity), _direction(direction), _max_rotate(max_rotate)
	{}

	Velocity(Vector<scalar> direction, double max_rotate = asin(1/2))
		: _direction(direction), _max_rotate(max_rotate)
	{
		_velocity = Vector<scalar>::norm(direction);
	}
	
	Velocity(const Velocity<scalar>&) = default;
	Velocity(Velocity<scalar>&&) = default;
	Velocity<scalar>& operator=(const Velocity<scalar>&) = default;
	Velocity<scalar>& operator=(Velocity<scalar>&&) = default;
	
	Velocity<scalar>& operator=(const Vector<scalar>& vector) { _direction = vector; return *this; }
	Velocity<scalar>& operator=(Vector<scalar>&& vector) { _direction = vector; return *this; }
	Velocity<scalar>& operator=(scalar velocity) { _veloctiy = veloctiy; return *this; }

	virtual bool init() override
	{
		if (_velocity == 0 || _max_rotate == 0) {
			return false;
		} else {
			return true;
		}
	}

	double max_rotate() const { return _max_rotate; }
	const Vector<scalar>& direction() const { return _direction; }
	scalar v() const { return _velocity; }

	scalar operator+(scalar a) const { return v() + a; }
	inline friend scalar operator+(scalar a, const Velocity<scalar>& b) { return b + a; }
	scalar operator-(scalar a) const { return v() - a; }
	inline friend scalar operator-(scalar a, const Velocity<scalar>& b) { return b - a; }
	scalar operator*(scalar a) const { return v() * a; }
	inline friend scalar operator*(scalar a, const Velocity<scalar>& b) { return b * a; }
	scalar operator/(scalar a) const { return v() / a; }
	inline friend scalar operator/(scalar a, const Velocity<scalar>& b) { return b / a; }

	virtual ~Velocity() override
	{}
protected:
	scalar _velocity;
	//angle _max_rotate;
	double _max_rotate;
	Vector<scalar> _direction;
};

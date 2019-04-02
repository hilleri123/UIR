
#pragma once

#include <cmath>

#include "init.h"
#include "vector.h"

//template <typename scalar, typename angle>
template <typename scalar>
class Velocity : base_init
{
public:
	explicit Velocity(scalar velocity = 1, double max_rotate = asin(1./2.))
		: _velocity(velocity), _max_rotate(max_rotate)
	{}
	
	Velocity(const Velocity<scalar>&) = default;
	Velocity(Velocity<scalar>&&) = default;
	Velocity<scalar>& operator=(const Velocity<scalar>&) = default;
	Velocity<scalar>& operator=(Velocity<scalar>&&) = default;
	
	Velocity<scalar>& operator=(scalar velocity) { _velocity = velocity; return *this; }

	virtual bool init() const override
	{
		if (_velocity == 0 || _max_rotate == 0) {	//!!!
			return false;
		} else {
			return true;
		}
	}

	double max_rotate() const { return _max_rotate; }
	scalar v() const { return _velocity; }

	bool operator==(scalar a) const {return v() == a; }
	inline friend bool operator==(scalar a, const Velocity<scalar>& v) {return v.v() == a; }
	bool operator!=(scalar a) const {return v() != a; }
	inline friend bool operator!=(scalar a, const Velocity<scalar>& v) {return v.v() != a; }
	bool operator>=(scalar a) const {return v() >= a; }
	inline friend bool operator>=(scalar a, const Velocity<scalar>& v) {return v.v() >= a; }
	bool operator<=(scalar a) const {return v() <= a; }
	inline friend bool operator<=(scalar a, const Velocity<scalar>& v) {return v.v() <= a; }
	bool operator<(scalar a) const {return v() < a; }
	inline friend bool operator<(scalar a, const Velocity<scalar>& v) {return v.v() < a; }
	bool operator>(scalar a) const {return v() > a; }
	inline friend bool operator>(scalar a, const Velocity<scalar>& v) {return v.v() > a; }

	bool operator==(const Velocity<scalar>& a) const {return v() == a.v(); }
	inline friend bool operator==(const Velocity<scalar>& a, const Velocity<scalar>& v) {return v.v() == a.v(); }
	bool operator!=(const Velocity<scalar>& a) const {return v() != a.v(); }
	inline friend bool operator!=(const Velocity<scalar>& a, const Velocity<scalar>& v) {return v.v() != a.v(); }
	bool operator>=(const Velocity<scalar>& a) const {return v() >= a.v(); }
	inline friend bool operator>=(const Velocity<scalar>& a, const Velocity<scalar>& v) {return v.v() >= a.v(); }
	bool operator<=(const Velocity<scalar>& a) const {return v() <= a.v(); }
	inline friend bool operator<=(const Velocity<scalar>& a, const Velocity<scalar>& v) {return v.v() <= a.v(); }
	bool operator<(const Velocity<scalar>& a) const {return v() < a.v(); }
	inline friend bool operator<(const Velocity<scalar>& a, const Velocity<scalar>& v) {return v.v() < a.v(); }
	bool operator>(const Velocity<scalar>& a) const {return v() > a.v(); }
	inline friend bool operator>(const Velocity<scalar>& a, const Velocity<scalar>& v) {return v.v() > a.v(); }

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
	scalar _velocity = 1;
	//angle _max_rotate;
	double _max_rotate;
};

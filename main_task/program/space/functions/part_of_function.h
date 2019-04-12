
#pragma once

#include <memory>

#include <iostream>

#include "../geometrics/point.h"
#include "../geometrics/vector.h"
#include "../init.h"
#include "rotate.h"

template <typename scalar, class velocity, typename t>
class PartOfFunction : base_init
{
public:
	explicit PartOfFunction(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>),
		       	velocity v = velocity(), const Vector<scalar>& direction = *std::unique_ptr<Vector<scalar>>(new Vector<scalar>))
		//: _begin(first), _end(second), _velocity(v)
		: _begin(first), _end(second), _velocity(v), _direction(direction), _rotate(Rotate<scalar, velocity, t>(first, second, v, direction))
	{
		//if (v == 0) {
			//throw ;
		//}
		//std::cout << "first = " << first << " second = " << second << std::endl;
		//_direction_f = Vector<scalar>(first, second);
		//_rotate = Rotate<scalar, velocity, t>(first, second, v, direction);
		_direction_f = Vector<scalar>(_rotate.end_point(), second);
	}

	
	virtual bool init() const override
	{
		if (_begin == _end || _velocity == 0 || !_rotate.init()) {
			//std::cout << "pof init" << std::endl;
			return false;
		} else {
			return true;
		}
	}

	
	//template <typename t>
	virtual Point<scalar> operator()(t time) const
	{
		//if (time > max_time<t>()) {
		if (time > max_time()) {
			//throw ;
			return _end;
		} else if (time < 0) {
			//throw ;
			return _begin;
		}
		if (time < _rotate.max_time()) {
			return _rotate(time);
		}
		scalar part = static_cast<scalar>(time) * (_velocity / Point<scalar>::norm(_rotate.end_point(), _end));
		auto&& vector = _direction_f * part;
		//return Point<scalar>(vector + _rotate.end_point());
		return vector + _rotate.end_point();
	}

	//template <typename t>
	virtual t max_time() const
	{
		//auto a = _rotate.end_point();
		//std::cout << "!" << (Point<scalar>::norm(a, _end) / _velocity) << std::endl;
		//std::cout << "max time " << static_cast<t>(Point<scalar>::norm(a, _end) / _velocity) << " between " << a.x() << " " << a.y() << " " << a.z() << " and " << _end.x() << " " << _end.y() << " " << _end.z() << std::endl;
		return static_cast<t>(Point<scalar>::norm(_rotate.end_point(), _end) / _velocity) + _rotate.max_time();
	}

	virtual Vector<scalar> direction() const
	{
		return _direction_f;
	}

	virtual ~PartOfFunction() override
	{}

protected:
	Point<scalar> _begin;
	Point<scalar> _end;
	velocity _velocity;
	Vector<scalar> _direction;

private:
	Vector<scalar> _direction_f;
	Rotate<scalar, velocity, t> _rotate;
};

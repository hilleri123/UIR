
#pragma once

#include <memory>

#include <iostream>

#include "point.h"
#include "vector.h"
#include "init.h"

template <typename scalar, class velocity, typename t>
class PartOfFunction : base_init
{
public:
	explicit PartOfFunction(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>),
		       	velocity v = velocity(), const Vector<scalar>& direction = *std::unique_ptr<Vector<scalar>>(new Vector<scalar>))
		//: _begin(first), _end(second), _velocity(v)
		: _velocity(v), _direction(direction)
	{
		//if (v == 0) {
			//throw ;
		//}
		_begin = first;
		_end = second;
		//std::cout << "first = " << first << " second = " << second << std::endl;
		_direction_f = Vector<scalar>(first, second);
	}

	
	virtual bool init() const override
	{
		if (_begin == _end || _velocity == 0) {
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
		scalar part = static_cast<scalar>(time) * (_velocity / Point<scalar>::norm(_begin, _end));
		auto&& vector = _direction_f * part;
		auto result = Point<scalar>(vector + _begin);
		return result;
	}

	//template <typename t>
	virtual t max_time() const
	{
		return static_cast<t>(Point<scalar>::norm(_begin, _end) / _velocity);
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
};


#pragma once

#include <memory>

#include <iostream>

#include "point.h"
#include "vector.h"

template <typename scalar, typename t>
class PartOfFunction
{
public:
	explicit PartOfFunction(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>), scalar v = 1)
		//: _begin(first), _end(second), _velocity(v)
		: _velocity(v)
	{
		if (v == 0) {
			//throw ;
		}
		_begin = first;
		_end = second;
		//std::cout << "first = " << first << " second = " << second << std::endl;
		_direction_f = Vector<scalar>(_begin, _end);
	}
	
	//template <typename t>
	virtual Point<scalar>& operator()(t time) const
	{
#if 0
		if (_direction_f == nullptr) {
			_direction_f = new Vector<scalar>(_begin, _end);
		}
#endif
		//if (time > max_time<t>()) {
		if (time > max_time()) {
			//throw ;
			return _end;
		} else if (time < 0) {
			//throw ;
			return _begin;
		}
		//std::cout << "result" << std::endl;
		scalar part = static_cast<scalar>(time) * (_velocity / Point<scalar>::norm(_begin, _end));
		//auto& result = *new Point<scalar>(_direction_f->operator*(static_cast<scalar>(time) * (_velocity / Point<scalar>::norm(_begin, _end))) + _begin);
		//std::cout << "part = " << part << std::endl;
		//std::cout << "vector at " << _direction_f << std::endl;
		//auto&& vector = _direction_f->operator*(part);
		auto&& vector = _direction_f * part;
		//auto& result = *new Point<scalar>(_direction_f->operator*(part) + _begin);
		//std::cout << "vector" << std::endl;
		auto& result = *new Point<scalar>(vector + _begin);
		//std::cout << "returning" << std::endl;
		return result;
	}

	//template <typename t>
	virtual t max_time() const
	{
		return static_cast<t>(Point<scalar>::norm(_begin, _end) / _velocity);
	}


protected:
	Point<scalar>& _begin = *new Point<scalar>();
	Point<scalar>& _end = *new Point<scalar>();
	scalar _velocity;

private:
	Vector<scalar>& _direction_f = *new Vector<scalar>();
};

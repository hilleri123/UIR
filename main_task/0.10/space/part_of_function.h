
#pragma once

#include <memory>

#include "point.h"
#include "vector.h"

template <typename scalar>
class PartOfFunction
{
public:
	explicit PartOfFunction(Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>), Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>), scalar v = 1)
		: _begin(first), _end(second), _velocity(v)
	{
		if (v == 0) {
			throw ;
		}
	}
	
	template <typename t>
	Point<scalar>& operator()(t time) const
	{
		if (_direction == nullptr) {
			_direction = new Vector<scalar>(_begin, _end);
		}
		if (time > max_time<t>()) {
			//throw ;
			return _end;
		} else if (time < 0) {
			//throw ;
			return _begin;
		}
		return _direction->operator*(static_cast<scalar>(time) * (_velocity / Point<scalar>::norm(_begin, _end))) + _begin;
	}

	template <typename t>
	t max_time() const
	{
		return static_cast<t>(Point<scalar>::norm(_begin, _end) / _velocity);
	}

	~PartOfFunction()
	{
		if (_direction != nullptr) {
			delete _direction;
		}
	}

protected:
	Point<scalar>& _begin = *new Point<scalar>();
	Point<scalar>& _end = *new Point<scalar>();
	scalar _velocity;

private:
	Vector<scalar>* _direction = nullptr;
};

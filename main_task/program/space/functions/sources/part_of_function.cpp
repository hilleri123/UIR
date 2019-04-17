
#include "part_of_function.h"

PartOfFunction::PartOfFunction(const Point& first, const Point& second, Velocity v, const Vector& direction)
	: _begin(first), _end(second), _velocity(v), _direction(direction), _rotate(Rotate(first, second, v, direction))
{
	//if (v == 0) {
		//throw ;
	//}
	//std::cout << "first = " << first << " second = " << second << std::endl;
	//_direction_f = Vector(first, second);
	//_rotate = Rotate<double, double, t>(first, second, v, direction);
	_direction_f = Vector(_rotate.end_point(), second);
}

	
bool PartOfFunction::init() const
{
	if (_begin == _end || _velocity == 0 || !_rotate.init()) {
		//std::cout << "pof init" << std::endl;
		return false;
	} else {
		return true;
	}
}

Point PartOfFunction::operator()(double time) const
{
	if (time > max_time()) {
		return _end;
	} else if (time < 0) {
		return _begin;
	}
	if (time < _rotate.max_time()) {
		return _rotate(time);
	}
	double part = time * (_velocity / Point::norm(_rotate.end_point(), _end));
	auto&& vector = _direction_f * part;
	return vector + _rotate.end_point();
}

double PartOfFunction::max_time() const
{
	//auto a = _rotate.end_point();
	//std::cout << "!" << (Point::norm(a, _end) / _double) << std::endl;
	//std::cout << "max time " << static_cast<t>(Point::norm(a, _end) / _double) << " between " << a.x() << " " << a.y() << " " << a.z() << " and " << _end.x() << " " << _end.y() << " " << _end.z() << std::endl;
	return (Point::norm(_rotate.end_point(), _end) / _velocity) + _rotate.max_time();
}

Vector PartOfFunction::direction() const
{
	return _direction_f;
}

PartOfFunction::~PartOfFunction()
{}


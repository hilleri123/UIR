
#include "part_of_function.h"

PartOfFunction::PartOfFunction(const Point& first, const Point& second, const Point& c, const Velocity& v)
	: _first(c, first), _second(c, second), _center(c), _velocity(v)
{
	std::cout << "first :" << (_first + Point(0,0,0)) << " second :" << (_second + Point(0,0,0)) << " center :" << _center << std::endl;
	std::cout << "r_first :" << Vector::norm(_first) << " r_second :" << Vector::norm(_second) << std::endl;
}

	
bool PartOfFunction::init() const
{
	//if (_begin == _end || _velocity == 0 || !_rotate.init()) {
	if (_velocity == 0) {
		//std::cout << "pof init" << std::endl;
		return false;
	} else {
		return true;
	}
}

Point PartOfFunction::operator()(double time) const
{
	if (time > max_time()) {
		return _second+_center;
	} else if (time < 0) {
		return _first+_center;
	}
	//std::cout << (max_time()/(_second^_first)) << std::endl;
	auto&& vector = _first.rotate(_second, time/max_time()*(_second^_first));
	return vector + _center;
}

double PartOfFunction::max_time() const
{
	return (Vector::norm(_first) * (_first^_second)) / _velocity;
}

PartOfFunction::~PartOfFunction()
{}


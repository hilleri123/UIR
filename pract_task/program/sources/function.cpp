
#include "function.h"

Interval::Interval(double begin, PartOfFunction f)
	: _begin(begin), _f(f)
{}

Point Interval::operator()(double time) const
{
	return _f(time-_begin);
}

bool Interval::in(double time) const 
{
	return time <= (_begin + _f.max_time()) && time >= _begin;
}

double Interval::begin() const 
{
	return _begin;
}

double Interval::end() const
{
	return _begin + _f.max_time();
}	



Function::Function(const std::vector<std::pair<Point, Velocity>>& points)
{
	auto& trajectory = *combine(points);
	double time_b = 0;
	double time_e = 0;
	for (auto i = trajectory.begin(); i < trajectory.end(); i++) {
		double max_time = i->max_time();
		time_e += max_time;
		_function.emplace_back(Interval(time_b, *i));
		time_b += max_time;
	}
	delete &trajectory;
}
	
Point Function::operator()(double time) const
{
	for (auto i = _function.begin(); i < _function.end(); i++) {
		if (i->in(time)) {
			return (*i)(time);
		}
	}
	return (_function.back())(time);
}

Interval Function::interval(std::size_t i) const
{
	if (i < _function.size()) {
		return _function.at(i);
	} else {
		return _function.back();
	}
}

std::size_t Function::find_interval(double t) const
{
	for (auto i = _function.begin(); i < _function.end(); i++) {
		if (i->in(t)) {
			return i - _function.begin();
		}
	}
	return _function.size() - 1;
}

double Function::max_time() const
{
	return _function.back().end();
}


Function::~Function()
{}


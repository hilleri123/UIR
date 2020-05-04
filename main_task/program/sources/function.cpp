
#include "function.h"

Interval::Interval(double begin, double end)
	: _begin(begin), _end(end)
{}

bool Interval::in_interval(double time, const Interval interval)
{
	return time <= interval._end && time >= interval._begin;
}

bool Interval::in(double time) const 
{
	return time <= _end && time >= _begin;
}

double Interval::begin() const 
{
	return _begin;
}

double Interval::end() const
{
	return _end;
}	



Function::Function(const std::vector<std::pair<Point, Velocity>>& points)
{
	//std::cout << "constructor" << std::endl;
	if (points.size() < 2)
		return;
	auto& trajectory = *combine(points);
	//std::cout << "trajectory size = " << trajectory.size() << std::endl;
	double time_b = 0;
	double time_e = 0;
	for (auto i = trajectory.begin(); i < trajectory.end(); i++) {
		//std::cout << "!" << std::endl;
		double max_time = i->max_time();
		time_e += max_time;
		//_function.push_back( std::make_pair<PartOfFunction<double, t>&, Interval<t>&>(*i, std::ref(Interval<t>(time_b, time_e))) );
		//_function.push_back( std::make_pair<PartOfFunction<double, t>&, Interval<t>&>(std::ref(*i), std::ref(interval)) );
		//auto pair = std::make_pair(*i, interval);
		//std::cout << "push_back" << std::endl;
		//_function.push_back(std::make_pair(*i, interval));
		//_function.emplace_back(pair);
		//std::cout << "begin " << time_b << " end " << time_e << std::endl;
		_function.emplace_back(*i, Interval(time_b, time_e));
		//std::cout << "pushed_back" << std::endl;
		time_b += max_time;
	}
	delete &trajectory;
}
	
std::pair<Point, Velocity> Function::operator()(double time) const
{
	for (auto i = _function.begin(); i < _function.end(); i++) {
		//std::cout << "check" << std::endl;
		if (Interval::in_interval(time, std::get<1>(*i))) {
			//std::cout << "in interval " << std::get<1>(*i).begin() << std::endl;
			const PartOfFunction& part = std::get<0>(*i);
			//return std::get<0>(*i)(time - std::get<1>(*i).begin());
			return std::make_pair(part(time - std::get<1>(*i).begin()), part.stats());
		}
	}
	const PartOfFunction& part = std::get<0>(_function.back());
	return std::make_pair(part(time), part.stats());
	//return std::get<0>(_function.back())(time);
}

Interval Function::interval(std::size_t i) const
{
	if (i < _function.size()) {
		return std::get<1>(_function.at(i));
	} else {
		return std::get<1>(_function.back());
	}
}

std::size_t Function::find_interval(double t) const
{
	for (auto i = _function.begin(); i < _function.end(); i++) {
		if (std::get<1>(*i).in(t)) {
			return i - _function.begin();
		}
	}
	return _function.size() - 1;
}

double Function::max_time() const
{
	return std::get<1>(_function.back()).end();
}

Function::~Function()
{}


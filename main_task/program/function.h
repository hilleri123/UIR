
#pragma once

#include <vector>
#include <utility>

#include <iostream>

#include "space/combinator.h"
#include "space/part_of_function.h"
#include "space/point.h"



template <typename t>
class Interval
{
public:
	explicit Interval(t begin, t end)
		: _begin(begin), _end(end)
	{}
	static bool in_interval(t time, const Interval<t> interval)
	{
		if (time <= interval._end && time >= interval._begin) { return true; } else { return false; }
	}
	t begin() const { return _begin; }	
	t end() const { return _end; }	
protected:
	t _begin;
	t _end;
};




template <typename scalar, class velocity, typename t>
class Function
{
public:
	explicit Function(const std::vector<std::pair<Point<scalar>, velocity>>& points)
	{
		std::cout << "constructor" << std::endl;
		auto& trajectory = combine<scalar, velocity, t>(points);
		std::cout << "trajectory size = " << trajectory.size() << std::endl;
		t time_b = 0;
		t time_e = 0;
		for (auto i = trajectory.begin(); i < trajectory.end(); i++) {
			t max_time = i->max_time();
			time_e += max_time;
#if 0
			_function.push_back( std::make_pair<PartOfFunction<scalar, t>, std::pair<t, t>>(*i, std::make_pair<t, t>(time_b, time_e)) );
#endif
			//auto& interval = *new Interval<t>(time_b, time_e);
			//_function.push_back( std::make_pair<PartOfFunction<scalar, t>&, Interval<t>&>(*i, std::ref(Interval<t>(time_b, time_e))) );
			//_function.push_back( std::make_pair<PartOfFunction<scalar, t>&, Interval<t>&>(std::ref(*i), std::ref(interval)) );
			//auto pair = std::make_pair(*i, interval);
			//std::cout << "push_back" << std::endl;
			//_function.push_back(std::make_pair(*i, interval));
			//_function.emplace_back(pair);
			_function.emplace_back(*i, Interval<t>(time_b, time_e));
			//std::cout << "pushed_back" << std::endl;
			time_b += max_time;
		}
		delete &trajectory;
	}
	
	Point<scalar> operator()(t time) const
	{
		for (auto i = _function.begin(); i < _function.end(); i++) {
#if 0
			if (in_interval(time, std::get<1>(*i))) {
				return std::get<0>(*i)(time - std::get<0>(std::get<1>(*i)))
			}
#endif
			//std::cout << "check" << std::endl;
			if (Interval<t>::in_interval(time, std::get<1>(*i))) {
				//std::cout << "in interval " << std::get<1>(*i).begin() << std::endl;
				return std::get<0>(*i)(time - std::get<1>(*i).begin());
			}
		}
		return std::get<0>(_function.back())(time);
	}

	~Function()
	{
		delete &_function;
	}

protected:
#if 0
	static bool in_interval(t time, std::pair<t, t> interval)
	{
		if (time <= std::get<1>(interval) && time >= std::get<0>(interval)) { return true; } else { return false; }
	}

	auto& _function = *new std::vector<std::pair<PartOfFunction<scalar, t>, std::pair<t, t>>>();
#endif

	std::vector<std::pair<PartOfFunction<scalar, velocity, t>, Interval<t>>>& _function = *new std::vector<std::pair<PartOfFunction<scalar, velocity, t>, Interval<t>>>();
};

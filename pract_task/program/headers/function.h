
#pragma once

#include <vector>
#include <utility>

#include <iostream>

#include "combinator.h"
#include "part_of_function.h"
#include "point.h"
#include "velocity.h"



class Interval
{
public:
	explicit Interval(double begin, PartOfFunction f);
	bool in(double time) const;
	Point operator()(double time) const;
	double begin() const;
	double end() const;
protected:
	double _begin;
	PartOfFunction _f;
};




class Function
{
public:
	explicit Function(const std::vector<std::pair<Point, Velocity>>& points);
	
	Point operator()(double time) const;

	Interval interval(std::size_t) const;

	std::size_t find_interval(double) const;

	double max_time() const;

	~Function();

protected:

	std::vector<Interval> _function;
};

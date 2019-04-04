
#pragma once

#include <vector>
#include <utility>

#include <iostream>

#include "part_of_function.h"
#include "velocity.h"


template <typename scalar, class velocity, typename t>
std::vector<PartOfFunction<scalar, velocity, t>>& combine(const std::vector<std::pair<Point<scalar>, velocity>>& points)
//std::vector<Rotate<scalar, Velocity<velocity>, t>>& combine(const std::vector<std::pair<Point<scalar>, velocity>>& points)
{
	using PF = PartOfFunction<scalar, velocity, t>;
	//using RF = Rotate<scalar, velocity, t>;
	auto& result = *new std::vector<PF>();
	PF* part;
	//Vector<scalar> vector(Point<scalar>(), std::get<0>(*points.begin()));
	auto direction = Vector<scalar>(Point<scalar>(0,0,0), std::get<0>(*points.begin()));
	for (auto i = points.begin(); i+1 < points.end(); i++) {
		INIT (part, PF, std::get<0>(*i), std::get<0>(*(i+1)), std::get<1>(*i), direction);
		//INIT (part, PF, std::get<0>(*i), std::get<0>(*(i+1)), Velocity<scalar>(std::get<1>(*i), vector));
		direction = part->direction();
		result.push_back(*part);
		delete part;
	}
	return result;
}

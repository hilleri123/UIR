
#pragma once

#include <vector>
#include <utility>

#include <iostream>

#include "part_of_function.h"


template <typename scalar, class velocity, typename t>
std::vector<PartOfFunction<scalar, velocity, t>>& combine(const std::vector<std::pair<Point<scalar>, velocity>>& points)
{
	using PF = PartOfFunction<scalar, velocity, t>;
	auto& result = *new std::vector<PF>();
	PF* part;
	for (auto i = points.begin(); i+1 < points.end(); i++) {
		INIT (part, PF, std::get<0>(*i), std::get<0>(*(i+1)) );
		result.push_back(*part);
	}
	return result;
}

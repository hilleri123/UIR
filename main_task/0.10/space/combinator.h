
#pragma once

#include <vector>
#include <utility>

#include <iostream>

#include "part_of_function.h"


template <typename scalar, class velocity, typename t>
std::vector<PartOfFunction<scalar, t>>& combine(const std::vector<std::pair<Point<scalar>, velocity>>& points)
{
	auto& result = *new std::vector<PartOfFunction<scalar, t>>();
	for (auto i = points.begin(); i+1 < points.end(); i++) {
		//std::cout << "get<0> = " << std::get<0>(*i) << " get<1> = " << std::get<0>(*(i+1)) << std::endl;
		result.emplace_back(std::get<0>(*i), std::get<0>(*(i+1)));
	}
	return result;
}

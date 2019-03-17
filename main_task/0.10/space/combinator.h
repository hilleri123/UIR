
#pragma once

#include <vector>
#include <utility>

#include "part_of_function.h"


template <typename scalar, class velocity>
std::vector<PartOfFunction<scalar>>& combine(const std::vector<std::pair<Point<scalar>, velocity>>& points)
{
	auto& result = *new std::vector<PartOfFunction<scalar>>();
	for (auto i = points.begin(); i < points.end(); i++) {
		result.emplace_back(std::get<0>(*i), std::get<1>(*i));
	}
	return result;
}

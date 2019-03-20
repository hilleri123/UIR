
#pragma once

#include <vector>
#include <utility>

#include <iostream>

#include "part_of_function.h"


template <typename scalar, class velocity, typename t>
std::vector<PartOfFunction<scalar, t>>& combine(const std::vector<std::pair<Point<scalar>, velocity>>& points)
{
	using PF = PartOfFunction<scalar, t>;
	//auto& result = *new std::vector<PartOfFunction<scalar, t>>();
	auto& result = *new std::vector<PF>();
	for (auto i = points.begin(); i+1 < points.end(); i++) {
		//std::cout << "get<0> = " << std::get<0>(*i) << " get<1> = " << std::get<0>(*(i+1)) << std::endl;
		//result.emplace_back(std::get<0>(*i), std::get<0>(*(i+1)));
		INIT(part, (PartOfFunction<scalar, t>), std::get<0>(*i), std::get<0>(*(i+1)) )
		// INIT (part, PF, std::get<0>(*i), std::get<0>(*(i+1)) )
		result.push_back(*part);
	}
	return result;
}

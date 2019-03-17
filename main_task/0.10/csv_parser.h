
#pragma once

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <functional>

#include <iostream>

#include "space/point.h"


template <typename scalar, class velocity>
std::vector<std::pair<Point<scalar>, velocity>>& csv_parser_read(const char* file)
{
	auto& result = *new std::vector<std::pair<Point<scalar>, velocity>>();
	std::cout << "init" << std::endl;
	
	std::ifstream stream(file);
	if (!stream.is_open()) {
		std::cout << "not open" << std::endl;
		throw ;
	}
	std::string buf;
	
	while (std::getline(stream, buf)) {
		std::vector<std::string> parts;
		auto begin = buf.begin();
		auto end = buf.begin();
		for (end; end < buf.end(); end++) {
			//std::cout << *end << std::endl;
			if (*end == ',') {			// csv
				std::string tmp(begin, end);
				//parts.emplace_back(begin, end);
				parts.emplace_back(tmp);
				//std::cout << '"' << tmp << '"' << std::endl;
				//std::cout << "emplace_back" << std::endl;
				begin = end + 1;
			}
		}
		{
			std::string tmp(begin, end);
			parts.emplace_back(tmp);
		}
		//
		
		//std::cout << "size = " << parts.size() << std::endl;
		if (parts.size() == 4) {
			double x = std::stod(parts[0]);
			double y = std::stod(parts[1]);
			double z = std::stod(parts[2]);
			double s = std::stod(parts[3]);

			auto pair = std::make_pair(*new Point<scalar>(x, y, z), s);

			//std::cout << std::get<0>(pair) << std::endl;

			result.push_back(pair);
		} else {
			// bad data
			std::cout << "bad data" << std::endl;
			throw ;
		}

		//
	}
	stream.close();

	return result;
}

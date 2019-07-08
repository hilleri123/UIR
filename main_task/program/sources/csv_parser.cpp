
#include "csv_parser.h"


std::vector<std::pair<Point, Velocity>>& csv_parser_read(const char* file)
{
	
	std::ifstream stream;
	//stream.exceptions(std::ios_base::failbit | std::ios_base::eofbit);
	//stream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	stream.open(file);
	if (!stream.is_open()) {
		//std::cout << "not open" << std::endl;
		throw std::ifstream::failure("not open");
	}
	auto& result = *new std::vector<std::pair<Point, Velocity>>();
	std::string buf;
	
	double angle = asin(1./2.);

	while (std::getline(stream, buf) ) {
	//while (!stream.eof()) {
		//std::getline(stream, buf);
		
		buf.erase(std::remove_if(buf.begin(), buf.end(), [](char c){ return std::isspace(c); }), buf.end());

		std::vector<std::string> parts;
		auto begin = buf.begin();
		auto end = buf.begin();
		for (; end < buf.end(); end++) {
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

		if (begin != end) {
			std::string tmp(begin, end);
			parts.emplace_back(tmp);

		}

		//std::cout << "size : " << parts.size() << std::endl;
		//for (auto i = parts.begin(); i < parts.end(); i++) {
			//std::cout << "'" << *i << "'" << std::endl;
		//}
		//
		
		//std::cout << "size = " << parts.size() << std::endl;
		if (parts.size() == 4 || parts.size() == 5) {
			if (parts.size() == 5) {
				angle = std::stod(parts[4]) / 45 * atan(1);
				//std::cout << angle << std::endl;
			}
			//double x = std::stod(parts[0]);
			//double y = std::stod(parts[1]);
			//double z = std::stod(parts[2]);

			double r = std::stod(parts[0]);
			double latitude = std::stod(parts[1]) / 45 * atan(1);
			double longitude = std::stod(parts[2]) / 45 * atan(1);

			double s = std::stod(parts[3]);

			
			Velocity* v = nullptr;
			INIT (v, Velocity, s, angle);
			if (v != nullptr) {
				//auto pair = std::make_pair(Point(x, y, z), *v);

				Point tmp;
				auto pair = std::make_pair(tmp.by_geo(r, latitude, longitude), *v);
				//std::cout << std::get<0>(pair) << std::endl;
				result.push_back(pair);
				delete v;
			} else {
				// bad data
				std::cout << "velocity cannt exists" << std::endl;
				delete &result;
				throw ;			//!!!
			}

		} else if (parts.size() != 0) {
			// bad data
			std::cout << "bad data" << std::endl;
			delete &result;
			throw ;			//!!!
		}

		//
	}
	stream.close();

	return result;
}

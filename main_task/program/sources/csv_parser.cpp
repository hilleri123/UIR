
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
	
	while (std::getline(stream, buf) ) {
	//while (!stream.eof()) {
		//std::getline(stream, buf);
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

			
			Velocity* v = nullptr;
			INIT (v, Velocity, s);
			if (v != nullptr) {
				auto pair = std::make_pair(Point(x, y, z), *v);
				//std::cout << std::get<0>(pair) << std::endl;
				result.push_back(pair);
				delete v;
			} else {
				// bad data
				std::cout << "bad data" << std::endl;
				delete &result;
				throw ;			//!!!
			}

		} else {
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

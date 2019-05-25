
#include "combinator.h"


std::vector<PartOfFunction>* combine(const std::vector<std::pair<Point, Velocity>>& points)
{
	using PF = PartOfFunction;
	auto& result = *new std::vector<PF>();
	PF* part;
	auto direction = Vector(std::get<0>(*points.begin()), std::get<0>(*(points.begin()+1)));
	for (auto i = points.begin(); i+1 < points.end(); i++) {
		INIT (part, PF, std::get<0>(*i), std::get<0>(*(i+1)), std::get<1>(*i), direction);
		//INIT (part, PF, std::get<0>(*i), std::get<0>(*(i+1)), Velocity(std::get<1>(*i), vector));
		if (part == nullptr) {
			std::cout << "no part here " << (i - points.begin()) << std::endl;
		}
		direction = part->direction();
		result.push_back(*part);
		delete part;
		//std::cout << "+part" << std::endl;
	}
	return &result;
}
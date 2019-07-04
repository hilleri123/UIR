
#include "combinator.h"


std::vector<PartOfFunction>* combine(const std::vector<std::pair<Point, Velocity>>& points)
{
	using PF = PartOfFunction;
	auto& result = *new std::vector<PF>();
	PF* part;
	Sphere a(Point(), std::get<0>(*points.begin()), 0);
	std::cout << a << "const delta :" << Point::norm(std::get<0>(*points.begin()), a.plane()) << std::endl;
	std::cout << "plane :" << a.plane() << " point :" << std::get<0>(*points.begin()) << std::endl; 
	//auto direction = Vector(std::get<0>(*points.begin()), std::get<0>(*(points.begin()+1)));
	for (auto i = points.begin(); i+1 < points.end(); i++) {
		std::cout << "pre delta :" << Point::norm(a.plane(), std::get<0>(*i)) << std::endl;
		a = a.new_sphere(std::get<0>(*(i+1)));
		//std::cout << a << std::endl;
		std::cout << "delta :" << Point::norm(a.plane(), std::get<0>(*i)) << std::endl;
		//std::cout << "norm :" << Point::norm(a.plane(), a.center()) << " " << Point::norm(a.center(), std::get<0>(*(i+1))) << std::endl;
		std::cout << "norm :" << Point::norm(std::get<0>(*i), a.center()) << " " << Point::norm(a.center(), std::get<0>(*(i+1))) << std::endl;
		INIT (part, PF, std::get<0>(*i), std::get<0>(*(i+1)), a.center(), std::get<1>(*i));
		if (part == nullptr) {
			std::cout << "no part here " << (i - points.begin()) << std::endl;
		}
		std::cout << "--------------------" << std::endl;
		//direction = part->direction();
		result.push_back(*part);
		a = Sphere(a.center(), std::get<0>(*(i+1)), 0);
		//std::cout << a << std::endl;
		std::cout << a << "const delta :" << Point::norm(std::get<0>(*points.begin()), a.plane()) << std::endl;
		std::cout << "plane :" << a.plane() << " point :" << std::get<0>(*(i+1)) << std::endl; 
		delete part;
	}
	return &result;
}

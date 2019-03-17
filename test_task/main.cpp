#include <vector>
#include <utility>
#include <iostream>
#include <cstdio>

#include "point.h"
#include "sphere.h"
#include "plane.h"

using MyPoint = Point<double, double>;
using Radar = Sphere<double, double>;
using MyPlane = Plane<double, double>;

std::vector<Radar>& parser(char* file, Radar& earth)
{
	FILE *xml_file = fopen(file, "r");
	if (xml_file == nullptr) {
		std::cout << "no file" << std::endl;
		//throw "no file";
	}

	auto& result = *new std::vector<Radar>;
	result.emplace_back(earth.getPoint(0.4, 0), 2);
	result.emplace_back(earth.getPoint(0.6, 1.5), 1);
	result.emplace_back(earth.getPoint(0.4, 2), 2.5);
	result.emplace_back(earth.getPoint(0.6, 2.1), 1.1);
	result.emplace_back(earth.getPoint(2.4, 4), 4.8);
	result.emplace_back(earth.getPoint(5.4, 1), 3.8);
	result.emplace_back(earth.getPoint(1.4, 2), 8);
	result.emplace_back(earth.getPoint(0.1, 0.1), 4);
	result.emplace_back(earth.getPoint(0, 0), 4);

	return result;
}

int main(int argc, char** argv)
{
	try {
		std::vector<Radar> radars;
		MyPoint aaa(0, 0, 0);
		Radar earth(aaa, 10);
		if (argc == 2) {
			radars = parser(argv[1], earth);
		}
		MyPoint a(1, 1, 1);
		MyPoint b(2, 2, 2);
		if ((a+b)!=MyPoint(3, 3, 3)) {
			throw;
		}
		std::cout << a << b << MyPoint::distance(a, b) << std::endl;
	
		std::cout << earth.getPoint(0.1, 0.1) << earth.getPoint(0.5, 0.1) << std::endl;
		std::cout << earth.distance(earth.getPoint(0.1, 0.1), earth.getPoint(0.5, 0.1), 0, false) << std::endl;
		Radar LR(earth.getPoint(0, 0.2), 3);
		MyPlane aerobus(earth, 2, 0.1, std::make_pair(0.1, 0.1));
		MyPlane airobus(earth, 2, 0, std::make_pair(2, 0));
		//MyPlane aerobus(earth, 1, 0.1, std::make_pair(0, 0));
		std::cout << aerobus << std::endl;
		std::cout << aerobus.intersection(LR) << std::endl;

		aerobus.time(radars);
		std::cout << airobus << std::endl;
		airobus.time(radars);
	} catch (const char *a) {
		std::cout << a << std::endl;
	}

	return 0;
};

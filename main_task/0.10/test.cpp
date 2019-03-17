
#include <iostream>

#include "function.h"
#include "csv_parser.h"

using MyFunction = Function<double, double, double>;

int main(int argc, char** argv)
{
	//MyFunction a(csv_parser_read<double, double>("test_data.csv"));
	auto data = csv_parser_read<double, double>("test_data.csv");
	MyFunction a(data);
	for (double time = 0; time < 9; time+=0.1) {
		std::cout << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
	}
	return 0;
};


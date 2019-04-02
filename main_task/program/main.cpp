
#include <iostream>

#include "function.h"
#include "csv_parser.h"
#include "space/velocity.h"

using MyFunction = Function<double, double, double>;

int main(int argc, char** argv)
{
	if (argc != 2) {
		return 1;
	}
	//auto data = csv_parser_read<double, double>("test_data.csv");
	auto& data = csv_parser_read<double, double>(argv[1]);
	MyFunction a(data);
	for (double time = 0; time < 9; time+=0.1) {
		std::cout << time << " " << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
	}
	delete &data;
	return 0;
};


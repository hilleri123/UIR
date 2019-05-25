
#include <iostream>

//#include "function.h"
//#include "csv_parser.h"
//#include "space/functions/velocity.h"
#include "function.h"
#include "csv_parser.h"
#include "velocity.h"


int main(int argc, char** argv)
{
	if (argc != 2) {
		return 1;
	}
	auto& data = csv_parser_read(argv[1]);
	Function a(data);
	double h = 0.1;
	for (double time = 0; time < a.max_time()+2*h; time+=h) {
		std::cout << time << " " << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
	}
	delete &data;
	return 0;
};


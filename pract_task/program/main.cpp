
#include <iostream>
#include <fstream>
#include <cstring>

//#include "function.h"
//#include "csv_parser.h"
//#include "space/functions/velocity.h"
#include "function.h"
#include "csv_parser.h"
#include "velocity.h"


int main(int argc, char** argv)
{
	if (argc < 2) {
		return 1;
	}
	double h = 0.1;
	char* in = argv[1];
	char* out = nullptr;

	for (int i = 2; i < argc; i++) {
		if (!strcmp(argv[i], "-h")) {
			if (i+1 < argc) {
				if (argv[i+1][0] != '-') {
					h = std::stod(argv[i+1]);
				}
			}
		} else if (!strcmp(argv[i], "-o")) {
			if (i+1 < argc) {
				if (argv[i+1][0] != '-') {
					out = argv[i+1];
				}
			}
		}

	}

	auto& data = csv_parser_read(in);
	Function a(data);
	
	std::ofstream stream;

	std::cout << in << std::endl;
	if (out != nullptr) {
		std::cout << out << std::endl;
		stream.open(out);
		if (!stream.is_open()) {
			throw std::ofstream::failure("outfile not open");
		}
	}
	std::cout << h << std::endl;


	for (double time = 0; time < a.max_time()+h; time+=h) {
		if (out == nullptr) {
			std::cout << time << " " << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
		} else {
			stream << time << " " << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
		}
	}
	if (stream.is_open()) {
		stream.close();
	}
	delete &data;
	return 0;
};


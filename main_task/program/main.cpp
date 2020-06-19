
#include <iostream>
#include <fstream>
#include <cstring>

//#include "function.h"
//#include "csv_parser.h"
//#include "space/functions/velocity.h"
#include "function.h"
#include "csv_parser.h"
#include "velocity.h"
#include "sphere.h"
#include "log.h"

#include <boost/program_options.hpp>


int main(int argc, char** argv)	
{	
	namespace po = boost::program_options;

	double h = 1;
	std::string in;
	std::string out;
	//char* in = argv[1];
	//char* out = nullptr;


	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("input", po::value<std::string>(), "input file")
		("output", po::value<std::string>(), "output file")
		("step", po::value<double>(), "time step");
		
	po::variables_map vmap;
	po::store(po::parse_command_line(argc, argv, desc), vmap);
	po::notify(vmap);

	if (vmap.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}

	if (vmap.count("step"))
		h = vmap["step"].as<double>();

	if (vmap.count("input"))
		in = vmap["input"].as<std::string>();

	if (vmap.count("output"))
		out = vmap["output"].as<std::string>();


#if 0
	if (argc < 2) {
		return 2;
	}
	in = std::string(argv[1]);
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
					out = std::string(argv[i+1]);
				}
			}
		}

	}
#endif

	//auto& data = csv_parser_read(in, earth::radius());
	auto& data = csv_parser_read(in);
	Function a(data);
	
	std::ofstream stream;
#if 0
	std::ofstream plot;
	plot.open("plot.txt");
	
	for (auto i = data.begin(); i < data.end(); i++)
		plot << std::get<0>(*i).x() << " " 
			<< std::get<0>(*i).y() << " "
			<< std::get<0>(*i).z() << std::endl;
	
	plot.close();
#endif

	//std::cout << in << std::endl;
	my_log::log_it(my_log::level::info, __FUNCTION_NAME__, in);
	if (out.size() > 0) {
		//std::cout << out << std::endl;
		my_log::log_it(my_log::level::info, __FUNCTION_NAME__, out);
		stream.open(out);
		if (!stream.is_open()) {
			throw std::ofstream::failure("outfile not open");
		}
	}
	my_log::log_it(my_log::level::info, __FUNCTION_NAME__, "Height "+std::to_string(h));
	my_log::log_it(my_log::level::info, __FUNCTION_NAME__, "Time "+std::to_string(a.max_time()));
	//std::cout << h << std::endl;
	//std::cout << a.max_time() << std::endl;


	const Conversion flatting = earth::flatting_conv();

	for (double time = 0; time < a.max_time()+h; time+=h) {
		auto pair = a(time);
		Point point = std::get<0>(pair);
		Velocity velocity = std::get<1>(pair);
		double lat = point.latitude();
		double lon = point.longitude();

		//Point tmp;
		//double local_R = flatting.to(tmp.by_geo(earth::radius(), lat, lon)).radius();

		double r = point.radius() - earth::local_R(lat, lon);

		if (stream.is_open()) {
			//stream << time << " " << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
			//stream << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
			//stream << time << " " << point.radius() << " " << point.latitude() << " " << point.longitude() << " " << velocity << std::endl;
			stream << time << " H(" << r << ") lat(" << lat << ") lon(" << lon << ") v(" << velocity.v() << ", " << (velocity.max_rotate() * h)
			       	<< ") c(" << velocity.course() << ")" << std::endl;
			//stream << time << " " << a(time).radius() << " " << a(time).latitude() << " " << a(time).longitude() << std::endl;
		} else {
			//std::cout << time << " " << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
			//std::cout << a(time).x() << " " << a(time).y() << " " << a(time).z() << std::endl;
			//std::cout << time << " " << a(time).radius() << " " << a(time).latitude() << " " << a(time).longitude() << std::endl;
			//std::cout << time << " " << point.radius() << " " << point.latitude() << " " << point.longitude() << " " << velocity << std::endl;
			std::cout << time << " " << r << " " << lat << " " << lon << " " << velocity << std::endl;
		}
	}
	if (stream.is_open()) {
		stream.close();
	}
	delete &data;
	return 0;
};


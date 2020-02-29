

#include "sphere.h"


namespace sphere {
	double a = 100;
	double b = 100;
	double f = (a - b) / a;


	double error = 0.00001;

	double split_distance = 100;
}



bool direct(const double& lat1, const double& z1, const double& s, double& lat2, double& L, double& z2) {
	double U1 = atan( (1. - sphere::f) * tan(lat1) );
	double o1 = atan( tan(U1) / cos(z1) );
	double z = cos(U1) * sin(z1);

	//u_2 = u^2
	double u_2 = pow(cos(z1), 2.)* (pow(sphere::a, 2.) - pow(sphere::b, 2.)) / pow(sphere::b, 2.);

	double A = 1. + (u_2 / 16384.) * (4096. + u_2 * (-768. + u_2 * (320. - 175. * u_2)));
	double B = (u_2 / 1024.) * (256. + u_2 * (-128. + u_2 * (74. - 47. * u_2)));

	double o = s / (sphere::b * A);

	double delta_o;

	//om2 = 2 * om
	double om2;

	do {
		om2 = 2. * o1 + o;
		delta_o = B * sin(o) * (cos(om2) + B / 4. * (cos(o) * (-1. + 2. * pow(cos(om2), 2))
				       	- B / 6. * cos(om2) * (-3. + 4. * pow(sin(o), 2)) * (-3. + 4. * pow(cos(om2), 2))));
		o = s / (sphere::b * A) + delta_o;
	} while (less(abs(delta_o), sphere::error));

	//---------------------------------------

	lat2 = atan( (sin(U1) * cos(o) + cos(U1) * sin(o) * cos(z1))
		       	/ ((1. - sphere::f) * pow( (pow(sin(z), 2) + pow( (sin(U1) * sin(o) - cos(U1) * cos(o) * cos(z1)) , 2)) , 0.5)) );

	double k = atan( (sin(o) * sin(z1)) / (cos(U1) * cos(o) - sin(U1) * sin(o) * cos(z1)) );

	double C = (sphere::f / 16.) * pow(cos(z), 2) * (4. + sphere::f * (4. - 3. * pow(cos(z), 2)));

	L = k - (1. - C) * sphere::f * sin(z) * (o + C * sin(o) * (cos(om2) + C * cos(o) * (-1. + 2. * pow(cos(om2), 2))));

	z2 = atan( sin(z) / (-sin(U1) * sin(o) + cos(U1) * cos(o) * cos(z1)) );

	return true;
}

bool inverse(const double& lat1, const double& lat2, const double& L, double& s, double& z1, double& z2) {
	
	double k = L;
	double prev_k = 0;

	double U1 = atan( (1. - sphere::f) * tan(lat1) );
	double U2 = atan( (1. - sphere::f) * tan(lat2) );

	double o;
	//om2 = 2 * om
	double om2;

	do {
		o = asin( pow( ( pow(cos(U2) * sin(k), 2) + pow( (cos(U1) * sin(U2) - sin(U1) * cos(U2) * cos(k)) , 2) ) , 0.5) );
		std::cout << "sin2 o - " << o << std::endl;

		o = acos( sin(U1) * sin(U2) + cos(U1) * cos(U2) * cos(k) );
		std::cout << "cos o - " << o << std::endl;

		double z = asin( cos(U1) * cos(U2) * sin(k) / sin(o) );

		//om2 = 2 * om
		om2 = acos( cos(o) - 2. * sin(U1) * sin(U2) / pow(cos(z), 2) );

		double C = (sphere::f / 16.) * pow(cos(z), 2) * (4. + sphere::f * (4. - 3. * pow(cos(z), 2)));

		prev_k = k;
		k = L + (1. - C) * sphere::f * sin(z) * (o + C * sin(o) * (cos(om2) + C * cos(o) * (-1. + 2. * pow(cos(om2), 2))));
		

	} while (less(abs(k - prev_k), sphere::error));

	z1 = atan( (cos(U2) * sin(k)) / (cos(U1) * sin(U2) - sin(U1) * cos(U2) * cos(k)) );

	z2 = atan( (cos(U1) * sin(k)) / (- sin(U1) * cos(U2) + cos(U1) * sin(U2) * cos(k)) );

	//u_2 = u^2
	double u_2 = pow(cos(z1), 2.)* (pow(sphere::a, 2.) - pow(sphere::b, 2.)) / pow(sphere::b, 2.);

	double A = 1. + (u_2 / 16384.) * (4096. + u_2 * (-768. + u_2 * (320. - 175. * u_2)));
	double B = (u_2 / 1024.) * (256. + u_2 * (-128. + u_2 * (74. - 47. * u_2)));

	double delta_o = B * sin(o) * (cos(om2) + B / 4. * (cos(o) * (-1. + 2. * pow(cos(om2), 2))
				       	- B / 6. * cos(om2) * (-3. + 4. * pow(sin(o), 2)) * (-3. + 4. * pow(cos(om2), 2))));
	s = sphere::b * A * (o - delta_o);


	return true;
}


std::vector<BzCurve> orthodoxy(const Point& first, const Point& second) {

	std::vector<BzCurve> result;

	double lat1, lat2, L;
	double s, z1, z2;

	lat1 = first.latitude();
	lat2 = second.latitude();
	L = second.longitude() - first.longitude();

	if (!inverse(lat1, lat2, L, s, z1, z2)) {
		std::cerr << "bool inverse(const double& lat1, const double& lat2, const double& L, double& s, double& z1, double& z2) failed" << std::endl;
	}

	std::size_t n = static_cast<std::size_t>(s / sphere::split_distance) + 1;

	const std::size_t N = 4;

	double tmp_s = sphere::split_distance / (N - 1);

	std::array<Point, N> tmp;
	//tmp.front() = first;
	tmp.fill(first);

	for (std::size_t i = 0; i < n; i++) {
		if (i - 1 == n)
			tmp_s = (s - sphere::split_distance * i) / (N - 1);

		for (std::size_t j = 0; j < N - 1; j++) {
			Point& curr = tmp.at(j);
			Point& next = tmp.at(j+1);

			lat1 = curr.latitude();

			if (!direct(lat1, z1, tmp_s, lat2, L, z2)) {
				std::cerr << "bool direct(const double& lat1, const double& z1, const double& s, double& lat2, double& L, double& z2) failed" << std::endl;
			}
			next.by_geo(curr.radius(), lat2, curr.longitude() + L);
			z1 = z2;
		}

		result.emplace_back(tmp);
		
		tmp.front() = tmp.back();
	}

	return result;
}



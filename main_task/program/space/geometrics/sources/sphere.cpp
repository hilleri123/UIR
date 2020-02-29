

#include "sphere.h"


namespace sphere {
	double a = 100;
	double b = 100;
	double f = (a - b) / a;


	double error = 0.00001;
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

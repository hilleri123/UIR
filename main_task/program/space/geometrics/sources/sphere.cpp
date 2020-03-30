

#include "sphere.h"


namespace sphere {
	//double a = 100;
	//double b = 100;
	//double f = (a - b) / a;
	//double a = 6378.388;
	double a = 6378.137;
	//double f = 1./297.;
	double f = 1./298.257223263;
	double b = a - f * a;

	double error = 0.001;

	double split_distance = 100;


	//double R_earth = R_EARTH;
	//double R_earth = 6400;

	//Matrix flatting = 
}


double earth::radius() {
	return sphere::a;
	//return sphere::R_earth;
}

Conversion earth::flatting_conv() {
	Vector flatting(Point(1,1,sphere::b / sphere::a));
	Matrix to, from;
	Matrix::multiplay_foreward_backward(to, from, Matrix::comp, &flatting);
	return Conversion(to, from);
}

Vector earth::norm(double lat, double lon) {
	Point p;
	p.by_geo(earth::radius(), lat, lon);
	//Sphere : (x/a)^2+(y/a)^2+(z/b)^2=1
	//F'x(p)*(x-px) + F'x(p)*(x-px) + F'x(p)*(x-px) = 0 
	//Ax+By+Cz+D=0
	//A = 2px/a^2
	double x = 2*p.x() / pow(sphere::a, 2);
	//B = 2py/a^2
	double y = 2*p.y() / pow(sphere::a, 2);
	//C = 2pz/b^2
	double z = 2*p.z() / pow(sphere::b, 2);
	Vector res(Point(x, y, z));
	res.normolize();
	return res;
}

Vector earth::norm(Point p) {
	return earth::norm(p.latitude(), p.longitude());
}

double earth::H(Point p) {
	return p.radius() - earth::local_R(p);
}


double earth::local_R(double lat, double lon) {
	Point p;
	p.by_geo(earth::radius(), lat, lon);
	const Conversion flatting = earth::flatting_conv();
	return flatting.to(p).radius();
}

double earth::local_R(Point p) {
	return local_R(p.latitude(), p.longitude());
}

bool direct(const double& lat1, const double& z1, const double& s, double& lat2, double& L, double& z2) {

	if (lat1 != lat1 || z1 != z1 || s != s) {
		std::cerr << "nan found lat1(" << lat1 << ") z1(" << z1 << ") s(" << s << ")" << std::endl;
		return false;
	}

	double U1 = atan( (1. - sphere::f) * tan(lat1) );
	double o1 = atan( tan(U1) / cos(z1) );
	double z = cos(U1) * sin(z1);

	//u_2 = u^2
	double u_2 = pow(cos(z1), 2.) * (pow(sphere::a, 2.) - pow(sphere::b, 2.)) / pow(sphere::b, 2.);

	double A = 1. + (u_2 / 16384.) * (4096. + u_2 * (-768. + u_2 * (320. - 175. * u_2)));
	double B = (u_2 / 1024.) * (256. + u_2 * (-128. + u_2 * (74. - 47. * u_2)));

	double o = s / (sphere::b * A);

	double delta_o;

	//om2 = 2 * om
	double om2;

	//std::cout << "u_2 " << u_2 << " A " << A << " B " << B << std::endl;
	//int max = 0;

	do {
		om2 = 2. * o1 + o;
		delta_o = B * sin(o) * (cos(om2) + B / 4. * (cos(o) * (-1. + 2. * pow(cos(om2), 2))
				       	- B / 6. * cos(om2) * (-3. + 4. * pow(sin(o), 2)) * (-3. + 4. * pow(cos(om2), 2))));
		o = s / (sphere::b * A) + delta_o;

		//std::cout << "fabs(delta_o) " << fabs(delta_o) << " o " << o << std::endl;
		//max++;

	} while (less(sphere::error, fabs(delta_o))/* && max < 10*/);

	//---------------------------------------

	//lat2 = atan( (sin(U1) * cos(o) + cos(U1) * sin(o) * cos(z1))
		       	// / ((1. - sphere::f) * pow( (pow(sin(z), 2) + pow( (sin(U1) * sin(o) - cos(U1) * cos(o) * cos(z1)) , 2)) , 0.5)) );
	lat2 = atan2( sin(U1) * cos(o) + cos(U1) * sin(o) * cos(z1) ,
		       	(1. - sphere::f) * pow( (pow(sin(z), 2) + pow( (sin(U1) * sin(o) - cos(U1) * cos(o) * cos(z1)) , 2)) , 0.5) );

	//double k = atan( (sin(o) * sin(z1)) / (cos(U1) * cos(o) - sin(U1) * sin(o) * cos(z1)) );
	double k = atan2( sin(o) * sin(z1) , cos(U1) * cos(o) - sin(U1) * sin(o) * cos(z1) );

	double C = (sphere::f / 16.) * pow(cos(z), 2) * (4. + sphere::f * (4. - 3. * pow(cos(z), 2)));

	L = k - (1. - C) * sphere::f * sin(z) * (o + C * sin(o) * (cos(om2) + C * cos(o) * (-1. + 2. * pow(cos(om2), 2))));

	//z2 = atan( sin(z) / (-sin(U1) * sin(o) + cos(U1) * cos(o) * cos(z1)) );
	z2 = atan2( sin(z) , -sin(U1) * sin(o) + cos(U1) * cos(o) * cos(z1) );

	return true;
}

bool inverse(const double& lat1, const double& lat2, const double& L, double& s, double& z1, double& z2) {

	if (lat1 != lat1 || lat2 != lat2 || L != L) {
		std::cerr << "nan found lat1(" << lat1 << ") lat2(" << lat2 << ") L(" << L << ")" << std::endl;
		return false;
	}
	
	double k = L;
	double prev_k = 0;

	double U1 = atan( (1. - sphere::f) * tan(lat1) );
	double U2 = atan( (1. - sphere::f) * tan(lat2) );

	//std::cout << "U1 " << U1 << " U2 " << U2 << std::endl;

	double o;
	//om2 = 2 * om
	double om2;

	do {
		//equals
		double sin_o = pow( ( pow(cos(U2) * sin(k), 2) + pow( (cos(U1) * sin(U2) - sin(U1) * cos(U2) * cos(k)) , 2) ) , 0.5);
		double cos_o = sin(U1) * sin(U2) + cos(U1) * cos(U2) * cos(k);
		//o = atan(sin_o / cos_o);
		o = atan2(sin_o, cos_o);


		//double z = asin( cos(U1) * cos(U2) * sin(k) / sin(o) );
		double z = asin( round_one( cos(U1) * cos(U2) * sin(k) / sin_o ) );

		//om2 = 2 * om
		//om2 = acos( cos(o) - 2. * sin(U1) * sin(U2) / pow(cos(z), 2) );
		om2 = acos( round_one( cos_o - 2. * sin(U1) * sin(U2) / pow(cos(z), 2) ) );

		double C = (sphere::f / 16.) * pow(cos(z), 2) * (4. + sphere::f * (4. - 3. * pow(cos(z), 2)));

		//std::cout << "o " << o << " z " << z << " om2 " << om2 << " C " << C << std::endl;

		prev_k = k;
		//k = L + (1. - C) * sphere::f * sin(z) * (o + C * sin(o) * (cos(om2) + C * cos(o) * (-1. + 2. * pow(cos(om2), 2))));
		k = L + (1. - C) * sphere::f * sin(z) * (o + C * sin_o * (cos(om2) + C * cos_o * (-1. + 2. * pow(cos(om2), 2))));
		
		//std::cout << "fabs(k - prev_k) " << fabs(k - prev_k) << std::endl;

	} while (less(sphere::error, fabs(k - prev_k)));

	//z1 = atan( (cos(U2) * sin(k)) / (cos(U1) * sin(U2) - sin(U1) * cos(U2) * cos(k)) );
	z1 = atan2( cos(U2) * sin(k) , cos(U1) * sin(U2) - sin(U1) * cos(U2) * cos(k) );

	//z2 = atan( (cos(U1) * sin(k)) / (- sin(U1) * cos(U2) + cos(U1) * sin(U2) * cos(k)) );
	z2 = atan2( cos(U1) * sin(k) , - sin(U1) * cos(U2) + cos(U1) * sin(U2) * cos(k) );

	//u_2 = u^2
	double u_2 = pow(cos(z1), 2.)* (pow(sphere::a, 2.) - pow(sphere::b, 2.)) / pow(sphere::b, 2.);

	double A = 1. + (u_2 / 16384.) * (4096. + u_2 * (-768. + u_2 * (320. - 175. * u_2)));
	double B = (u_2 / 1024.) * (256. + u_2 * (-128. + u_2 * (74. - 47. * u_2)));

	double delta_o = B * sin(o) * (cos(om2) + B / 4. * (cos(o) * (-1. + 2. * pow(cos(om2), 2))
				       	- B / 6. * cos(om2) * (-3. + 4. * pow(sin(o), 2)) * (-3. + 4. * pow(cos(om2), 2))));
	s = sphere::b * A * (o - delta_o);


	return true;
}


std::vector<BzCurve> orthodoxy(const Point& first_point, const Point& second, Vector* direction) {

	std::vector<BzCurve> result;
	//std::cout << "bz curve h1(" << (first_point.radius() - earth::local_R(first_point)) << ") h2(" << (second.radius() - earth::local_R(second)) << ")" << std::endl;

	double lat1, lat2, L;
	double s, z1, z2;

	const std::size_t N = 4;
	std::array<Point, N> tmp;
	//tmp.front() = first;

	Point first = first_point;

	do {
		tmp.fill(first);

		//lat1 = first.latitude();
		//lat2 = second.latitude();
		//L = second.longitude() - first.longitude();

		//if (!inverse(lat1, lat2, L, s, z1, z2)) {
			//std::cerr << "bool inverse(const double& lat1, const double& lat2, const double& L, double& s, double& z1, double& z2) failed" << std::endl;
		//}
		//std::cout << "S : " << s << std::endl;
		//std::cout << "z2 " << z2 << std::endl;

		//std::size_t n = static_cast<std::size_t>(s / sphere::split_distance) + 1;

		//double tmp_s = sphere::split_distance / (N - 1);
		//double tmp_tmp_s = s;

		//for (std::size_t i = 0; i < n; i++) {
		//if (i - 1 == n)
		//if (s < tmp_s)
			//tmp_s = (s - sphere::split_distance * i) / (N - 1);
			//tmp_s = s / (N - 1);

		//std::cout << "tmp_s : " << tmp_s << std::endl;

		const Conversion flatting = earth::flatting_conv();

		double curr_len = 0;

		for (std::size_t j = 0; j < N - 1; j++) {
			Point& curr = tmp.at(j);
			Point& next = tmp.at(j+1);

			lat1 = curr.latitude();
			lat2 = second.latitude();
			L = second.longitude() - curr.longitude();

			if (!inverse(lat1, lat2, L, s, z1, z2)) {
				std::cerr << "bool inverse(const double& lat1, const double& lat2, const double& L, double& s, double& z1, double& z2) failed" << std::endl;
			}
			//std::cout << "lat1 " << lat1 << " lat2 " << lat2 << " L " << L << " s " << s << std::endl;
			//std::cout << "s " << s << " z1 " << z1 << " z2 " << z2 << std::endl;

			double tmp_s = sphere::split_distance / (N - 1);
			if (s < tmp_s)
				tmp_s = s / (N - 1);

			//std::cout << "curr " << curr << std::endl;

			//lat1 = curr.latitude();

			if (!direct(lat1, z1, tmp_s, lat2, L, z2)) {
				std::cerr << "bool direct(const double& lat1, const double& z1, const double& s, double& lat2, double& L, double& z2) failed" << std::endl;
			}

			//std::cout << "lat2 " << lat2 << " L " << L << " z2 " << z2 << std::endl;
			//next.by_geo(curr.radius(), lat2, curr.longitude() + L);
			//Point tmp_point;
			//double h1 = flatting.to(tmp_point.by_geo(earth::radius(), curr.latitude(), curr.longitude())).radius();
			//double h2 = flatting.to(tmp_point.by_geo(earth::radius(), lat2, curr.longitude() + L)).radius();

			double h1 = earth::local_R(curr);
			double h2 = earth::local_R(lat2, curr.longitude() + L);

			double H = (curr.radius() - h1) + h2;
			next.by_geo(H, lat2, curr.longitude() + L);
			//std::cout << "bz curve " << next << " h1(" << (curr.radius() - h1) << ") h2(" << (next.radius() - h2) << ")" << std::endl;
			//z1 = z2;

			//tmp_tmp_s -= tmp_s;
			//std::cout << "z " << z1 << std::endl;
			//std::cout << "tmp tmp s " << tmp_tmp_s << std::endl;
			curr_len += tmp_s;
		}

		result.emplace_back(tmp);

		
		result.back().set_len(curr_len * first.radius() / earth::radius());
		//result.back().set_len(curr_len);
		//result.back().set_len(tmp_s * (N - 1));

		//s -= tmp_s * (N - 1);
		
		//tmp.front() = tmp.back();
		first = tmp.back();
	} while (more(s, 0));

	if (direction != nullptr) {
		Point O(0,0,0);
		
		Vector south(O, Point(0,0,earth::radius()));
		Vector new_z(second, O);
		Vector new_y = new_z * south;
		
		Conversion conv(&second, nullptr, &new_y, &new_z);

		Vector tmp(Point(cos(z2),sin(z2),0));

		*direction = conv.from(tmp);
		//std::cout << *direction << std::endl;
	}
		

	return result;
}


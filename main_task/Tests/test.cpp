
#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include "vector.h"
#include "metrics.h"
#include "part_of_function.h"
#include "combinator.h"
#include "function.h"
#include "point.h"
#include "velocity.h"



int main(int argc, char** argv)
{
	{
		Point point;
		Vector vector;
		PartOfFunction part;
	}
	{
		Point zero(0,0,0);
		Vector vector(zero, zero);
	}
	{
		Point a(0, 1, 0);
		Point b(0, 0, 1);
		Point o(0, 0, 0);
		Vector oa(o, a);
		Vector ob(o, b);
		assert((oa^ob) == atan(1)*2);
	}
	{
		Point o(0, 0, 0);
		Point a(3, 4, 0);
		Vector A(o, a);
		Point b(4, 3, 0);
		Vector B(o, b);
		assert(A == (A + B - B));
	}
	{
		for (double i0 = 0.1; i0 < 15; i0+=0.2) {
			Point o(0,0,0);
			Point a(i0,0,0);
			Vector A(o,a);
			int x = 0;
			int y = 0;
			int xy = 0;
			int err = 0;
			int all = 0;
			for (double i1 = -3.2; i1 < 3.2; i1+=0.3) {
				Point a1(cos(i1), sin(i1), 0);
				Vector A1(o,a1);
				for (double i = -4; i < 4; i+=0.1) {
					Vector F = A.rotate(A1, i);
					//std::cout << "len F = " << Vector::norm(F) << " len A = " << Vector::norm(A) << std::endl;
					assert(equal(Vector::norm(F), Vector::norm(A)));
					Point f = F + o;
					all++;
					bool show = false;
					char ch = 'i';
					double angle = i*copysign(1, a1.y());
					//assert(equal(f.x(), Vector::norm(A)*cos(angle)) && equal(f.y(), Vector::norm(A)*sin(angle)));
					if (equal(f.x(), Vector::norm(A)*cos(angle)) && equal(f.y(), Vector::norm(A)*sin(angle))){
						ch = '0';
						xy++;
						show = false;
					} else if (equal(f.x(), Vector::norm(A)*cos(angle))) {
						ch = 'x';
						x++;
						show = true;
					} else if (equal(f.y(), Vector::norm(A)*sin(angle))) {
						ch = 'y';
						y++;
						show = true;
					} else {
						ch = 'e';
						err++;
						show = true;
					}
					if (show) {
						//std::cout << "i = " << (i / atan(1) * 45) << " ort " << ((A^A1) / atan(1) * 45) << " --" << ch << std::endl;
						std::cout << "len = " << i0 << " i = " << (i / atan(1) * 45) << " ort " << (i1 / atan(1) * 45) << " --" << ch << std::endl;
						std::cout << " ort  " << (Point(0,0,0)+A1) << std::endl;
						std::cout << "! result " << f << " " << ((A^F) / atan(1) * 45) << std::endl;
						std::cout << "    " << Point(Vector::norm(A)*cos(angle), Vector::norm(A)*sin(angle), 0) << std::endl;
						//std::cout << "! A2" << s << " " << (A^A2) << std::endl << std::endl;
					}
				}
			}
			//std::cout << "err " << err << " xy " << xy << " " << " x " << x << " y " << y << " ALL " << all << std::endl;
			assert(xy == all);
		}
	}
	{
		for (int i = 0; i < 100; i++) {
			std::srand(unsigned(std::time(0)));
			int n = std::rand() % 20;
			std::vector<std::pair<Point, Velocity>> result;
			for (int j = 0; j < n; j++) {
				double h = 0.001;
				int m = 10000;
				double x = (std::rand()%m)*h;
				double y = (std::rand()%m)*h;
				double z = (std::rand()%m)*h;
				Velocity* v = nullptr;
				INIT(v, Velocity, (((std::rand()%m)*h)/1000));
				if (v != nullptr) {
					auto pair = std::make_pair(Point(x, y, z), *v);
					std::cout << "at " << result.size() << " " << Point(x, y, z) << " v " << v->v() << std::endl;
					result.push_back(pair);
					delete v;
				}
				//std::cout << "check 0" << std::endl;
			}
			Function f(result);
			//std::cout << "check 1" << std::endl;
			std::size_t id = 0;
			Point a = f(0);
			Point b = f(0);
			for (double t = 0; t < 1000; t+=0.01) {
				//std::cout << "check 2" << std::endl;
				if (!Interval::in_interval(t, f.interval(id))) {
					id++;
				}
				Point c = f(t);
				if (id < result.size()) {
					//std::cout << "norm " << Point::norm(a, b) << " velocity*t " << (std::get<1>(result.at(id))*0.01) << std::endl;
					assert(equal_or_less(Point::norm(a, b), std::get<1>(result.at(id))*0.01));
					assert(equal_or_less(Vector(a, b)^Vector(b, c), std::get<1>(result.at(id)).max_rotate()));
				} else {
					//std::cout << "norm " << Point::norm(a, b) << " velocity*t " << (std::get<1>(result.back())*0.01) << std::endl;
					assert(equal_or_less(Point::norm(a, b), std::get<1>(result.back())*0.01));
					assert(equal_or_less(Vector(a, b)^Vector(b, c), std::get<1>(result.back()).max_rotate()));
				}
				a = b;
				b = c;
			}
		}
	}


	return 0;
};

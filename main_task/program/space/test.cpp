
#include <iostream>
#include <cassert>

#include "vector.h"
#include "metrics.h"
//#include "part_of_function.h"
//#include "combinator.h"
#include "point.h"

using MyPoint = Point<double>;
using MyVector = Vector<double>;
//using MyPart = PartOfFunction<double, double, double>;

//actually not test

int main(int argc, char** argv)
{
	{
		MyPoint point;
		MyVector vector;
		//MyPart part;
	}
	{
		MyPoint zero(0,0,0);
		MyVector vector(zero, zero);
	}
	{
		MyPoint a(0, 1, 0);
		MyPoint b(0, 0, 1);
		MyPoint o(0, 0, 0);
		MyVector oa(o, a);
		MyVector ob(o, b);
		assert((oa^ob) == atan(1)*2);
	}
	{
		MyPoint o(0, 0, 0);
		MyPoint a(3, 4, 0);
		MyVector A(o, a);
		MyPoint b(4, 3, 0);
		MyVector B(o, b);
		assert(A == (A + B - B));
	}
#if 0
	{
		MyPoint o(0,0,0);
		MyPoint a(0,1,0);
		MyPoint b(1,1,0);
		MyPoint c(1,0,0);
		MyPoint d(1,-1,0);
		MyPoint e(0,-1,0);
		MyVector A(o, a);
		MyVector B(o, b);
		MyVector C(o, c);
		MyVector D(o, d);
		MyVector E(o, e);
		for (double i = -3; i < 4; i += 0.2) {
			std::cout << "\ti = " << i << std::endl;
			std::cout << "A B " << (o + A.rotate(B, i)) << " ^ " << (A^B) << std::endl;
			std::cout << "A C " << (o + A.rotate(C, i)) << " ^ " << (A^C) << std::endl;
			std::cout << "A D " << (o + A.rotate(D, i)) << " ^ " << (A^D) << std::endl;
			std::cout << "A E " << (o + A.rotate(E, i)) << " ^ " << (A^E) << std::endl;
		}
	}
#endif
	{
		MyPoint o(0,0,0);
		MyPoint a(1,0,0);
		MyVector A(o,a);
		int x = 0;
		int y = 0;
		int xy = 0;
		int err = 0;
		int all = 0;
		for (double i1 = -3.2; i1 < 3.2; i1+=0.3) {
			MyPoint a1(cos(i1), sin(i1), 0);
			MyVector A1(o,a1);
			//for (double i2 = -3.2; i2 < 3.2; i2+=0.1) {
				//MyPoint a2(sin(i2), cos(i2), 0);
				//MyVector A2(o,a2);
				for (double i = -4; i < 4; i+=0.1) {
					MyVector F = A.rotate(A1, i);
					MyPoint f = F + o;
					all++;
					//MyPoint s = A.rotate(A2, i) + o;
					//if (f != s) {
						bool show = false;
						//if (equal<double>(f.x(), -s.x()) && equal<double>(f.y(), -s.y())) {
							//xy++;
							//show = false;
						//} else if (equal<double>(f.x(), -s.x())) {
							//x++;
							//show = false;
						//} else if (equal<double>(f.y(), -s.y())) {
							//y++;
							//show = true;
						//} else if (f != s) {
							//err++;
							//show = true;
						//}
						char ch = 'i';
						//double angle = i;
						double angle = copysign(i, a1.y());
						if (equal<double>(f.x(), cos(angle)) && equal<double>(f.y(), sin(angle))){
							ch = '0';
							xy++;
							show = true;
						} else if (equal<double>(f.x(), cos(angle))) {
							ch = 'x';
							x++;
							show = true;
						} else if (equal<double>(f.y(), sin(angle))) {
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
							std::cout << "i = " << (i / atan(1) * 45) << " ort " << (i1 / atan(1) * 45) << " --" << ch << std::endl;
							std::cout << "! A1" << f << " " << ((A^F) / atan(1) * 45) << std::endl;
							std::cout << "    " << MyPoint(cos(angle), sin(angle), 0) << std::endl;
							//std::cout << "! A2" << s << " " << (A^A2) << std::endl << std::endl;
						}
					//}
				}
			//}
		}
		std::cout << "err " << err << " xy " << xy << " " << " x " << x << " y " << y << " ALL " << all << std::endl;
	}


	return 0;
};

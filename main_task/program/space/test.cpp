
#include <iostream>

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
		std::cout << (oa^ob) << std::endl;
	}
	{
		MyPoint o(0, 0, 0);
		MyPoint a(3, 4, 0);
		MyVector A(o, a);
		MyPoint b(4, 3, 0);
		MyVector B(o, b);
		if (A == B.rotate_z(A.xy_angle(B))) {
			std::cout << "A B correct" << std::endl;
		}
		if (A == B.rotate_z(B.xy_angle(A))) {
			std::cout << "B A correct" << std::endl;
		}
		auto c = B.rotate_z(B.xy_angle(A)) + o;
		std::cout << B.xy_angle(A) << " " << A.xy_angle(B) << std::endl;
		std::cout << c.x() << " " << c.y() << " " << c.z() << std::endl;
	}


	return 0;
};

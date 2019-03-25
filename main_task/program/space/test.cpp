
#include <iostream>

#include "vector.h"
#include "metrics.h"
#include "part_of_function.h"
#include "combinator.h"
#include "point.h"

using MyPoint = Point<double>;
using MyVector = Vector<double>;
using MyPart = PartOfFunction<double, double, double>;

//actually not test

int main(int argc, char** argv)
{
	{
		MyPoint point;
		MyVector vector;
		MyPart part;
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
	return 0;
};

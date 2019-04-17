
#include "metrics.h"

namespace error
{
	double distance = 0.000005;
}

namespace comparison
{
	std::size_t equal = 1;
	std::size_t less = 2;
	std::size_t more = 4;
	std::size_t equal_or_less = equal | less;
	std::size_t equal_or_more = equal | more;


	std::size_t compare(double a, double b)
	{
		std::size_t result = 0;
		if ((a + error::distance >= b) && (a - error::distance <= b)) {
			result = result | equal;
		}
		if (a + error::distance <= b) {
			result = result | less;
		}
		if (a - error::distance >= b) {
			result = result | more;
		}
		return result;
	}
}



bool equal(double a, double b)
{
	if (comparison::compare(a, b) == comparison::equal) { return true; } else { return false; }
}

bool equal_or_more(double a, double b)
{
	if (comparison::compare(a, b) == comparison::equal_or_more) { return true; } else { return false; }
}

bool equal_or_less(double a, double b)
{
	if (comparison::compare(a, b) == comparison::equal_or_less) { return true; } else { return false; }
}


bool less(double a, double b)
{
	if (comparison::compare(a, b) == comparison::less) { return true; } else { return false; }
}

bool more(double a, double b)
{
	if (comparison::compare(a, b) == comparison::more) { return true; } else { return false; }
}

bool is_null(double a)
{
	return equal(a, 0);
}


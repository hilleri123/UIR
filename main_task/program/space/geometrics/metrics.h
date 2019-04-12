
#pragma once

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


	template <typename scalar>
	std::size_t compare(scalar a, scalar b)
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


template <typename scalar>
bool equal(scalar a, scalar b)
{
	if (comparison::compare<scalar>(a, b) == comparison::equal) { return true; } else { return false; }
}

template <typename scalar>
bool equal_or_more(scalar a, scalar b)
{
	if (comparison::compare<scalar>(a, b) == comparison::equal_or_more) { return true; } else { return false; }
}

template <typename scalar>
bool equal_or_less(scalar a, scalar b)
{
	if (comparison::compare<scalar>(a, b) == comparison::equal_or_less) { return true; } else { return false; }
}


template <typename scalar>
bool less(scalar a, scalar b)
{
	if (comparison::compare<scalar>(a, b) == comparison::less) { return true; } else { return false; }
}

template <typename scalar>
bool more(scalar a, scalar b)
{
	if (comparison::compare<scalar>(a, b) == comparison::more) { return true; } else { return false; }
}

template <typename scalar>
bool is_null(scalar a)
{
	return equal(a, static_cast<scalar>(0));
}

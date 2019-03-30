
#pragma once

#include <cmath>

#include "point.h"
#include "vector.h"
#include "part_of_function.h"
#include "velocity.h"


template <typename scalar, class velocity, typename t>
class Rotate : PartOfFunction<scalar, velocity, t>
{
public:
	explicit Rptate(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>), velocity v = 1)
		: PartOfFunction<scalar, velocity, t>(first, second, velocity)
	{
		// A - start point
		// a - start vector
		// B - end point
		// b - end vector
		// O - center
		// R - radius
		auto& a = v.projection(Vector<scalar>(Point<scalar>(0, 0, 1)));
		Point<scalar>& B = *new Point<scalar>(second.x(), second.y(), first.z());

		auto&  v.projection(Vector<scalar>(Point<scalar>(0, 0, 1)));
		auto& AO = a.direction.rotate(atan(1)*2*sign)
		_center = AO + first;
	}

	virtual bool init() override
	{
		if (err || PartOfFunction<scalar, velocity, t>::init()) {
			return false;
		} else {
			return true;
		}
	}

	virtual Point<scalar>& operator() const override
	{
		saclar x = 1;
		saclar y = 1;
		saclar z = 1;
		return Point<scalar>(x, y, z);
	}

	virtual t max_time() const override
	{
		return 1;
	}

	virtual ~Rotate() override
	{}
protected:
private:
	bool err = false;
	Point<scalar> _center;
}; 


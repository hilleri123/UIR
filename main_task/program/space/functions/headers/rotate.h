
#pragma once

#include <cmath>
#include <iostream>
#include <cassert>

//#include "../geometrics/point.h"
//#include "../geometrics/vector.h"
//#include "velocity.h"
//#include "../init.h"
#include "point.h"
#include "vector.h"
#include "velocity.h"
#include "init.h"


class Rotate : base_init
{
public:
	explicit Rotate(Point first = Point(), Point second = Point(), Velocity v = Velocity(), Vector direction = Vector(Point(0,0,0), Point(1,0,0)));

	Rotate(const Rotate&) = default;
	Rotate(Rotate&&) = default;
	Rotate& operator=(const Rotate&) = default;
	Rotate& operator=(Rotate&&) = default;

	virtual bool init() const override;

	virtual Point operator()(double time) const;

	virtual double max_time() const;

	virtual Point end_point() const;

	virtual Vector direction() const;

	virtual ~Rotate() override;
protected:
private:
	bool _err = false;
	double _end_rotate;
	Point _begin;
	Point _end;
	Point _end_point;
	Point _center;
	Velocity _velocity;
	Vector _direction;
	double _clocks_hand = 1;
	
	double _k = 0; // v = v0 - k * t
}; 


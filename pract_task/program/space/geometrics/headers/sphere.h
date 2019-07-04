

#pragma once

#include <cmath>

#include <cassert>
#include <iostream>

#include "init.h"
#include "vector.h"
#include "point.h"


class Sphere : base_init
{
public:
	explicit Sphere(Point center = Point(), Point plane = Point(), double dir = 0);
	explicit Sphere(Point center = Point(), double r = 1, double dir = 0, double lat = 0, double lon = 0);

	Sphere(const Sphere& ) = default;
	Sphere(Sphere&& ) = default;
	Sphere& operator=(const Sphere& ) = default;
	Sphere& operator=(Sphere&& ) = default;

	Sphere new_sphere(Point ) const;
	Sphere new_sphere(double ) const;
	
	virtual bool init() const override;

	Point center() const;
	double radius() const;

	double direction() const;
	double latitude() const;
	double longitude() const;

	Point plane() const;

	bool check() const;

	friend std::ostream& operator<<(std::ostream&, const Sphere&);
	friend std::ostream& operator<<(std::ostream&, Sphere&&);

	virtual ~Sphere();

protected:
	Point _center;
	double _radius;

	double _direction;
	double _latitude;
	double _longitude;
};

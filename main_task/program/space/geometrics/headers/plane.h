
#pragma once

#include <memory>

#include "vector.h"
#include "point.h"
#include "init.h"


class Plane : base_init
{
public:
	explicit Plane(Vector vector = Vector(Point(0,0,1)), Point point = Point());
	
	Plane(Point first, Point second, Point third);

	Plane(const Plane&) = default;
	Plane(Plane&&) = default;
	Plane& operator=(const Plane&) = default;
	Plane& operator=(Plane&&) = default;

	bool operator==(const Plane&) const;
	bool operator!=(const Plane&) const;
	bool operator==(Plane&&) const;
	bool operator!=(Plane&&) const;

	Plane operator!() const;

	bool operator&(const Point&) const;
	bool operator&(Point&&) const;
	bool operator&(const Vector&) const;
	bool operator&(Vector&&) const;

	virtual bool init() const override;
	
	virtual ~Plane() override;
protected:
	Vector _norm;
	Point _center;
};

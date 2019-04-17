
#pragma once

#include "point.h"
#include "vector.h"
#include "plane.h"
#include "init.h"

#include <cmath>

class Circle : base_init
{
public:
	explicit Circle(Vector vector = Vector(), Plane plane = Plane());

	Circle(const Circle&) = default;
	Circle(Circle&&) = default;
	Circle& operator=(const Circle&) = default;
	Circle& operator=(Circle&&) = default;

	Point operator()(double) const;

	Plane plane() const;
	Vector vector() const;

	friend bool operator&(const Plane&, const Circle&);
	friend bool operator&(const Plane&, Circle&&);
	friend bool operator&(Plane&&, const Circle&);
	friend bool operator&(Plane&&, Circle&&);

	virtual bool init() const override;
	virtual ~Circle() override;
protected:
	Vector _vector;
	Plane _plane;
};

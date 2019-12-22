
#pragma once

#include <memory>

#include <iostream>

//#include "../geometrics/point.h"
//#include "../geometrics/vector.h"
//#include "../init.h"
//#include "rotate.h"
#include "point.h"
#include "vector.h"
#include "init.h"
#include "velocity.h"
#include "rotate.h"
#include "trans_matrix.h"
#include "xy_circle.h"

class PartOfFunction : base_init
{
public:
	explicit PartOfFunction(const Point& first = *std::unique_ptr<Point>(new Point), const Point& second = *std::unique_ptr<Point>(new Point),
		       	const Velocity& v = *std::unique_ptr<Velocity>(new Velocity), const Vector& direction = *std::unique_ptr<Vector>(new Vector));

	PartOfFunction(const PartOfFunction&) = default;
	PartOfFunction(PartOfFunction&&) = default;
	PartOfFunction& operator=(const PartOfFunction&) = default;
	PartOfFunction& operator=(PartOfFunction&&) = default;

	virtual bool init() const override;
	
	virtual Point operator()(double time) const;

	virtual double max_time() const;

	virtual Vector direction() const;

	virtual ~PartOfFunction() override;

protected:
	Point _begin;
	Point _end;
	Velocity _velocity;
	Vector _direction;

private:
	Vector _direction_f;
	Rotate _rotate;

	double _alpha;
};

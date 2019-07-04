
#pragma once

#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>

//#include "metrics.h"
//#include "../init.h"
#include "metrics.h"
#include "init.h"



class Point : base_init
{
public:
	explicit Point(double x = 0, double y = 0, double z = 0);

	Point(const Point&) = default;
	Point(Point&&) = default;
	Point& operator=(const Point&) = default;
	Point& operator=(Point&&) = default;

	double operator[](std::size_t index) const;

	double x() const;
	double y() const;
	double z() const;

	bool operator==(const Point& point) const;
	bool operator!=(const Point& point) const;

	bool operator==(Point&& point) const;
	bool operator!=(Point&& point) const;
	
	bool check() const;

	friend std::ostream& operator<<(std::ostream& stream, const Point& point);
	friend std::ostream& operator<<(std::ostream& stream, Point&& point);

	static double norm(const Point& first, const Point& second);
	static double norm(Point&& first, const Point& second);
	static double norm(const Point& first, Point&& second);
	static double norm(Point&& first, Point&& second);


protected:
	double _x;
	double _y;
	double _z;
};


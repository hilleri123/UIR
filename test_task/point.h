
#pragma once

#include <functional>
#include <iostream>

#include <cmath>



template <typename scalar, typename degree>
class Point
{
public:
	explicit Point(scalar x = 0, scalar y = 0, scalar z = 0)
		: _x(x), _y(y), _z(z)
	{
		isEuclid = true;
	}

	Point(const Point<scalar, degree>& ) = default;
	Point(Point<scalar, degree>&& ) = default;
	Point<scalar, degree>& operator=(const Point<scalar, degree>& ) = default;
	Point<scalar, degree>& operator=(Point<scalar, degree>&& ) = default;

	~Point() = default;

	scalar& x() const { if (!isEuclid) sync(); isPolar=false; return _x;}
	scalar& y() const { if (!isEuclid) sync(); isPolar=false; return _y;}
	scalar& z() const { if (!isEuclid) sync(); isPolar=false; return _z;}
	scalar& r() const { if (!isPolar) sync(); isEuclid=false; return _r;}
	degree& p() const { if (!isPolar) sync(); isEuclid=false; return _p;}
	degree& q() const { if (!isPolar) sync(); isEuclid=false; return _q;}

	bool operator==(const Point<scalar, degree>& a)  const
	{
		a.sync();
		sync();
		if (a.x()==x() && a.y()==y() && a.z()==z()) {
			return true;
		} else {
			return false;
		}
	}
	bool operator==(Point<scalar, degree>&& a)  const
	{
		a.sync();
		sync();
		if (a.x()==x() && a.y()==y() && a.z()==z()) {
			return true;
		} else {
			return false;
		}
	}
	bool operator!=(const Point<scalar, degree>& a) const { return !(*this == a);} 
	bool operator!=(Point<scalar, degree>&& a) const { return !(*this == a);} 

	Point<scalar, degree>& operator+(const Point<scalar, degree>& a) const
	{
		auto& result = *new Point<scalar, degree>();
		for (int i = 0; i < 3; i++)
			result[i] = this->operator[](i) + a[i];
		return result;
	}

	Point<scalar, degree>& operator+(Point<scalar, degree>&& a) const
	{
		auto& result = *new Point<scalar, degree>();
		for (int i = 0; i < 3; i++)
			result[i] = this->operator[](i) + a[i];
		return result;
	}

	Point<scalar, degree>& operator-(const Point<scalar, degree>& a) const
	{
		auto& result = *new Point<scalar, degree>();
		for (int i = 0; i < 3; i++)
			result[i] = this->operator[](i) - a[i];
		return result;
	}

	Point<scalar, degree>& operator-(Point<scalar, degree>&& a) const
	{
		auto& result = *new Point<scalar, degree>();
		for (int i = 0; i < 3; i++)
			result[i] = this->operator[](i) - a[i];
		return result;
	}

	scalar& operator[](std::size_t i) const
	{
		if (i > 2) {
			throw "out of range";			//!!!!!
		}
		if (!isEuclid) {
			sync();
		}
		isPolar = false;
		if (i == 0) {
			return std::ref(x());
		} else if (i == 1) {
			return std::ref(y());
		} else if (i == 2) {
			return std::ref(z());
		}
	}

	friend std::ostream& operator<<(std::ostream &stream, Point<scalar, degree> a)
	{
		a.sync();
		stream << "[" << a.x() << ", " << a.y() << ", " << a.z() << "] (" << a.r() << ", " << a.q() << ", " << a.p() << ") ";
		return stream;
	}

	static scalar distance(const Point<scalar, degree>& first, const Point<scalar, degree>& second) 
	{
		scalar result = 0;
		for (int i=0; i<3; i++) {
			result += pow((first[i] - second[i]), 2);
		}
		return sqrt(result);
	}
protected:

	void sync()  const
	{
		if (isEuclid || isPolar) {
			if (!isPolar) {
				_r = sqrt(_x*_x + _y*_y + _z*_z);
				if (_x == 0) {
					_p = atan(1) * 2;
				} else {
					_p = atan(_y / _x);
				}
				if (_x < 0) {
					_p += atan(1)*4;      			//pi
				} else if (_y == 0) {
					_p = 0;
				}
				if (_r == 0) {
					_p = 0;
					_q = 0;
				} else {
					_q = asin(_z / _r);
				}
				isPolar = true;
			} else if (!isEuclid) {
				_z = _r * sin(_q);
				_x = _r * cos(_q) * cos(_p);
				_y = _r * cos(_q) * sin(_p);
				isEuclid = true;
			}
		} else {
			throw "sync err";		//!!!!!
		}
	}

	mutable bool isEuclid = false;
	mutable scalar _x;
	mutable scalar _y;
	mutable scalar _z;

	mutable bool isPolar = false;
	mutable scalar _r;
	mutable degree _q;
	mutable degree _p;
};



#pragma once

#include <memory>
#include <cmath>

#include <iostream>

#include "init.h"
#include "point.h"


template <typename scalar>
class Vector : base_init
{
public:
	explicit Vector(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>()), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>()))
	{
		_direction = Point<scalar>(second.x()-first.x(), second.y()-first.y(), second.z()-first.z());
	}

	Vector(const Vector<scalar>& ) = default;
	Vector(Vector<scalar>&& ) = default;
	Vector<scalar>& operator=(const Vector<scalar>& ) = default;
	Vector<scalar>& operator=(Vector<scalar>&& ) = default;
	
	bool operator==(const Vector<scalar>& vector) const { return _direction == vector._direction; }
	bool operator!=(const Vector<scalar>& vector) const { return _direction != vector._direction; }
	bool operator==(Vector<scalar>&& vector) const { return _direction == vector._direction; }
	bool operator!=(Vector<scalar>&& vector) const { return _direction != vector._direction; }
	
	// 			begin  *
	Vector<scalar> operator*(scalar a) const
	{ 
		auto result = Vector<scalar>();	       
		//std::cout << _direction << std::endl;
		result._direction = Point<scalar>(_direction.x() * a, _direction.y() * a, _direction.z() * a);
		//std::cout << result._direction << std::endl;
		return result;
	}
	Vector<scalar> operator*=(scalar a) { this->operator=( this->operator*(a) ); return *this; }
	friend Vector<scalar> operator*(scalar a, const Vector<scalar>& vector) { return vector * a; }
	friend Vector<scalar> operator*(scalar a, Vector<scalar>&& vector) { return vector * a; }

	Vector<scalar> operator*(const Vector<scalar>& vector) const
	{ 
		auto result = Vector<scalar>();
 		auto& a = _direction;		
 		auto& b = vector._direction;		
		result._direction = Point<scalar>( a.y()*b.z() - a.z()*b.y() , a.z()*b.x() - a.x()*b.z() , a.x()*b.y() - a.y()*b.x() );
		return result;
	}
	Vector<scalar> operator*=(const Vector<scalar>& vector) { this->operator=( this->operator*(vector) ); return *this; }

	Vector<scalar> operator*(Vector<scalar>&& vector) const
	{ 
		auto result = Vector<scalar>();
 		auto& a = _direction;		
 		auto& b = vector._direction;		
		result._direction = Point<scalar>( a.y()*b.z() - a.z()*b.y() , a.z()*b.x() - a.x()*b.z() , a.x()*b.y() - a.y()*b.x() );
		return result;
	}
	Vector<scalar> operator*=(Vector<scalar>&& vector) { this->operator=( this->operator*(vector) ); return *this; }
	//		end  *

	//		begin  +
	Vector<scalar> operator+(const Vector<scalar>& vector) const
	{
		auto result = Vector<scalar>();	       
		result._direction = Point<scalar>(_direction.x() + vector._direction.x(), _direction.y() + vector._direction.y(), _direction.z() + vector._direction.z());
		return result;
	}
	Vector<scalar> operator+=(const Vector<scalar>& vector) { this->operator=( this->operator+(vector) ); return *this; }

	Vector<scalar> operator+(Vector<scalar>&& vector) const
	{
		auto result = Vector<scalar>();	       
		result._direction = Point<scalar>(_direction.x() + vector._direction.x(), _direction.y() + vector._direction.y(), _direction.z() + vector._direction.z());
		return result;
	}
	Vector<scalar> operator+=(Vector<scalar>&& vector) { this->operator=( this->operator+(vector) ); return *this; }

	//Point<scalar> operator+(const Point<scalar>& point) const
	//{
		//auto result = Point<scalar>(_direction.x() + point.x(), _direction.y() + point.y(), _direction.z() + point.z());
		//return result;
	//}
	//Point<scalar> operator+(Point<scalar>& point) const
	//{
		//auto result = Point<scalar>(_direction.x() + point.x(), _direction.y() + point.y(), _direction.z() + point.z());
		//return result;
	//}
	friend Point<scalar> operator+(const Vector<scalar>& vector, const Point<scalar>& point)
	{
		auto result = Point<scalar>(vector._direction.x() + point.x(), vector._direction.y() + point.y(), vector._direction.z() + point.z());
		return result;
	}
	friend Point<scalar> operator+(const Vector<scalar>& vector, Point<scalar>&& point)
	{
		auto result = Point<scalar>(vector._direction.x() + point.x(), vector._direction.y() + point.y(), vector._direction.z() + point.z());
		return result;
	}
	friend Point<scalar> operator+(Vector<scalar>&& vector, const Point<scalar>& point)
	{
		auto result = Point<scalar>(vector._direction.x() + point.x(), vector._direction.y() + point.y(), vector._direction.z() + point.z());
		return result;
	}
	friend Point<scalar> operator+(Vector<scalar>&& vector, Point<scalar>&& point)
	{
		auto result = Point<scalar>(vector._direction.x() + point.x(), vector._direction.y() + point.y(), vector._direction.z() + point.z());
		return result;
	}
	//		end +

	//		begin -
	Vector<scalar> operator-(const Vector<scalar>& vector) const
	{
		scalar x = vector._direction.x() - _direction.x();
		scalar y = vector._direction.y() - _direction.y();
		scalar z = vector._direction.z() - _direction.z();
		auto result = Vector<scalar>(Point<scalar>(x, y, z));
		return result;
	}

	Vector<scalar> operator-(Vector<scalar>&& vector) const
	{
		scalar x = vector._direction.x() - _direction.x();
		scalar y = vector._direction.y() - _direction.y();
		scalar z = vector._direction.z() - _direction.z();
		auto result = Vector<scalar>(Point<scalar>(x, y, z));
		return result;
	}

	Vector<scalar> operator-=(const Vector<scalar>& vector) { this->operator=(this->operator-(vector)); return *this; }
	Vector<scalar> operator-=(Vector<scalar>&& vector) { this->operator=(this->operator-(vector)); return *this; }
	//		end-
	//		end-

	//		begin ^
	//template <typename angle>
       	//angle operator^(const Vector<scalar>& vector) const
       	double operator^(const Vector<scalar>& vector) const
	{
		scalar s = _direction.x() * vector._direction.x() + _direction.y() * vector._direction.y() + _direction.z() * vector._direction.z();
		return acos( s / Vector<scalar>::norm(*this) / Vector<scalar>::norm(vector));
	}

	//template <typename angle>
       	//angle operator^(Vector<scalar>&& vector) const
       	double operator^(Vector<scalar>&& vector) const
	{
		scalar s = _direction.x() * vector._direction.x() + _direction.y() * vector._direction.y() + _direction.z() * vector._direction.z();
		return acos( s / Vector<scalar>::norm(*this) / Vector<scalar>::norm(vector));
	}

	double xy_angle(const Vector<scalar>& vector) const
	{
		return Vector<scalar>::angle_in_2d(_direction.x(), _direction.y(), vector._direction.x(), vector._direction.y());
	}

	double xy_angle(Vector<scalar>&& vector) const
	{
		return Vector<scalar>::angle_in_2d(_direction.x(), _direction.y(), vector._direction.x(), vector._direction.y());
	}

	double xz_angle(const Vector<scalar>& vector) const
	{
		return Vector<scalar>::angle_in_2d(_direction.x(), _direction.z(), vector._direction.x(), vector._direction.z());
	}

	double xz_angle(Vector<scalar>&& vector) const
	{
		return Vector<scalar>::angle_in_2d(_direction.x(), _direction.z(), vector._direction.x(), vector._direction.z());
	}

	double yz_angle(const Vector<scalar>& vector) const
	{
		return Vector<scalar>::angle_in_2d(_direction.y(), _direction.z(), vector._direction.y(), vector._direction.z());
	}

	double yz_angle(Vector<scalar>&& vector) const
	{
		return Vector<scalar>::angle_in_2d(_direction.y(), _direction.z(), vector._direction.y(), vector._direction.z());
	}

	//		end^

	//		begin rotate
	//template <typename angle>
	//Vector<scalar>& rotate_x(angle alpha) const
	Vector<scalar> rotate_x(double alpha) const
	{
		scalar x = _direction.x();
		scalar y = _direction.y() * cos(alpha) - _direction.z() * sin(alpha);
		scalar z = _direction.y() * sin(alpha) + _direction.z() * cos(alpha);
		auto result = Vector<scalar>(Point<scalar>(0,0,0), Point<scalar>(x, y, z));
		return result;
	}

	//template <typename angle>
	//Vector<scalar>& rotate_y(angle alpha) const
	Vector<scalar> rotate_y(double alpha) const
	{
		scalar x = _direction.x() * cos(alpha) + _direction.z() * sin(alpha);
		scalar y = _direction.y();
		scalar z = _direction.x() * (-sin(alpha)) + _direction.z() * cos(alpha);
		auto result = Vector<scalar>(Point<scalar>(0,0,0), Point<scalar>(x, y, z));
		return result;
	}

	//template <typename angle>
	//Vector<scalar>& rotate_z(angle alpha) const
	Vector<scalar> rotate_z(double alpha) const
	{
		scalar x = _direction.x() * cos(alpha) - _direction.y() * sin(alpha);
		scalar y = _direction.x() * sin(alpha) + _direction.y() * cos(alpha);
		scalar z = _direction.z();
		auto result = Vector<scalar>(Point<scalar>(0,0,0), Point<scalar>(x, y, z));
		return result;
	}

	Vector<scalar> rotate(const Vector<scalar>& vector, double alpha) const
	{
		scalar norm_first = Vector<scalar>::norm(*this);
		scalar norm_second = Vector<scalar>::norm(vector);
		//scalar k = sin(alpha) / (norm_first * sin(alpha) + norm_second * sin(fabs(this->operator^(vector) - alpha)));
		scalar k = sin(alpha) / (norm_first * sin(alpha) + norm_second * sin(this->operator^(vector) - alpha));
		auto result = ((*this) + (vector - (*this)) * k);
		result = result * (norm_first / Vector<scalar>::norm(result));
		return result;
	}

	Vector<scalar> rotate(Vector<scalar>&& vector, double alpha) const
	{
		scalar norm_first = Vector<scalar>::norm(*this);
		scalar norm_second = Vector<scalar>::norm(vector);
		//scalar k = sin(alpha) / (norm_first * sin(alpha) + norm_second * sin(fabs(this->operator^(vector) - alpha)));
		scalar k = sin(alpha) / (norm_first * sin(alpha) + norm_second * sin(this->operator^(vector) - alpha));
		auto result = ((*this) + (vector - (*this)) * k);
		result = result * (norm_first / Vector<scalar>::norm(result));
		return result;
	}

	//		end rotate
	
	Vector<scalar> projection(const Vector<scalar>& plane) const
	{
		auto angle = this->operator^(plane);
		auto& vector = *new Vector<scalar>(plane);
		if (angle < atan(1)*2) {
			vector *= -1;
		}
		return this->operator+(vector * sin(angle) * (Vector<scalar>::norm(*this) / Vector<scalar>::norm(vector)));
	}

	Vector<scalar> projection(Vector<scalar>&& plane) const
	{
		auto angle = this->operator^(plane);
		auto& vector = *new Vector<scalar>(plane);
		if (angle < atan(1)*2) {
			vector *= -1;
		}
		return this->operator+(vector * sin(angle) * (Vector<scalar>::norm(*this) / Vector<scalar>::norm(vector)));
	}


	static scalar norm(const Vector<scalar>& vector) { return Point<scalar>::norm(Point<scalar>(0,0,0), vector._direction); }
	static scalar norm(Vector<scalar>&& vector) { return Point<scalar>::norm(Point<scalar>(0,0,0), vector._direction); }

	virtual ~Vector()
	{}

protected:
	static double angle_in_2d(scalar x0, scalar y0, scalar x1, scalar y1) 
	{
		double a0 = atan(y0 / x0);
		double a1 = atan(y1 / x1);
		if (x0 < 0) {
			a0 += atan(1)*2;
		}
		if (x1 < 0) {
			a1 += atan(1)*2;
		}
		return a1 - a0;
	}

	//Point<scalar>& _direction = *new Point<scalar>();
	Point<scalar> _direction;
};

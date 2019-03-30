

#pragma once

#include <memory>
#include <cmath>

#include <iostream>

#include "point.h"


template <typename scalar>
class Vector : base_init
{
public:
	explicit Vector(const Point<scalar>& first = *std::unique_ptr<Point<scalar>>(new Point<scalar>()), const Point<scalar>& second = *std::unique_ptr<Point<scalar>>(new Point<scalar>()))
	{
		//for (std::size_t i = 0; i < 3; i++) {
			//_direction[i] = second[i] - first[i];
		//}
		_direction = Point<scalar>(second.x()-first.x(), second.y()-first.y(), second.z()-first.z());
	}
	Vector(const Point<scalar>& direction) 
		: _direction(direction)
	{}

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

	Point<scalar> operator+(const Point<scalar>& point) const
	{
		auto result = Point<scalar>(_direction.x() + point.x(), _direction.y() + point.y(), _direction.z() + point.z());
		return result;
	}
	Point<scalar> operator+(Point<scalar>& point) const
	{
		auto result = Point<scalar>(_direction.x() + point.x(), _direction.y() + point.y(), _direction.z() + point.z());
		return result;
	}
	//friend Point<scalar> operator+(const Vector<scalar>& vector, const Point<scalar>& point) { return vector + point; }
	//friend Point<scalar> operator+(const Vector<scalar>& vector, Point<scalar>&& point) { return vector + point; }
	friend Point<scalar> operator+(Vector<scalar>&& vector, const Point<scalar>& point) { return vector + point; }
	friend Point<scalar> operator+(Vector<scalar>&& vector, Point<scalar>&& point) { return vector + point; }
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
		scalar s = _direction.x() * vector._direction.x() + _direction.y() * vector._directon.y() + _direction.z() * vector._direction.z();
		return acos( s / Vector<scalar>::norm(*this) / Vector<scalar>::norm(vector));
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
		auto result = Vector<scalar>(point(Point<scalar>(x, y, z)));
		return result;
	}

	//template <typename angle>
	//Vector<scalar>& rotate_y(angle alpha) const
	Vector<scalar> rotate_y(double alpha) const
	{
		scalar x = _direction.x() * cos(alpha) + _direction.z() * sin(alpha);
		scalar y = _direction.y();
		scalar z = _direction.x() * (-sin(alpha)) + _direction.z() * cos(alpha);
		auto result = Vector<scalar>(point(Point<scalar>(x, y, z)));
		return result;
	}

	//template <typename angle>
	//Vector<scalar>& rotate_z(angle alpha) const
	Vector<scalar> rotate_z(double alpha) const
	{
		scalar x = _direction.x() * cos(alpha) - _direction.y() * sin(alpha);
		scalar y = _direction.x() * sin(alpha) + _direction.y() * cos(alpha);
		scalar z = _direction.z();
		auto result = Vector<scalar>(point(Point<scalar>(x, y, z)));
		return result;
	}

	//		end rotate
	
	Vector<scalar> projection(const Vector<scalar>& plane) const
	{
		auto angle = this->operator^(plane);
		auto& vector = *new Vector<scalar>(plane);
		if (plane < atan(1)*2) {
			vector *= -1;
		}
		return this->operator+(vector * sin(angle) * (Vector<scalar>::norm(*this) / Vector<scalar>::norm(vector)));
	}

	Vector<scalar> projection(Vector<scalar>&& plane) const
	{
		auto angle = this->operator^(plane);
		auto& vector = *new Vector<scalar>(plane);
		if (plane < atan(1)*2) {
			vector *= -1;
		}
		return this->operator+(vector * sin(angle) * (Vector<scalar>::norm(*this) / Vector<scalar>::norm(vector)));
	}


	static scalar norm(const Vector<scalar>& vector) { return Point<scalar>::norm(Point<scalar>(0,0,0), vector._direction); }
	static scalar norm(Vector<scalar>&& vector) { return Point<scalar>::norm(Point<scalar>(0,0,0), vector._direction); }

protected:

	//Point<scalar>& _direction = *new Point<scalar>();
	Point<scalar> _direction;
};

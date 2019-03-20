

#pragma once

#include <memory>

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
	Vector<scalar>& operator*(scalar a) const
	{ 
		auto& result = *new Vector<scalar>();	       
		//std::cout << _direction << std::endl;
		result._direction = Point<scalar>(_direction.x() * a, _direction.y() * a, _direction.z() * a);
		//std::cout << result._direction << std::endl;
		return result;
	}
	Vector<scalar>& operator*=(scalar a) { this->operator=( this->operator*(a) ); return *this; }
	friend Vector<scalar>& operator*(scalar a, const Vector<scalar>& vector) { return vector * a; }
	friend Vector<scalar>& operator*(scalar a, Vector<scalar>&& vector) { return vector * a; }

	Vector<scalar>& operator*(const Vector<scalar>& vector) const
	{ 
		auto& result = *new Vector<scalar>();
 		auto& a = _direction;		
 		auto& b = vector._direction;		
		result._direction = Point<scalar>( a.y()*b.z() - a.z()*b.y() , a.z()*b.x() - a.x()*b.z() , a.x()*b.y() - a.y()*b.x() );
		return result;
	}
	Vector<scalar>& operator*=(const Vector<scalar>& vector) { this->operator=( this->operator*(vector) ); return *this; }

	Vector<scalar>& operator*(Vector<scalar>&& vector) const
	{ 
		auto& result = *new Vector<scalar>();
 		auto& a = _direction;		
 		auto& b = vector._direction;		
		result._direction = Point<scalar>( a.y()*b.z() - a.z()*b.y() , a.z()*b.x() - a.x()*b.z() , a.x()*b.y() - a.y()*b.x() );
		return result;
	}
	Vector<scalar>& operator*=(Vector<scalar>&& vector) { this->operator=( this->operator*(vector) ); return *this; }
	//		end  *

	//		begin  +
	Vector<scalar>& operator+(const Vector<scalar>& vector) const
	{
		auto& result = *new Vector<scalar>();	       
		result._direction = Point<scalar>(_direction.x() + vector._direction.x(), _direction.y() + vector._direction.y(), _direction.z() + vector._direction.z());
		return result;
	}
	Vector<scalar>& operator+=(const Vector<scalar>& vector) { this->operator=( this->operator+(vector) ); return *this; }

	Vector<scalar>& operator+(Vector<scalar>&& vector) const
	{
		auto& result = *new Vector<scalar>();	       
		result._direction = Point<scalar>(_direction.x() + vector._direction.x(), _direction.y() + vector._direction.y(), _direction.z() + vector._direction.z());
		return result;
	}
	Vector<scalar>& operator+=(Vector<scalar>&& vector) { this->operator=( this->operator+(vector) ); return *this; }

	Point<scalar>& operator+(const Point<scalar>& point) const
	{
		auto& result = *new Point<scalar>(_direction.x() + point.x(), _direction.y() + point.y(), _direction.z() + point.z());
		return result;
	}
	Point<scalar>& operator+(Point<scalar>& point) const
	{
		auto& result = *new Point<scalar>(_direction.x() + point.x(), _direction.y() + point.y(), _direction.z() + point.z());
		return result;
	}
	friend Point<scalar>& operator+(const Vector<scalar>& vector, const Point<scalar>& point) { return vector + point; }
	friend Point<scalar>& operator+(const Vector<scalar>& vector, Point<scalar>&& point) { return vector + point; }
	friend Point<scalar>& operator+(Vector<scalar>&& vector, const Point<scalar>& point) { return vector + point; }
	friend Point<scalar>& operator+(Vector<scalar>&& vector, Point<scalar>&& point) { return vector + point; }
	//		end +

protected:
	//Point<scalar>& _direction = *new Point<scalar>();
	Point<scalar> _direction;
};


#include "part_of_function.h"

PartOfFunction::PartOfFunction(const Point& first, const Point& second, const Velocity& v, const Vector& direction)
	: _begin(first), _end(second), _velocity(v), _direction(direction)
{
	Vector delta = direction.rotate(Vector(Point(0,0,0), second), 2*atan(1));
	//double R = v.v() / v.max_rotate();
	Vector OA = Vector(Point(0,0,0), first);
	//double alpha = asin(R / Vector::norm(OA));
	double alpha = asin(v.v() / v.max_rotate() / Vector::norm(OA));
	Point Q = Point(0,0,0) + OA.rotate(delta, alpha);


	// n = (A, B, C) = Vector(Point(0,0,0), first)
	//double D = -(first.radius() * first.radius()); 	// Ax+By+Cz+D=0 A*A+B*B+C*C=R*R => D=-R*R
	double D = -(Q.radius() * Q.radius()); 	// Ax+By+Cz+D=0 A*A+B*B+C*C=R*R => D=-R*R
	double dr = first.x() * second.x() + first.y() * second.y() + first.z() * second.z() + D;	// Ax+By+Cz+D=dr
	if (copysign(1, D) == copysign(1, dr)) {	// on same side ( (0,0,0) and second) 
	} else {
	}

	//Point F = Point(0,0,0) + Vector(Point(0,0,0), second) * (-D / (first.x() * second.x() + first.y() * second.y() + first.z() * second.z()));	// Ax+By+Cz+D & (O, second) = F
	Point F = Point(0,0,0) + Vector(Point(0,0,0), second) * (-D / (Q.x() * second.x() + Q.y() * second.y() + Q.z() * second.z()));	// Ax+By+Cz+D & (O, second) = F
	//Point new_second = first + Vector(Point(0,0,0), F);		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	_rotate = Rotate(first, F, v, direction);
	//if (v == 0) {
		//throw ;
	//}
	//std::cout << "first = " << first << " second = " << second << std::endl;
	//_direction_f = Vector(first, second);
	//_rotate = Rotate<double, double, t>(first, second, v, direction);
	//std::cout << "velocity " << v.v() << ", " << v.max_rotate() << std::endl;
	_direction_f = Vector(_rotate.end_point(), second);
	if (equal(Vector::norm(_direction_f), 0)) {
		_direction_f = _rotate.direction();
		if (equal(Vector::norm(_direction_f), 0)) {
			_direction_f = direction;
		}
	}
}

	
bool PartOfFunction::init() const
{
	if (_begin == _end || _velocity == 0 || !_rotate.init()) {
		//std::cout << "pof init" << std::endl;
		return false;
	} else {
		return true;
	}
}

Point PartOfFunction::operator()(double time) const
{
	if (time > max_time()) {
		return _end;
	} else if (time < 0) {
		return _begin;
	}
	if (time < _rotate.max_time()) {
		return _rotate(time);
	} else {
		time -= _rotate.max_time();
	}
	//std::cout << "line " << time << std::endl;

	//assert(equal(_rotate.end_point().radius(), _end.radius()));

	Vector first(Point(0,0,0), _rotate.end_point());
	Vector second(Point(0,0,0), _end);
	//double part = (time - _rotate.max_time()) * (_velocity / Point::norm(_rotate.end_point(), _end));
	//std::cout << "part " << part << std::endl;
	//auto&& vector = _direction_f * part;

	//!!!!!!!!!!!!!!!! mb rotation err

	auto&& vector = first.rotate(second, time / max_time() * (second^first));

	return vector + Point(0,0,0);
}

double PartOfFunction::max_time() const
{
	//auto a = _rotate.end_point();
	//std::cout << "!" << (Point::norm(a, _end) / _double) << std::endl;
	//std::cout << "max time " << static_cast<t>(Point::norm(a, _end) / _double) << " between " << a.x() << " " << a.y() << " " << a.z() << " and " << _end.x() << " " << _end.y() << " " << _end.z() << std::endl;
	return (Point::norm(_rotate.end_point(), _end) / _velocity) + _rotate.max_time();
}

Vector PartOfFunction::direction() const
{
	return _direction_f;
}

PartOfFunction::~PartOfFunction()
{}


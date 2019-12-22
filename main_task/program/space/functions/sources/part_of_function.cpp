
#include "part_of_function.h"

PartOfFunction::PartOfFunction(const Point& first, const Point& m_second, const Velocity& v, const Vector& direction)
	: _begin(first), _end(m_second), _velocity(v), _direction(direction)
{
	Point C(0,0,0);	//Центр Земли

	double l = Vector(O, _begin)^Vector(O, _end)*(Point::norm(O, _begin));

	Matrix trans;

#if 0
	Point second = m_second;
	std::cout << "!!!!! first " << first << " second " << second << " dir " << (Point()+direction) << std::endl; 

	double h = m_second.radius()-first.radius();
	second.by_geo(first.radius(), second.latitude(), second.longitude());

	Vector&& fv = Vector(Point(), first);
	Vector&& sv = Vector(Point(), second);

	Vector&& sv_projection = sv - fv * cos(fv^sv);

	std::cout << "sv_projection " << (sv_projection + Point()) << std::endl;

	if (!equal(abs(cos(sv_projection^direction)), 1)) {
		Vector delta = direction.rotate(sv_projection, 2*atan(1));
		double alpha = asin(v.v() / v.max_rotate() / Vector::norm(fv));
		Vector&& norm_Q = fv.rotate(delta, alpha); 	// rotation plane's norm
		Point Q = Point() + norm_Q * cos(norm_Q^fv);

		std::cout << "Q " << Q << " radius " << Q.radius() << std::endl;

		double D = -(Q.radius() * Q.radius()); 	// Ax+By+Cz+D=0 A*A+B*B+C*C=R*R => D=-R*R
		double dr = first.x() * second.x() + first.y() * second.y() + first.z() * second.z() + D;	// Ax+By+Cz+D=dr
		if (copysign(1, D) == copysign(1, dr)) {	// on same side ( (0,0,0) and second) 
		} else {
		}

		Point F = Point() + sv * (-D / (Q.x() * second.x() + Q.y() * second.y() + Q.z() * second.z())); 	// Ax+By+Cz+D & (O, second) = F
		F = Q + Vector(Q, F) * (copysign(1, cos(fv^sv)));	// new F 


		std::cout << "F " << F << " second " << second << std::endl;

		_rotate = Rotate(first, F, v, direction);
	} else {
		_rotate = Rotate(first, first, v, direction);
	}
	std::cout << "^ " << (Vector(Point(), _rotate.end_point())^Vector(Point(), second)) << std::endl;
	_alpha = v.v() * log(fabs(1 + h / first.radius())) / ((Vector(Point(), _rotate.end_point())^Vector(Point(), second)) * first.radius());

	std::cout << "alpha " << _alpha << std::endl;
	std::cout << "R first " << first.radius() << " rotate " << _rotate.end_point().radius() << " second " << second.radius() << std::endl;
	_direction_f = sv.rotate(Vector(Point(), _rotate.end_point()), -2*atan(1));
#endif
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

	Vector first(Point(), _rotate.end_point());
	Vector second(Point(), _end);
	//double part = (time - _rotate.max_time()) * (_velocity / Point::norm(_rotate.end_point(), _end));
	//std::cout << "part " << part << std::endl;
	//auto&& vector = _direction_f * part;

	//!!!!!!!!!!!!!!!! mb rotation err

	//auto&& vector = first.rotate(second, time / (max_time() - _rotate.max_time()) * (second^first)) * (1 + _alpha * time);
	auto&& vector = first.rotate(second, _velocity / _alpha / Vector::norm(first) * log(fabs(1 + _alpha*time)) ) * (1 + _alpha * time);
	//std::cout << "or " << (second^first) << " " << (_velocity / _alpha / Vector::norm(first) * log(fabs(1 + _alpha*max_time()))) << std::endl;
	//std::cout << "R " << (Vector::norm(first) * abs(_alpha*max_time())) << " r " << Vector::norm(second) << std::endl;
	//std::cout << "R " << Vector::norm(first) << " a " << _alpha << " m_t " << max_time() << std::endl;
	//std::cout << "v(" << _velocity.v() << ")/a(" <<  _alpha << ")/r(" << Vector::norm(first) << ")*log(" << log(abs(1 + _alpha*time)) << ")" << std::endl;
	//std::cout << "log = 1 + (" << (_alpha*time) << ")" << std::endl;
	//std::cout << "% " << (_velocity / _alpha / Vector::norm(first) * log(abs(1 + _alpha*time))) << " " << (time/(max_time() - _rotate.max_time()*(second^first))) << std::endl;
	//std::cout << "f " << (Vector::norm(first) * _alpha * time) << std::endl;

	return vector + Point();
}

double PartOfFunction::max_time() const
{
	//auto a = _rotate.end_point();
	//std::cout << "!" << (Point::norm(a, _end) / _double) << std::endl;
	//std::cout << "max time " << static_cast<t>(Point::norm(a, _end) / _double) << " between " << a.x() << " " << a.y() << " " << a.z() << " and " << _end.x() << " " << _end.y() << " " << _end.z() << std::endl;
	//return (Point::norm(_rotate.end_point(), _end) / _velocity) + _rotate.max_time();
	Vector&& ev = Vector(Point(), _rotate.end_point()); 
	Vector&& sv = Vector(Point(), _end);
	//std::cout << "re " << _rotate.end_point() << " s " << _end << " r " << _rotate.end_point().radius() << " " << _end.radius() << std::endl;
	//assert(equal(Vector::norm(ev), Vector::norm(sv)));
	//return ((Vector::norm(ev)*(ev^sv)) / _velocity) + _rotate.max_time();
	//std::cout << "T " <<((_end.radius() - _rotate.end_point().radius()) / _alpha / _rotate.end_point().radius()) << " " << _rotate.max_time() << std::endl;
	return ((_end.radius() - _rotate.end_point().radius()) / _alpha / _rotate.end_point().radius()) + _rotate.max_time();
}

Vector PartOfFunction::direction() const
{
	return _direction_f;
}

PartOfFunction::~PartOfFunction()
{}


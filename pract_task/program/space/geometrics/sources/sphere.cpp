

#include "sphere.h"

Sphere::Sphere(Point center, Point plane, double dir)
	: _center(center), _radius(Point::norm(center, plane)), _direction(dir)
{
	double x = plane.x() - center.x();
	double y = plane.y() - center.y();
	double z = plane.z() - center.z();
	_latitude = atan(z / sqrt(x*x+y*y));
	_longitude = atan(x / y);
	if (less(x, 0)) {
		_longitude += 4*atan(1);
	}
}

Sphere::Sphere(Point center, double r, double dir, double lat, double lon)
	: _center(center), _radius(r), _direction(dir), _latitude(lat), _longitude(lon)
{}

bool Sphere::init() const
{
	return _radius > 0;
}

Sphere Sphere::new_sphere(Point next) const
{
	Vector r = Vector(plane(), next);
	double d = Vector::norm(r) / (2 * cos(r^(Vector(plane(), _center)))) - _radius;
	//return new_sphere(d);
	std::cout << "r :" << _radius << " d :" << d << std::endl;
	auto s = new_sphere(d);
	std::cout << "r :" << s._radius << " n :" << Point::norm(s._center, next) << std::endl;
	std::cout << "Delta :" << Point::norm(s.plane(), plane()) << std::endl;
	return s;
}

Sphere Sphere::new_sphere(double dr) const
{
	double x = _center.x() - dr * cos(_longitude) * cos(_latitude);
	double y = _center.y() - dr * sin(_longitude) * cos(_latitude);
	double z = _center.z() - dr * sin(_latitude);
	return Sphere(Point(x, y, z), _radius + dr, _direction, _latitude, _longitude);
}

Point Sphere::plane() const
{
	double x = _center.x() + _radius * cos(_longitude) * cos(_latitude);
	double y = _center.y() + _radius * sin(_longitude) * cos(_latitude);
	double z = _center.z() + _radius * sin(_latitude);
	return Point(x, y, z);
}

Point Sphere::center() const
{
	return _center;
}

double Sphere::radius() const
{
	return _radius;
}

double Sphere::direction() const
{
	return _direction;
}

double Sphere::latitude() const
{
	return _latitude;
}

double Sphere::longitude() const
{
	return _longitude;
}

bool Sphere::check() const
{
	return !((_radius!=_radius)||(_direction!=_direction)||(_latitude!=_latitude)||(_longitude!=_longitude)) && _center.check();
}

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere)
{
	std::cout << "new sphere : " << sphere._center << " " << sphere._radius << " " << sphere._direction << " " << sphere._latitude << " " << sphere._longitude << std::endl;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, Sphere&& sphere)
{
	std::cout << "new sphere : " << sphere._center << " " << sphere._radius << " " << sphere._direction << " " << sphere._latitude << " " << sphere._longitude << std::endl;
	return stream;
}

Sphere::~Sphere()
{}

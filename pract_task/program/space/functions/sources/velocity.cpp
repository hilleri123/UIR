
#include "velocity.h"

Velocity::Velocity(double velocity, double max_rotate)
	: _velocity(velocity), _max_rotate(max_rotate)
{}
	
Velocity& Velocity::operator=(double velocity) { _velocity = velocity; return *this; }

bool Velocity::init() const
{
	if (_velocity == 0 || _max_rotate == 0) {	//!!!
		return false;
	} else {
		return true;
	}
}

double Velocity::max_rotate() const { return _max_rotate; }
double Velocity::v() const { return _velocity; }

bool Velocity::operator==(double a) const {return v() == a; }
bool operator==(double a, const Velocity& v) {return v.v() == a; }
bool operator==(double a, Velocity&& v) {return v.v() == a; }
bool Velocity::operator!=(double a) const {return v() != a; }
bool operator!=(double a, const Velocity& v) {return v.v() != a; }
bool operator!=(double a, Velocity&& v) {return v.v() != a; }
bool Velocity::operator>=(double a) const {return v() >= a; }
bool operator>=(double a, const Velocity& v) {return v.v() >= a; }
bool operator>=(double a, Velocity&& v) {return v.v() >= a; }
bool Velocity::operator<=(double a) const {return v() <= a; }
bool operator<=(double a, const Velocity& v) {return v.v() <= a; }
bool operator<=(double a, Velocity&& v) {return v.v() <= a; }
bool Velocity::operator<(double a) const {return v() < a; }
bool operator<(double a, const Velocity& v) {return v.v() < a; }
bool operator<(double a, Velocity&& v) {return v.v() < a; }
bool Velocity::operator>(double a) const {return v() > a; }
bool operator>(double a, const Velocity& v) {return v.v() > a; }
bool operator>(double a, Velocity&& v) {return v.v() > a; }

bool Velocity::operator==(const Velocity& a) const {return v() == a.v(); }
bool operator==(const Velocity& a, const Velocity& v) {return v.v() == a.v(); }
bool operator==(Velocity&& a, Velocity&& v) {return v.v() == a.v(); }
bool Velocity::operator!=(const Velocity& a) const {return v() != a.v(); }
bool operator!=(const Velocity& a, const Velocity& v) {return v.v() != a.v(); }
bool operator!=(Velocity&& a, Velocity&& v) {return v.v() != a.v(); }
bool Velocity::operator>=(const Velocity& a) const {return v() >= a.v(); }
bool operator>=(const Velocity& a, const Velocity& v) {return v.v() >= a.v(); }
bool operator>=(Velocity&& a, Velocity&& v) {return v.v() >= a.v(); }
bool Velocity::operator<=(const Velocity& a) const {return v() <= a.v(); }
bool operator<=(const Velocity& a, const Velocity& v) {return v.v() <= a.v(); }
bool operator<=(Velocity&& a, Velocity&& v) {return v.v() <= a.v(); }
bool Velocity::operator<(const Velocity& a) const {return v() < a.v(); }
bool operator<(const Velocity& a, const Velocity& v) {return v.v() < a.v(); }
bool operator<(Velocity&& a, Velocity&& v) {return v.v() < a.v(); }
bool Velocity::operator>(const Velocity& a) const {return v() > a.v(); }
bool operator>(const Velocity& a, const Velocity& v) {return v.v() > a.v(); }
bool operator>(Velocity&& a, Velocity&& v) {return v.v() > a.v(); }

double Velocity::operator+(double a) const { return v() + a; }
double operator+(double a, const Velocity& b) { return a + b; }
double operator+(double a, Velocity&& b) { return a + b; }
double Velocity::operator-(double a) const { return v() - a; }
double operator-(double a, const Velocity& b) { return a - b._velocity; }
double operator-(double a, Velocity&& b) { return a - b._velocity; }
double Velocity::operator*(double a) const { return v() * a; }
double operator*(double a, const Velocity& b) { return a * b; }
double operator*(double a, Velocity&& b) { return a * b; }
double Velocity::operator/(double a) const { return v() / a; }
double operator/(double a, const Velocity& b) { return a / b._velocity; }
double operator/(double a, Velocity&& b) { return a / b._velocity; }

Velocity::~Velocity()
{}


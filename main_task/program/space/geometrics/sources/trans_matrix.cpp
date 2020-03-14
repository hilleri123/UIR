
#include "trans_matrix.h"



Matrix::Matrix(matrix opt, const Vector* vec, double angle)
	: _matrix(std::valarray<double>(0., 4*4))
{
	for (std::size_t i = 0; i < 4; i++)
		_matrix[i+i*4] = 1;

	switch (opt) {
	case null:
		break;
	case move:
		if (vec == nullptr) {
			err = new std::invalid_argument("in Matrix constructor vec_ptr == nullptr");
			break;
		}
		_matrix[4-1] = vec->x();
		_matrix[2*4-1] = vec->y();
		_matrix[3*4-1] = vec->z();
		break;
	case rotate:
		if (vec == nullptr) {
			err = new std::invalid_argument("in Matrix constructor vec_ptr == nullptr");
			break;
		}
		{
		double& x0 = _matrix[0];            double& x1 = _matrix[1];            double& x2 = _matrix[2];
		double& y0 = _matrix[0+4];          double& y1 = _matrix[1+4];          double& y2 = _matrix[2+4];
		double& z0 = _matrix[0+2*4];        double& z1 = _matrix[1+2*4];        double& z2 = _matrix[2+2*4];

		double norm = Vector::norm(*vec);
		double l = vec->x() / norm;	double m = vec->y() / norm;	double n = vec->z() / norm;
	
		//std::cout << "Point (" << l << " " << m << " " << n << ")" << std::endl;

		double cosA = cos(angle);
		double sinA = sin(angle);
		//en.wikipedia.org/wiki/Transformation_matrix
		x0 = l*l*(1-cosA)+cosA;         x1 = m*l*(1-cosA)-n*sinA;       x2 = n*l*(1-cosA)+m*sinA;
		y0 = l*m*(1-cosA)+n*sinA;       y1 = m*m*(1-cosA)+cosA;         y2 = n*m*(1-cosA)-l*sinA;
		z0 = l*n*(1-cosA)-m*sinA;       z1 = m*n*(1-cosA)+l*sinA;       z2 = n*n*(1-cosA)+cosA;
		//std::cout << "[ " << x0 << " " << x1 << " " << x2 << " ]" << std::endl;
		//std::cout << "[ " << y0 << " " << y1 << " " << y2 << " ]" << std::endl;
		//std::cout << "[ " << z0 << " " << z1 << " " << z2 << " ]" << std::endl;
		}
		break;
	case comp:
		if (vec == nullptr) {
			err = new std::invalid_argument("in Matrix constructor vec_ptr == nullptr");
			break;
		}
		{
		int last_line = 4*(4-1);
		_matrix[last_line] = vec->x();
		_matrix[last_line+1] = vec->y();
		_matrix[last_line+2] = vec->z();
		}
		break;
	default:
		err = new std::logic_error("in Matrix constructor 'switch case' in default section");
		break;
	}
}

	
bool Matrix::init() const
{
	if (err == nullptr)
		return true;
	else {
		//std::exception tmp(*err);
		//delete err;
		//err = nullptr;
		//throw tmp;
		throw *err;
	}
}


bool Matrix::operator==(const Matrix& m) const
{
	if (4 != 4)
		throw std::invalid_argument("multiply matrix with different dimensions");
	for (std::size_t i = 0; i < 4; i++) {
		if (!equal(_matrix[i], m._matrix[i]))
			return false;
	}
	return true;
}

bool Matrix::operator!=(const Matrix& m) const
{
	return !(*this == m);
}

bool Matrix::operator==(Matrix&& m) const
{
	if (4 != 4)
		throw std::invalid_argument("multiply matrix with different dimensions");
	for (std::size_t i = 0; i < 4; i++) {
		if (!equal(_matrix[i], m._matrix[i]))
			return false;
	}
	return true;
}

bool Matrix::operator!=(Matrix&& m) const
{
	return !(*this == m);
}



Matrix& Matrix::operator*=(const Matrix& m)
{
	this->operator=(*this * m);
	return *this;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	if (m1.size() != m2.size())
		throw std::invalid_argument("multiply matrix with different dimensions");
	Matrix res;
	for (std::size_t i = 0; i < m1.size(); i++) {
		std::slice row(i*m1.size(), m1.size(), 1);
		for (std::size_t j = 0; j < m1.size(); j++) {
			std::slice col(j, m1.size(), m1.size());
			res._matrix[j + i*m1.size()] = (m1._matrix[ row ] * m2._matrix[ col ]).sum(); 
		}
	}
	return res;
}

Point Matrix::operator()(Point point) const
{
	if (4 != 4)
		throw std::invalid_argument("point and matrix have different dimensions");
	std::valarray<double> vec = {point.x(), point.y(), point.z(), 1.};
	//double s = (_matrix[ std::slice(3*4, 4, 1) ] * vec).sum(); 
	//if (equal(s, 1))
		//throw ;

	double x = (_matrix[ std::slice(0, 4, 1) ] * vec).sum(); 
	double y = (_matrix[ std::slice(4, 4, 1) ] * vec).sum(); 
	double z = (_matrix[ std::slice(2*4, 4, 1) ] * vec).sum(); 
	return Point(x, y, z);
}

Vector Matrix::operator()(Vector vector) const
{
	if (4 != 4)
		throw std::invalid_argument("vector and matrix have different dimensions");
	//std::valarray<double> vec = {vector.x(), vector.y(), vector.z(), 1.};
	//double s = (_matrix[ std::slice(3*4, 4, 1) ] * vec).sum(); 
	//if (equal(s, 1))
		//throw ;

	//double x = (_matrix[ std::slice(0, 4, 1) ] * vec).sum(); 
	//double y = (_matrix[ std::slice(4, 4, 1) ] * vec).sum(); 
	//double z = (_matrix[ std::slice(2*4, 4, 1) ] * vec).sum(); 
	//return Vector(Point(0,0,0), Point(x, y, z));

	Point begin = this->operator()(Point(0,0,0));
	Point end = this->operator()(Point(vector.x(), vector.y(), vector.z()));

	return Vector(begin, end);
}


#if 0
Matrix Matrix::rotate(const Vector& vec, double a)
{
	Matrix res;
	double& x0 = res._matrix[0];                    double& x1 = res._matrix[1];                    double& x2 = res._matrix[2];
	double& y0 = res._matrix[0+4];          double& y1 = res._matrix[1+4];          double& y2 = res._matrix[2+4];
	double& z0 = res._matrix[0+2*4];        double& z1 = res._matrix[1+2*4];        double& z2 = res._matrix[2+2*4];

	double norm = Vector::norm(vec);
	double l = vec.x() / norm;	double m = vec.y() / norm;	double n = vec.z() / norm;
	
	//std::cout << "Point (" << l << " " << m << " " << n << ")" << std::endl;

	double cosA = cos(a);
	double sinA = sin(a);
	//en.wikipedia.org/wiki/Transformation_matrix
	x0 = l*l*(1-cosA)+cosA;         x1 = m*l*(1-cosA)-n*sinA;       x2 = n*l*(1-cosA)+m*sinA;
	y0 = l*m*(1-cosA)+n*sinA;       y1 = m*m*(1-cosA)+cosA;         y2 = n*m*(1-cosA)-l*sinA;
	z0 = l*n*(1-cosA)-m*sinA;       z1 = m*n*(1-cosA)+l*sinA;       z2 = n*n*(1-cosA)+cosA;
	//std::cout << "[ " << x0 << " " << x1 << " " << x2 << " ]" << std::endl;
	//std::cout << "[ " << y0 << " " << y1 << " " << y2 << " ]" << std::endl;
	//std::cout << "[ " << z0 << " " << z1 << " " << z2 << " ]" << std::endl;

	return res;
}

Matrix Matrix::rotate(Vector&& vec, double a)
{
	Matrix res;
	double& x0 = res._matrix[0];                    double& x1 = res._matrix[1];                    double& x2 = res._matrix[2];
	double& y0 = res._matrix[0+4];          double& y1 = res._matrix[1+4];          double& y2 = res._matrix[2+4];
	double& z0 = res._matrix[0+2*4];        double& z1 = res._matrix[1+2*4];        double& z2 = res._matrix[2+2*4];

	double norm = Vector::norm(vec);
	double l = vec.x() / norm;	double m = vec.y() / norm;	double n = vec.z() / norm;
	
	double cosA = cos(a);
	double sinA = sin(a);
	//en.wikipedia.org/wiki/Transformation_matrix
	x0 = l*l*(1-cosA)+cosA;         x1 = m*l*(1-cosA)-n*sinA;       x2 = n*l*(1-cosA)+m*sinA;
	y0 = l*m*(1-cosA)+n*sinA;       y1 = m*m*(1-cosA)+cosA;         y2 = n*m*(1-cosA)-l*sinA;
	z0 = l*n*(1-cosA)-m*sinA;       z1 = m*n*(1-cosA)+l*sinA;       z2 = n*n*(1-cosA)+cosA;

	return res;
}


Matrix Matrix::move(const Vector& vec)
{
	Matrix res;

	res._matrix[4-1] = vec.x();
	res._matrix[2*4-1] = vec.y();
	res._matrix[3*4-1] = vec.z();

	return res;
}

Matrix Matrix::move(Vector&& vec)
{
	Matrix res;

	res._matrix[4-1] = vec.x();
	res._matrix[2*4-1] = vec.y();
	res._matrix[3*4-1] = vec.z();

	return res;
}

Matrix Matrix::compression(const Vector& vec)
{
	Matrix res;

	int last_line = 4*(4-1);
	res._matrix[last_line] = vec.x();
	res._matrix[last_line+1] = vec.y();
	res._matrix[last_line+2] = vec.z();

	return res;
}
#endif


std::size_t Matrix::size() const { return 4; }

#if 0
Matrix&& Matrix::transform(const Matrix& matrixs...)
{
	va_list args;
	va_start(args, matrixs);
	Matrix res = va_arg(args, Matrix);
	for (std::size_t i = 1; i < matrixs; i++)
		res *= va_arg(args, Matrix);
	va_end(args);

	return res;
}
#endif

bool Matrix::multiplay_foreward_backward(Matrix& foreward, Matrix& backward, matrix opt, const Vector* vec_ptr, double angle)
{
	Matrix foreward_copy = foreward;
	Matrix* tmp;
	INIT(tmp, Matrix, opt, vec_ptr, angle);
	if (tmp == nullptr)
		return false;
	foreward *= *tmp;
	delete tmp;
	if (vec_ptr != nullptr) {
		Vector tmp_vec = *vec_ptr * (-1);
		INIT(tmp, Matrix, opt, &tmp_vec, angle);
	} else {
		INIT(tmp, Matrix, opt, vec_ptr, angle);
	}
	if (tmp == nullptr) {
		foreward = foreward_copy;
		return false;
	}
	backward = *tmp * backward;
	delete tmp;
	return true;
}


std::ostream& operator<<(std::ostream& stream, const Matrix& m)
{
	for (std::size_t i = 0; i < 4; i++) {
		std::cout << "|";
		for (std::size_t j = 0 ; j < 4; j++) {
			std::cout << "\t" << m._matrix[i*4 + j];
		}
		std::cout << "|" << std::endl;
	}

	return stream;
}

std::ostream& operator<<(std::ostream& stream, Matrix&& m)
{
	for (std::size_t i = 0; i < 4; i++) {
		std::cout << "|";
		for (std::size_t j = 0 ; j < 4; j++) {
			std::cout << "\t" << m._matrix[i*4 + j];
		}
		std::cout << "|" << std::endl;
	}

	return stream;
}

Matrix::~Matrix()
{
	if (err != nullptr)
		delete err;
}

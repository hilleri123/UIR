
#pragma once


#include "point.h"
#include "vector.h"
#include "metrics.h"

#include <cstdarg>
#include <valarray>
#include <utility>
#include <stdexcept>



class Matrix : public base_init
{
public:
	enum matrix {null, move, rotate, comp};
//	    x y z
//	 x (1 0 0 0)
//	 y (0 1 0 0)
//	 z (0 0 1 0)
//	   (0 0 0 1)
	explicit Matrix(matrix opt = null, const Vector* v = nullptr, double angle = 0);

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) = default;
	
	virtual bool init() const override;

	bool operator==(const Matrix& vector) const;
	bool operator!=(const Matrix& vector) const;
	bool operator==(Matrix&& vector) const;
	bool operator!=(Matrix&& vector) const;

//	this = this * matrix
	Matrix& operator*=(const Matrix&);

	friend Matrix operator*(const Matrix&, const Matrix&);

	Point operator()(Point) const;

	Vector operator()(Vector) const;

	friend std::ostream& operator<<(std::ostream& stream, const Matrix& m);
	friend std::ostream& operator<<(std::ostream& stream, Matrix&& m);

	std::size_t size() const;

	//static Matrix&& transform(const Matrix& matrixs...);
	
	static bool multiplay_foreward_backward(Matrix& foreward, Matrix& backward, matrix opt = null, const Vector* vec_ptr = nullptr, double angle = 0);

	virtual ~Matrix() override;
protected:
	std::valarray<double> _matrix;

	std::exception* err = nullptr;
};

#ifndef RAYTRACE_MATRIX_H
#define RAYTRACE_MATRIX_H

class Matrix
{
public:
	double m[4][4];

public:
	Matrix();
	Matrix(const Matrix& mat);
	~Matrix();

	Matrix& operator=(const Matrix& rhs);

	void setIdentity();

	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator/(const Matrix& mat, double d);
};

#endif

#include "Matrix.h"

Matrix::Matrix()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			m[x][y] = 0.0;
		}
	}
}

Matrix::Matrix(const Matrix& mat)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			m[x][y] = mat.m[x][y];
		}
	}
}

Matrix::~Matrix()
{}

void Matrix::setIdentity()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
	}
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
	if (this == &rhs)
		return (*this);

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			m[x][y] = rhs.m[x][y];
		}
	}

	return (*this);
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix prod;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			double sum = 0.0;
			for (int j = 0; j < 4; j++)
				sum += lhs.m[x][j] * rhs.m[j][y];
			prod.m[x][y] = sum;
		}
	}

	return prod;
}

Matrix operator/(const Matrix& mat, double d)
{
	Matrix ret;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			ret.m[x][y] = mat.m[x][y] / d;
		}
	}

	return ret;
}


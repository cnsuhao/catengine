#include "Point3D.h"
#include "Vector3D.h"
#include "Normal.h"
#include "Matrix.h"
#include <math.h>

Point3D::Point3D()
	: x(0.0), y(0.0), z(0.0)
{}

Point3D::Point3D(double a, double b, double c)
	: x(a), y(b), z(c)
{}

Point3D::Point3D(const Point3D& p)
	: x(p.x), y(p.x), z(p.z)
{}

Point3D::Point3D(const Vector3D& v)
	: x(v.x), y(v.x), z(v.z)
{}

Point3D::Point3D(const Normal& n)
	: x(n.x), y(n.x), z(n.z)
{}

Point3D::~Point3D()
{}

Point3D& Point3D::operator=(const Point3D& rhs)
{
	if (this == &rhs)
		return (*this);

	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

Point3D& Point3D::operator=(const Vector3D& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

Point3D& Point3D::operator=(const Normal& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

double Point3D::distance(const Point3D& p) const
{
	return sqrt(this->distanceSquared(p));
}

double Point3D::distanceSquared(const Point3D& p) const
{
	return ((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) + (z-p.z)*(z-p.z));
}

Point3D operator*(const Matrix& mat, const Point3D& p)
{
	return Point3D(mat.m[0][0]*p.x + mat.m[0][1]*p.y + mat.m[0][2]*p.z + mat.m[0][3],
								 mat.m[1][0]*p.x + mat.m[1][1]*p.y + mat.m[1][2]*p.z + mat.m[1][3],
								 mat.m[2][0]*p.x + mat.m[2][1]*p.y + mat.m[2][2]*p.z + mat.m[2][3]);
}


#include "Normal.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "math.h"

Normal::Normal()
	: x(0.0), y(0.0), z(0.0)
{}

Normal::Normal(double _x, double _y, double _z)
	: x(_x), y(_y), z(_z)
{}

Normal::Normal(const Normal& n)
	: x(n.x), y(n.y), z(n.z)
{}

Normal::Normal(const Vector3D& v)
	: x(v.x), y(v.y), z(v.z)
{}

Normal::Normal(const Point3D& p)
	: x(p.x), y(p.y), z(p.z)
{}

Normal::~Normal()
{}

Normal& Normal::operator=(const Normal& rhs)
{
	if (this == &rhs)
		return (*this);

	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

Normal& Normal::operator=(const Vector3D& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

Normal& Normal::operator=(const Point3D& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

void Normal::normalize()
{
	double length = sqrt(x*x + y*y + z*z);
	x /= length;
	y /= length;
	z /= length;
}

Normal operator*(const Matrix& mat, const Normal& v)
{
	return Normal(mat.m[0][0]*v.x + mat.m[0][1]*v.y + mat.m[0][2]*v.z,
								mat.m[1][0]*v.x + mat.m[1][1]*v.y + mat.m[1][2]*v.z,
								mat.m[2][0]*v.x + mat.m[2][1]*v.y + mat.m[2][2]*v.z);
}

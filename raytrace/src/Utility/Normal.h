#ifndef RAYTRACE_NORMAL_H
#define RAYTRACE_NORMAL_H

class Point3D;
class Vector3D;

class Normal
{
public:
	double x, y, z;

public:
	Normal();
	Normal(double _x, double _y, double _z);
	Normal(const Normal& n);
	Normal(const Vector3D& v);
	Normal(const Point3D& v);
	~Normal();

	Normal& operator=(const Normal& rhs);
	Normal& operator=(const Vector3D& rhs);
	Normal& operator=(const Point3D& rhs);

	void normalize();

	Normal operator-() const;
	Normal& operator+=(const Normal& n);
};

inline Normal Normal::operator-() const
{
	return Normal(-x, -y, -z);
}

inline Normal& Normal::operator+=(const Normal& n)
{
	x += n.x;
	y += n.y;
	z += n.z;
	return (*this);
}

class Matrix;
Normal operator*(const Matrix& mat, const Normal& n);

#endif

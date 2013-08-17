#ifndef RAYTRACE_VECTOR3D_H
#define RAYTRACE_VECTOR3D_H

class Normal;
class Point3D;

class Vector3D
{
public:
	double x, y, z;

public:
	Vector3D();
	Vector3D(double _x, double _y, double _z);
	Vector3D(const Vector3D& v);
	Vector3D(const Normal& n);
	Vector3D(const Point3D& p);
	~Vector3D();

	Vector3D& operator=(const Vector3D& rhs);
	Vector3D& operator=(const Normal& rhs);
	Vector3D& operator=(const Point3D& rhs);

	Vector3D operator-() const;
	Vector3D& operator+=(const Vector3D& v);

	double length();
	double lenSquared();		// square of the length

	void normalize();
	Vector3D& hat();				// return a unit vector, and normalize the vector

};

inline Vector3D Vector3D::operator-() const
{
	return Vector3D(-x, -y, -z);
}
/*
Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return (*this);
}
*/
inline double Vector3D::lenSquared()
{
	return (x*x + y*y + z*z);
}

inline Vector3D operator*(const Vector3D& v, double a)
{
	return Vector3D(v.x*a, v.y*a, v.z*a);
}

inline Vector3D operator*(double a, const Vector3D& v)
{
	return Vector3D(v.x*a, v.y*a, v.z*a);
}

inline Vector3D operator/(const Vector3D& v, double a)
{
	return Vector3D(v.x/a, v.y/a, v.z/a);
}

inline Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}

inline Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}

// dot product
inline double operator*(const Vector3D& lhs, const Vector3D& rhs)
{
	return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z);
}

// cross product
inline Vector3D operator^(const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.y*rhs.z - lhs.z*rhs.y,
									lhs.z*rhs.x - lhs.x*rhs.z,
									lhs.x*rhs.y - lhs.y*rhs.x);
}

class Matrix;
Vector3D operator*(const Matrix& mat, const Vector3D& v);

#endif

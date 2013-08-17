#ifndef RAYTRACE_POINT3D_H
#define RAYTRACE_POINT3D_H

class Normal;
class Vector3D;

class Point3D
{
public:
	double x, y, z;

public:
	Point3D();
	Point3D(double a, double b, double c);
	Point3D(const Point3D& p);
	Point3D(const Vector3D& p);
	Point3D(const Normal& n);
	~Point3D();

	double distance(const Point3D& p) const;				// distance between two point
	double distanceSquared(const Point3D& p) const;	// square of distance between two points

	Point3D& operator=(const Point3D& p);
	Point3D& operator=(const Vector3D& v);
	Point3D& operator=(const Normal& n);
	Point3D operator-() const;
};

inline Point3D Point3D::operator-() const
{
	return Point3D(-x, -y, -z);
}

class Matrix;
Point3D operator*(const Matrix& mat, const Point3D& v);

#endif

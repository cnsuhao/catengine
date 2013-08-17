#ifndef RAYTRACE_RAY_H
#define RAYTRACE_RAY_H

#include "Point3D.h"
#include "Vector3D.h"

class Ray
{
public:
	Point3D o;		// origin
	Vector3D d;		// direction

	Ray();
	Ray(const Point3D& origin, const Vector3D& dir);
	Ray(const Ray& ray);
	~Ray();

	Ray& operator=(const Ray& rhs);
};

#endif

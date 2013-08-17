#ifndef RAYTRACE_SPHERE_H
#define RAYTRACE_SPHERE_H

#include "GeometricObject.h"
#include "Utility/Point3D.h"

class Sphere : public GeometricObject
{
public:
	Sphere();
	Sphere(Point3D center, double r);
	Sphere(const Sphere& sphere);
	virtual ~Sphere();

	Sphere& operator=(const Sphere& sphere);

	virtual Sphere* clone() const;
	void setCenter(const Point3D& c);
	void setCenter(double x, double y, double z);
	void setRadius(double r);
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	virtual RGBColor getColor() const { return color_; };
	void setColor(const RGBColor& c) { color_ = c; }

private:
	Point3D center_;
	double  radius_;
	RGBColor color_;

	static const double kEpsilon;
};

inline void Sphere::setCenter(const Point3D& c)
{
	center_ = c;
}

inline void Sphere::setCenter(double x, double y, double z)
{
	center_.x = x;
	center_.y = y;
	center_.z = z;
}

inline void Sphere::setRadius(double r)
{
	radius_ = r;
}

#endif

#include "Sphere.h"
#include "Utility/Constants.h"
#include "Utility/ShadeRec.h"
#include <math.h>

Sphere::Sphere() :
	GeometricObject(),
	center_(0.0, 0.0, 0.0),
	radius_(1.0),
	color_(RGBColor::RED)
{}

Sphere::Sphere(Point3D c, double r) :
	GeometricObject(),
	center_(c),
	radius_(r),
	color_(RGBColor::RED)
{}

Sphere::Sphere(const Sphere& sphere) :
	GeometricObject(sphere),
	center_(sphere.center_),
	radius_(sphere.radius_)
{}

Sphere* Sphere::clone() const
{
	return new Sphere(*this);
}

Sphere& Sphere::operator=(const Sphere& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	center_ = rhs.center_;
	radius_ = rhs.radius_;
	return (*this);
}

Sphere::~Sphere()
{}

bool Sphere::hit(const Ray& ray, double &tmin, ShadeRec& sr) const
{
	double t;
	Vector3D temp = ray.o - center_;
	double   a    = ray.d * ray.d;
	double   b    = 2.0 * temp * ray.d;
	double   c    = temp * temp - radius_ * radius_;
	double   disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return false;

	double e = sqrt(disc);
	double denom = 2.0 * a;
	t = (-b - e) / denom;
	if (t > kEpsilon)
	{
		tmin = t;
		sr.normal = (temp + t * ray.d) / radius_;
		sr.localHitPoint = ray.o + t * ray.d;
		return true;
	}

	t = (-b + e) / denom;
	if (t > kEpsilon)
	{
		tmin = t;
		sr.normal = (temp + t * ray.d) / radius_;
		sr.localHitPoint = ray.o + t * ray.d;
		return true;
	}

	return false;
}


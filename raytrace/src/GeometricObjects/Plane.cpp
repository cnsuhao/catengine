#include "Plane.h"
#include "Utility/Constants.h"
#include "Utility/Ray.h"
#include "Utility/ShadeRec.h"

Plane::Plane() : point_(0,0,0), normal_(0,1,0), color_(RGBColor::GREEN)
{
}

Plane::Plane(const Point3D& p, const Normal& n) : point_(p), normal_(n), color_(RGBColor::GREEN)
{
}

Plane::~Plane()
{
}

bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t = (point_ - ray.o) * normal_ / (ray.d * normal_);

	if (t > kEpsilon)
	{
		tmin = t;
		sr.normal = normal_;
		sr.localHitPoint = ray.o + t * ray.d;
		return true;
	}

	return false;
}


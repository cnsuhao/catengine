#pragma once

#include "Utility/Point3D.h"
#include "Utility/Normal.h"
#include "Utility/RGBColor.h"
#include "GeometricObject.h"

class Plane : public GeometricObject
{
public:
	Plane();
	Plane(const Point3D& p, const Normal& n);
	virtual ~Plane();
	
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual RGBColor getColor() const { return color_; }
	void setColor(const RGBColor& c) { color_ = c; }

private:
	Point3D point_;  // point through which plane passes
	Normal normal_;  // normal to the plane
	RGBColor color_;
};


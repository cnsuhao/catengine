#ifndef RAYTRACE_GEOMETRIC_OBJECT_H
#define RAYTRACE_GEOMETRIC_OBJECT_H

#include "Utility/RGBColor.h"

class Ray;
class ShadeRec;
class Material;

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
	virtual RGBColor getColor() const = 0;

	Material* getMaterial() const { return pMaterial_; }
	virtual void setMaterial(Material* pMaterial);

protected:
	mutable Material* pMaterial_;		// mutable allows Compound::hit, Instance::hit
																	// and Grid::hit to assign to pMaterial_.
																	// hit functions are const

	GeometricObject& operator=(const GeometricObject& rhs);
};

#endif

#ifndef RAYTRACESHADERECH
#define RAYTRACESHADERECH

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class Material;

class ShadeRec
{
public:
	bool      hitAnObject;				// Did the ray hit an object?
	Material *pMaterial;					// Pointer to the nearest object's material
	Point3D   hitPoint;						// World coordinates of intersectoin
	Point3D   localHitPoint;			// World coordinates of hit point on generic object (used for texture transformations)
	Normal    normal;							// Normal at hit point
	Ray       ray;								// Required for specular highlights and area lights
	int       depth;							// recursion depth
	float     t;									// ray parameter
	RGBColor  color;

public:
	ShadeRec();
	ShadeRec(const ShadeRec& sr);
};

#endif

#ifndef RAYTRACE_SINGLE_SPHERE_H
#define RAYTRACE_SINGLE_SPHERE_H

#include "Tracer.h"

class SingleSphere : public Tracer
{
public:
	SingleSphere();
	SingleSphere(World* pWorld);
	virtual ~SingleSphere();

	virtual RGBColor traceRay(const Ray& ray) const;
};

#endif

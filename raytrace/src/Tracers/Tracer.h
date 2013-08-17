#ifndef RAYTRACE_TRACER_H
#define RAYTRACE_TRACER_H

#include "Utility/RGBColor.h"

class Ray;
class World;

class Tracer
{
public:
	Tracer();
	Tracer(World *pWorld);
	virtual ~Tracer();

	virtual RGBColor traceRay(const Ray& ray) const;
	virtual RGBColor traceRay(const Ray& ray, int depth) const;

protected:
	World* pWorld_;
};

#endif

#include "Tracer.h"
#include <stdlib.h>

Tracer::Tracer()
	: pWorld_(NULL)
{}

Tracer::Tracer(World *pWorld)
	: pWorld_(pWorld)
{}

Tracer::~Tracer()
{
	if (pWorld_)
		pWorld_ = NULL;
}

RGBColor Tracer::traceRay(const Ray& ray) const
{
	return RGBColor::BLACK;
}

RGBColor Tracer::traceRay(const Ray& ray, int depth) const
{
	return RGBColor::BLACK;
}



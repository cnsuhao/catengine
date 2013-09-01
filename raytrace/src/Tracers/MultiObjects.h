#pragma once

#include "Tracer.h"

class MultiObjects : public Tracer
{
public:
	MultiObjects();
	MultiObjects(World* pWorld);
	virtual ~MultiObjects();

	virtual RGBColor traceRay(const Ray& ray) const;
};


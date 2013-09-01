#include "MultiObjects.h"
#include "World/World.h"
#include "Utility/ShadeRec.h"

MultiObjects::MultiObjects()
	: Tracer()
{}

MultiObjects::MultiObjects(World* pWorld)
	: Tracer(pWorld)
{}

MultiObjects::~MultiObjects()
{}

RGBColor MultiObjects::traceRay(const Ray& ray) const
{
	ShadeRec sr(pWorld_->hit(ray));

	if (sr.hitAnObject)
		return sr.color;
	else
		return pWorld_->getBgColor();
}


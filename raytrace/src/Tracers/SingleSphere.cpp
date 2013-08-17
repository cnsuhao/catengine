#include "SingleSphere.h"
#include "World/SphereWorld.h"
#include "Utility/ShadeRec.h"

SingleSphere::SingleSphere()
	: Tracer()
{}

SingleSphere::SingleSphere(World* pWorld)
	: Tracer(pWorld)
{}

SingleSphere::~SingleSphere()
{}

RGBColor SingleSphere::traceRay(const Ray& ray) const
{
	ShadeRec sr(pWorld_->hit(ray));

	if (sr.hitAnObject)
		return sr.color;
	else
		return pWorld_->getBgColor();
}


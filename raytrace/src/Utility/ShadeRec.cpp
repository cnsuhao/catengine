// there is no default constructor as the World reference has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "ShadeRec.h"
#include <stdlib.h>

ShadeRec::ShadeRec() :
	hitAnObject(false),
	pMaterial(NULL),
	hitPoint(),
	localHitPoint(),
	normal(),
	ray(),
	depth(0),
	t(0.0)
{}

ShadeRec::ShadeRec(const ShadeRec& sr) :
	hitAnObject(sr.hitAnObject),
	pMaterial(sr.pMaterial),
	hitPoint(sr.hitPoint),
	localHitPoint(sr.localHitPoint),
	normal(sr.normal),
	ray(sr.ray),
	depth(sr.depth),
	t(sr.t)
{}


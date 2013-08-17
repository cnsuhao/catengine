#ifndef RAYTRACE_SPHERE_WORLD_H
#define RAYTRACE_SPHERE_WORLD_H

// chap03, simple world

#include "World.h"
#include "GeometricObjects/Sphere.h"

class SphereWorld : public World
{
public:
	Sphere sphere;

public:
	SphereWorld();
	virtual ~SphereWorld();

	virtual void build();
	virtual ShadeRec hit(const Ray& ray);

private:
	virtual void renderSceneInternal();
};

#endif

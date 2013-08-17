#ifndef RAYTRACE_PERSPECTIVE_WORLD_H
#define RAYTRACE_PERSPECTIVE_WORLD_H

// chap08, perspective world

#include "World.h"
#include "GeometricObjects/Sphere.h"

class PerspectiveWorld : public World
{
public:
	Sphere sphere;

public:
	PerspectiveWorld();
	virtual ~PerspectiveWorld();

	virtual void build();
	virtual ShadeRec hit(const Ray& ray);

private:
	virtual void renderSceneInternal();
};

#endif

#ifndef RAYTRACE_PERSPECTIVE_WORLD_H
#define RAYTRACE_PERSPECTIVE_WORLD_H

// chap08, perspective world

#include "World.h"
#include "GeometricObjects/Sphere.h"

class PerspectiveWorld : public World
{
public:
	PerspectiveWorld();
	virtual ~PerspectiveWorld();

	virtual void build();

private:
	virtual void renderSceneInternal();
};

#endif

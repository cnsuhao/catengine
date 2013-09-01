#pragma once

// chap03, simple world

#include "World.h"
#include "GeometricObjects/Sphere.h"

class SphereWorld : public World
{
public:
	SphereWorld();
	virtual ~SphereWorld();

	virtual void build();

private:
	virtual void renderSceneInternal();
};

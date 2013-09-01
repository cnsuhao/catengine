#pragma once

// chap03, multi-objects world

#include "World.h"

class MultiObjectsWorld : public World
{
public:
	MultiObjectsWorld();
	virtual ~MultiObjectsWorld();

	virtual void build();

private:
	virtual void renderSceneInternal();
};

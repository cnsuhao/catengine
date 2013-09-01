#include "World.h"
#include "Utility/Constants.h"
#include "Utility/Maths.h"
#include "Utility/ShadeRec.h"
#include "Tracers/Tracer.h"
#include "GeometricObjects/GeometricObject.h"
#include <assert.h>

World::World() :
	bgColor_(RGBColor::BLACK),
	pTracer_(NULL),
	pWin_(NULL),
	pRenderer_(NULL)
{}

World::~World()
{
	for (size_t i = 0; i < objects_.size(); i++)
	{
		delete objects_[i];
	}
	objects_.clear();

	if (pTracer_)
	{
		delete pTracer_;
		pTracer_ = NULL;
	}

	if (pRenderer_)
	{
		SDL_DestroyRenderer(pRenderer_);
		pRenderer_ = NULL;
	}

	if (pWin_)
	{
		SDL_DestroyWindow(pWin_);
		pWin_ = NULL;
	}
}

void World::addObject(GeometricObject* obj)
{
	objects_.push_back(obj);
}

ShadeRec World::hit(const Ray& ray)
{
	ShadeRec sr;
	double t;
	double tmin = kHugeValue;
	int numObjects = objects_.size();

	for (int i = 0; i < numObjects; i++)
	{
		if (objects_[i]->hit(ray, t, sr) && (t < tmin))
		{
			sr.hitAnObject = true;
			tmin = t;
			sr.color = objects_[i]->getColor();
		}
	}

	return sr;
}

void World::openWindow(int hRes, int vRes)
{
	int result;
	result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0);

	pWin_ = SDL_CreateWindow("RayTracing", 100, 100, hRes, vRes, SDL_WINDOW_SHOWN);
	assert(pWin_ != NULL);

	pRenderer_ = SDL_CreateRenderer(pWin_, -1, SDL_RENDERER_ACCELERATED);
	assert(pRenderer_ != NULL);

	SDL_SetRenderDrawColor(pRenderer_, (Uint8)(bgColor_.r*255), (Uint8)(bgColor_.g*255), (Uint8)(bgColor_.b*255), 255);
	SDL_RenderClear(pRenderer_);

	atexit(SDL_Quit);
}

void World::presentWindow()
{
	SDL_RenderPresent(pRenderer_);

	SDL_Event event;
	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			break;
	}
}

void World::renderScene()
{
	openWindow(vp_.hRes, vp_.vRes);
	this->renderSceneInternal();
	presentWindow();
}

RGBColor World::clampToColor(const RGBColor &c) const
{
	if (c.r > 1.0 || c.g > 1.0 || c.b > 1.0)
		return RGBColor::RED;

	return c;
}

RGBColor World::maxToOne(const RGBColor &c) const
{
	float maxValue = (float)max(c.r, max(c.g, c.b));
	if (maxValue > 1.0)
		return (c / maxValue);
	else
		return c;
}

void World::displayPixel(int x, int y, const RGBColor &c)
{
	RGBColor mappedColor;

	if (vp_.showOutOfGamut)
		mappedColor = clampToColor(c);
	else
		mappedColor = maxToOne(c);

	if (vp_.gamma != 1.0f)
		mappedColor = mappedColor.powc(vp_.invGamma);

	SDL_SetRenderDrawColor(pRenderer_, (Uint8)(c.r*255), (Uint8)(c.g*255), (Uint8)(c.b*255), 255);
	SDL_RenderDrawPoint(pRenderer_, x, y);
}


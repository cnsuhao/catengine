#pragma once

#include "ViewPlane.h"
#include "Utility/RGBColor.h"
#include "Utility/ShadeRec.h"
#include <vector>
#if defined(_WIN32)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class GeometricObject;
class Tracer;
class Ray;

class World
{
public:
	World();
	virtual ~World();

	virtual void build() = 0;

	void addObject(GeometricObject* obj);
	ShadeRec hit(const Ray& ray);

	void renderScene();
	RGBColor getBgColor() { return bgColor_; }

protected:
	ViewPlane vp_;
	RGBColor bgColor_;
	Tracer *pTracer_;
	std::vector<GeometricObject*> objects_;

protected:
	void displayPixel(int x, int y, const RGBColor& c);

private:
	virtual void renderSceneInternal() = 0;
	void openWindow(int w, int h);
	void presentWindow();

	RGBColor clampToColor(const RGBColor &c) const;
	RGBColor maxToOne(const RGBColor &c) const;

private:
	SDL_Window *pWin_;
	SDL_Renderer *pRenderer_;
};


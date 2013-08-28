#ifndef RAYTRACE_WORLD_H
#define RAYTRACE_WORLD_H

#include "ViewPlane.h"
#include "Utility/RGBColor.h"
#include "Utility/ShadeRec.h"
#if defined(_WIN32)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Tracer;
class Ray;

class World
{
public:
	World();
	virtual ~World();

	virtual void build() = 0;
	virtual ShadeRec hit(const Ray& ray) = 0;

	void renderScene();
	RGBColor getBgColor() { return bgColor_; }

protected:
	ViewPlane vp_;
	RGBColor bgColor_;
	Tracer *pTracer_;

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

#endif

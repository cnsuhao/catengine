#include "PerspectiveWorld.h"
#include "Tracers/SingleSphere.h"
#include "Utility/Vector3D.h"
#include "Utility/Ray.h"
#include <stdlib.h>
#include <assert.h>

PerspectiveWorld::PerspectiveWorld()
{}

PerspectiveWorld::~PerspectiveWorld()
{}

void PerspectiveWorld::build()
{
	vp_.setHRes(400);
	vp_.setVRes(400);
	vp_.setPixelSize(1.0);
	vp_.setGamma(1.8);

	pTracer_ = new SingleSphere(this);

	sphere.setCenter(0.0, 0.0, 0.0);
	sphere.setRadius(85.0);
	sphere.setColor(RGBColor::BLUE);
}

ShadeRec PerspectiveWorld::hit(const Ray& ray)
{
	ShadeRec sr;
	double t;

	if (sphere.hit(ray, t, sr))
	{
		sr.hitAnObject = true;
		sr.color       = sphere.getColor();
	}

	return sr;
}

void PerspectiveWorld::renderSceneInternal()
{
	RGBColor pixelColor;
	Ray ray;
	double zw = 100.0;
	double x, y;

	ray.o = Point3D(0, 0, zw);

	for (int r = 0; r < vp_.vRes; r++)
	{
		for (int c = 0; c < vp_.hRes; c++)
		{
			x = vp_.s * (c - 0.5 * (vp_.hRes - 1.0));
			y = vp_.s * (0.5 * (vp_.vRes - 1.0) - r);
			Point3D pt(x, y, 0);
			ray.d = pt - ray.o;
			ray.d.normalize();
			pixelColor = pTracer_->traceRay(ray);
			displayPixel(c, r, pixelColor);
		}
	}
}

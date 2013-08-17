#include "RGBColor.h"
#include <math.h>

const RGBColor RGBColor::BLACK(0.0, 0.0, 0.0);
const RGBColor RGBColor::WHITE(1.0, 1.0, 1.0);
const RGBColor RGBColor::RED(1.0, 0.0, 0.0);
const RGBColor RGBColor::GREEN(0.0, 1.0, 0.0);
const RGBColor RGBColor::BLUE(0.0, 0.0, 1.0);

RGBColor::RGBColor()
	: r(0.0), g(0.0), b(0.0)
{}

RGBColor::RGBColor(float _r, float _g, float _b)
	: r(_r), g(_g), b(_b)
{}

RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{}

RGBColor::~RGBColor()
{}

RGBColor& RGBColor::operator=(const RGBColor& rhs)
{
	if (this == &rhs)
		return (*this);

	r = rhs.r;
	g = rhs.g;
	b = rhs.b;
	return (*this);
}

// raise each component to the specified power
// used for color filtering in Chap28
RGBColor RGBColor::powc(float p) const
{
	return RGBColor(pow(r,p), pow(g,p), pow(b,p));
}


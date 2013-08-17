#include "ViewPlane.h"

ViewPlane::ViewPlane() :
	hRes(400),
	vRes(400),
	s(1.0),
	numSamples(1),
	gamma(1.0),
	invGamma(1.0),
	showOutOfGamut(false)
{}

ViewPlane::ViewPlane(const ViewPlane& vp) :
	hRes(vp.hRes),
	vRes(vp.vRes),
	s(vp.s),
	numSamples(vp.numSamples),
	gamma(vp.gamma),
	invGamma(vp.invGamma),
	showOutOfGamut(vp.showOutOfGamut)
{}

ViewPlane& ViewPlane::operator=(const ViewPlane& rhs)
{
	if (this == &rhs)
		return *this;

	hRes           = rhs.hRes;
	vRes           = rhs.vRes;
	s              = rhs.s;
	numSamples     = rhs.numSamples;
	gamma          = rhs.gamma;
	invGamma       = rhs.invGamma;
	showOutOfGamut = rhs.showOutOfGamut;
	return *this;
}

ViewPlane::~ViewPlane()
{}


#pragma once

class ViewPlane
{
public:
	int   hRes;						// horizontal image resolution
	int   vRes;						// vertical image resolution
	float s;							// pixel size
	int   numSamples;			// number of samples per pixel
	float gamma;					// gamma correction factor
	float invGamma;				// the inverse of the gamma correction factor
	bool  showOutOfGamut;	// display red if RGBColor out of gamut

public:
	ViewPlane();
	ViewPlane(const ViewPlane& vp);
	ViewPlane& operator=(const ViewPlane& rhs);
	~ViewPlane();

	void setHRes(const int _hRes) { hRes = _hRes; }
	void setVRes(const int _vRes) { vRes = _vRes; }
	void setPixelSize(const float size) { s = size; }
	void setGamma(const float g) { gamma = g; invGamma = 1.0f / g; }
	void setGamutDisplay(bool show) { showOutOfGamut = show; }
	void setSamples(const int n) { numSamples = n; }
};


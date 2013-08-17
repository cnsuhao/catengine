#ifndef RAYTRACE_MATERIAL_H
#define RAYTRACE_MATERIAL_H

#include "Utility/RGBColor.h"

class ShadeRec;

class Material
{
public:
	Material();
	Material(const Material& material);
	virtual ~Material();

	virtual Material* clone() const = 0;
	virtual RGBColor shade(ShadeRec& sr);

protected:
	Material& operator=(const Material& rhs);
};

#endif

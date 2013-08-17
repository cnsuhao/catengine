#include "GeometricObject.h"
#include "Materials/Material.h"
#include <stdlib.h>

GeometricObject::GeometricObject()
	: pMaterial_(NULL)
{}

GeometricObject::GeometricObject(const GeometricObject& object)
{
	if (object.pMaterial_)
		pMaterial_ = object.pMaterial_->clone();
	else
		pMaterial_ = NULL;
}

GeometricObject& GeometricObject::operator=(const GeometricObject& rhs)
{
	if (this == &rhs)
		return (*this);

	if (pMaterial_)
	{
		delete pMaterial_;
		pMaterial_ = NULL;
	}

	if (rhs.pMaterial_)
		pMaterial_ = rhs.pMaterial_->clone();

	return (*this);
}

GeometricObject::~GeometricObject()
{
	if (pMaterial_)
	{
		delete pMaterial_;
		pMaterial_ = NULL;
	}
}

void GeometricObject::setMaterial(Material *pMaterial)
{
	pMaterial_ = pMaterial;
}


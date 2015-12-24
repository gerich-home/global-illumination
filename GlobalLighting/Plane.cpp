#include "StdAfx.h"
#include "Plane.h"

Plane::Plane(const Vector& normal, GO_FLOAT d, const Material* material) :
	normal(normal),
	d(d),
	material(material)
{
}

Plane::Plane(const Vector& a, const Vector& b, const Vector& A, const Material* material) :
	normal(a.CrossProduct(b).Normalize()),
	material(material)
{
	d = A.DotProduct(normal);
}

Plane::Plane(GO_FLOAT a, GO_FLOAT b, GO_FLOAT c, GO_FLOAT d, const Material* material):
	normal(Vector(a, b, c).Normalize()),
	d(d),
	material(material)
{
}

const HitPoint* Plane::Intersection(const Vector& start, const Vector& direction) const
{
	GO_FLOAT divident = normal.DotProduct(direction);

	if(divident == 0)
	{
		return NULL;
	}

	GO_FLOAT t = (start.DotProduct(normal) + d) / normal.DotProduct(direction);

	if(t < 0)
	{
		return NULL;
	}

	return new HitPoint(t, normal, material);
}

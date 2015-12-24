#include "StdAfx.h"
#include "Plane.h"

using namespace Engine;

Shapes::Plane::Plane(const Vector& normal, GO_FLOAT d, const IMaterial* material) :
	normal(normal),
	d(d),
	A( (normal.x != 0 ? -d / normal.x : 0                                              ),
	   (normal.x != 0 ? 0             : (normal.y != 0 ? -d / normal.y : 0            )),
	   (normal.x != 0 ? 0             : (normal.y != 0 ? 0             : -d / normal.z))
	   ),
	material(material)
{
}

Shapes::Plane::Plane(const Vector& a, const Vector& b, const Vector& A, const IMaterial* material) :
	normal(a.CrossProduct(b).Normalize()),
	A(A),
	material(material)
{
	d = A.DotProduct(normal);
}

Shapes::Plane::Plane(GO_FLOAT a, GO_FLOAT b, GO_FLOAT c, GO_FLOAT d, const IMaterial* material):
	normal(Vector(a, b, c).Normalize()),
	d(d),
	material(material),
	A( (a != 0 ? -d / a : 0                         ),
	   (a != 0 ? 0      : (b != 0 ? -d / b : 0     )),
	   (a != 0 ? 0      : (b != 0 ? 0      : -d / c))
	   )
{
}

const HitPoint* Shapes::Plane::Intersection(const Vector& start, const Vector& direction) const
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
#include "StdAfx.h"
#include "Plane.h"

Plane::Plane(const Vector& normal, GO_FLOAT d, const Material* material, const Luminance& Le) :
	normal(normal),
	d(d),
	A( (normal.x != 0 ? -d / normal.x : 0                                              ),
	   (normal.x != 0 ? 0             : (normal.y != 0 ? -d / normal.y : 0            )),
	   (normal.x != 0 ? 0             : (normal.y != 0 ? 0             : -d / normal.z))
	   ),
	material(material),
	Le(Le)
{
}

Plane::Plane(const Vector& a, const Vector& b, const Vector& A, const Material* material, const Luminance& Le) :
	normal(a.CrossProduct(b).Normalize()),
	A(A),
	material(material),
	Le(Le)
{
	d = A.DotProduct(normal);
}

Plane::Plane(GO_FLOAT a, GO_FLOAT b, GO_FLOAT c, GO_FLOAT d, const Material* material, const Luminance& Le):
	normal(Vector(a, b, c).Normalize()),
	d(d),
	material(material),
	A( (a != 0 ? -d / a : 0                         ),
	   (a != 0 ? 0      : (b != 0 ? -d / b : 0     )),
	   (a != 0 ? 0      : (b != 0 ? 0      : -d / c))
	   ),
	Le(Le)
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

const LightPoint Plane::SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const
{
	return LightPoint(Vector(), 1, Le.colors[colorIndex]);
}

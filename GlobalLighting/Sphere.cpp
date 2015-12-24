#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Sphere.h"

using namespace Engine;

Shapes::Sphere::Sphere(const Vector& center, GO_FLOAT r, const IMaterial* material) :
	center(center),
	material(material),
	r2(r * r),
	rinv(1 / r)
{
}

const HitPoint* Shapes::Sphere::Intersection(const Vector& start, const Vector& direction) const
{
	Vector ac = start - center;
	
	GO_FLOAT b = ac.DotProduct(direction);
	GO_FLOAT c = ac.Norm() - r2;

	GO_FLOAT D = b * b - c;

	if(D < 0)
	{
		return NULL;
	}

	D = sqrt(D);
	GO_FLOAT t = -b - D;
	
	if(t < GO_FLOAT_EPSILON)
	{
		t = -b + D;
	
		if(t < GO_FLOAT_EPSILON)
		{
			return NULL;
		}
	}

	return new HitPoint(t, (start + t * direction - center) * rinv, material);
}
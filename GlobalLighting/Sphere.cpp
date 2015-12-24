#include "StdAfx.h"

#include <math.h>
#include "Sphere.h"


Sphere::Sphere(const Vector& center, GO_FLOAT r, const Material* material) :
	center(center),
	material(material),
	r2(r * r),
	rinv(1 / r)
{
}


Sphere::~Sphere(void)
{
}

const HitPoint* Sphere::Intersection(const Vector& start, const Vector& direction) const
{
	Vector ac = start - center;
	
	GO_FLOAT b = ac.DotProduct(direction);
	GO_FLOAT c = ac.Norm() - r2;

	GO_FLOAT D = b * b - c;

	if(c < GO_FLOAT_EPSILON)
	{
		return NULL;
	}

	if(D < 0)
	{
		return NULL;
	}

	D = sqrt(D);
	GO_FLOAT t = -b - D;
	
	if(t < 0)
	{
		return NULL;
	}

	return new HitPoint(t, (start + t * direction - center) * rinv, material);
}

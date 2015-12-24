#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Sphere.h"


Sphere::Sphere(const Vector& center, GO_FLOAT r, const Material* material, const Luminance& Le) :
	center(center),
	material(material),
	r(r),
	r2(r * r),
	rinv(1 / r),
	probability(1 / (4 * M_PI * r * r)),
	Le(Le)
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

const LightPoint Sphere::SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const
{	
	GO_FLOAT cosa = (GO_FLOAT) rand() / RAND_MAX;
	GO_FLOAT sina = sqrt(1 - cosa * cosa);
	GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

	return LightPoint(center + r * Vector(cosa * cos(b), cosa * sin(b), sina), probability, Le.colors[colorIndex]);
}

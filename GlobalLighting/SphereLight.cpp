#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "SphereLight.h"

using namespace Engine;

Lights::Sphere::Sphere(const Vector& center, GO_FLOAT r, const Luminance& Le) :
	center(center),
	r(r),
	probability(1 / (4 * M_PI * r * r)),
	Le(Le)
{
}

const LightPoint Lights::Sphere::SampleLightPoint(const Vector& point) const
{	
	GO_FLOAT cosa = (GO_FLOAT) rand() / RAND_MAX;
	GO_FLOAT sina = sqrt(1 - cosa * cosa);
	GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

	const Vector normal = Vector(cosa * cos(b), cosa * sin(b), sina);

	return LightPoint(center + r * normal, normal, probability, Le);
}

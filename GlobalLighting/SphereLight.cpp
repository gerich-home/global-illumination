#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "SphereLight.h"

using namespace Engine;

Lights::Sphere::Sphere(const Vector& center, GO_FLOAT r, const Luminance& le) :
	center(center),
	r(r),
	probability(1 / (4 * M_PI * r * r)),
	le(le)
{
}

const LightPoint Lights::Sphere::SampleLightPoint(const Vector& point) const
{	
	GO_FLOAT cosa = (GO_FLOAT) rand() / RAND_MAX;
	GO_FLOAT sina = sqrt(1 - cosa * cosa);
	GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

	const Vector normal = Vector(cosa * cos(b), cosa * sin(b), sina);

	return LightPoint(center + r * normal, normal, probability, le);
}

void Lights::Sphere::EmitPhotons(int nphotons, Photon photons[]) const
{
	Luminance energy = le / nphotons;
	for(int i = 0; i < nphotons; i++)
	{		
		GO_FLOAT sina = (GO_FLOAT) rand() / RAND_MAX;
		GO_FLOAT cosa = sqrt(1 - sina * sina);
		GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

		const Vector normal = Vector(cosa * cos(b), cosa * sin(b), sina);
		
		cosa = (GO_FLOAT) rand() / RAND_MAX;
		sina = sqrt(1 - cosa * cosa);
		b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

		Vector direction = Vector(sina * cos(b), sina * sin(b), cosa).Transform(normal);

		photons[i] = Photon(center + r * normal, normal, direction, energy);
	}
}

Luminance Lights::Sphere::Le() const 
{
	return le;
}

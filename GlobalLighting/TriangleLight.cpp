#include "StdAfx.h"
#include "TriangleLight.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Engine;

Lights::Triangle::Triangle(const Vector a, const Vector b, const Vector c, const Luminance& Le): 
	a(a),
	ba(b - a),
	ca(c - a),
	normal((b - a).CrossProduct(c - a).Normalize()),
	probability(2 / (b - a).CrossProduct(c - a).Length()),
	le(le)
{
}

const LightPoint Lights::Triangle::SampleLightPoint(const Vector& point) const
{
	GO_FLOAT t1 = (GO_FLOAT) rand() / RAND_MAX;
	GO_FLOAT t2 = (GO_FLOAT) rand() / RAND_MAX;

	if(t1 + t2 > 1)
	{
		t1 = 1 - t1;
		t2 = 1 - t2;
	}

	Vector p = a + t1 * ba + t2 * ca;
	return LightPoint(p, normal, probability, le);
}

void Lights::Triangle::EmitPhotons(int nphotons, Photon photons[]) const
{
	Luminance energy = le / nphotons;
	for(int i = 0; i < nphotons; i++)
	{
		GO_FLOAT t1 = (GO_FLOAT) rand() / RAND_MAX;
		GO_FLOAT t2 = (GO_FLOAT) rand() / RAND_MAX;
		
		GO_FLOAT cosa = (GO_FLOAT) rand() / RAND_MAX;
		GO_FLOAT sina = sqrt(1 - cosa * cosa);
		GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

		Vector direction = Vector(sina * cos(b), sina * sin(b), cosa).Transform(normal);

		photons[i] = Photon(a + t1 * ba + t2 * ca, normal, direction, energy);
	}
}

Luminance Lights::Triangle::Le() const 
{
	return le;
}
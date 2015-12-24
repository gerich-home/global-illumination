#include "StdAfx.h"
#include "SquareLight.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Engine;

Lights::Square::Square(const Vector a, const Vector b, const Vector c, const Luminance& le):
	a(a),
	ba(b - a),
	ca(c - a),
	normal((b - a).CrossProduct(c - a).Normalize()),
	probability(1 / (b - a).CrossProduct(c - a).Length()),
	le(le)
{
}

const LightPoint Lights::Square::SampleLightPoint(const Vector& point) const
{
	GO_FLOAT t1 = (GO_FLOAT) rand() / RAND_MAX;
	GO_FLOAT t2 = (GO_FLOAT) rand() / RAND_MAX;

	return LightPoint(a + t1 * ba + t2 * ca, normal, probability, le);
}

void Lights::Square::EmitPhotons(int nphotons, Photon photons[]) const
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

Luminance Lights::Square::Le() const 
{
	return le;
}
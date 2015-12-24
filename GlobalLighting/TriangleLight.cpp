#include "StdAfx.h"
#include "TriangleLight.h"

using namespace Engine;

Lights::Triangle::Triangle(const Vector a, const Vector b, const Vector c, const Luminance& Le): 
	a(a),
	ba(b - a),
	ca(c - a),
	normal((b - a).CrossProduct(c - a).Normalize()),
	probability(2 / (b - a).CrossProduct(c - a).Length()),
	Le(Le)
{
}

const LightPoint Lights::Triangle::SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const
{
	GO_FLOAT t1 = (GO_FLOAT) rand() / RAND_MAX;
	GO_FLOAT t2 = (GO_FLOAT) rand() / RAND_MAX;

	if(t1 + t2 > 1)
	{
		t1 = 1 - t1;
		t2 = 1 - t2;
	}

	return LightPoint(a + t1 * ba + t2 * ca, normal, probability, Le.colors[colorIndex]);
}
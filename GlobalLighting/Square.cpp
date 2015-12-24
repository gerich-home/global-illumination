#include "StdAfx.h"
#include "Square.h"


Square::Square(const Vector a, const Vector b, const Vector c, const Material* material, const Luminance& Le):
	a(a),
	ba(b - a),
	ca(c - a),
	normal((b - a).CrossProduct(c - a)),
	n((b - a).CrossProduct(c - a).Normalize()),
	probability((b - a).CrossProduct(c - a).Length()),
	material(material),
	Le(Le)
{
}

const HitPoint* Square::Intersection(const Vector& start, const Vector& direction) const
{
	GO_FLOAT t = 0;
	GO_FLOAT t1 = 0;
	GO_FLOAT t2 = 0;
	

	GO_FLOAT divident = - direction.DotProduct(normal);
	
	if(!divident)
	{
		return NULL;
	}

	GO_FLOAT factor = 1 / divident;

	Vector sa = start - a;
	Vector saxdir = sa.CrossProduct(direction);
	t1 = -ba.DotProduct(saxdir) * factor;
	
	if((t1 < 0) || (1 < t1))
	{
		return NULL;
	}
				
	t2 = ca.DotProduct(saxdir) * factor;
	
	if((t2 < 0) || (1 < t2))
	{
		return NULL;
	}
	
	t = sa.DotProduct(normal) * factor;

	if(t < GO_FLOAT_EPSILON)
	{
		return NULL;
	}

	return new HitPoint(t, n, material);
}

const LightPoint Square::SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const
{
	GO_FLOAT t1 = (GO_FLOAT) rand() / RAND_MAX;
	GO_FLOAT t2 = (GO_FLOAT) rand() / RAND_MAX;

	return LightPoint(a + t1 * ba + t2 * ca, probability, Le.colors[colorIndex]);
}
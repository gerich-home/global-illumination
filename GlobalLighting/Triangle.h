#pragma once
#include "IShape.h"
#include "ILightSource.h"

class Triangle: public IShape, public ILightSource
{
public:
	Triangle(const Vector a, const Vector b, const Vector c, const Material* material, const Luminance& Le = Luminance());

	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;
	virtual const LightPoint SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const;

private:
	const Vector normal;
	const Vector n;
	const GO_FLOAT probability;
	const Vector ba;
	const Vector ca;
	const Vector a;
	const Material* material;
	const Luminance Le;
};


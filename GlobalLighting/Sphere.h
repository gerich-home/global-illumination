#pragma once
#include "IShape.h"
#include "ILightSource.h"
#include "Material.h"
#include "Vector.h"

class Sphere : public IShape, public ILightSource
{
public:
	Sphere(const Vector& center, GO_FLOAT r, const Material* material, const Luminance& Le = Luminance());
	
	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;
	virtual const LightPoint SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const;

private:
	const GO_FLOAT r;
	const GO_FLOAT r2;
	const GO_FLOAT rinv;
	const GO_FLOAT probability;
	const Vector center;
	const Material* material;
	const Luminance Le;
};


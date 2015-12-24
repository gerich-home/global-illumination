#pragma once
#include "Vector.h"
#include "IShape.h"
#include "ILightSource.h"

class Plane : public IShape, public ILightSource
{
public:
	Plane(const Vector& normal, GO_FLOAT d, const Material* material, const Luminance& Le = Luminance());
	Plane(const Vector& a, const Vector& b, const Vector& A, const Material* material, const Luminance& Le = Luminance());
	Plane(GO_FLOAT a, GO_FLOAT b, GO_FLOAT c, GO_FLOAT d, const Material* material, const Luminance& Le = Luminance());

	~Plane() { }

	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;
	virtual const LightPoint SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const;

private:
	GO_FLOAT d;
	const Vector normal;
	const Vector A;
	const Material* material;
	const Luminance Le;
};


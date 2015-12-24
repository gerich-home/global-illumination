#pragma once
#include "Vector.h"
#include "IShape.h"

class Plane : public IShape
{
public:
	Plane(const Vector& normal, GO_FLOAT d, const Material* material);
	Plane(const Vector& a, const Vector& b, const Vector& A, const Material* material);
	Plane(GO_FLOAT a, GO_FLOAT b, GO_FLOAT c, GO_FLOAT d, const Material* material);
	~Plane() { }

	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

private:
	GO_FLOAT d;
	const Vector normal;
	const Material* material;
};


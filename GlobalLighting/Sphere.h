#pragma once
#include "IShape.h"
#include "Material.h"
#include "Vector.h"

class Sphere : public IShape
{
public:
	Sphere(const Vector& center, GO_FLOAT r, const Material* material);
	~Sphere();
	
	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

private:
	GO_FLOAT r2;
	GO_FLOAT rinv;
	const Vector center;
	const Material* material;
};


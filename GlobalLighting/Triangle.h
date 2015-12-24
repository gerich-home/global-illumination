#pragma once
#include "IShape.h"
class Triangle: public IShape
{
public:
	Triangle(const Vector a, const Vector b, const Vector c, const Material* material);
	~Triangle() {}

	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

private:
	 Vector normal;
	 Vector n;
	 const Vector ba;
	 const Vector ca;
	 const Vector a;
	 const Material* material;
};


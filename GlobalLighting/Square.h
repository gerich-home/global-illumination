#pragma once
#include "Vector.h"
#include "IShape.h"

class Square: public IShape
{
public:
	Square(const Vector a, const Vector b, const Vector c, const Material* material);
	~Square(void);

	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

private:
	const Vector a;
	const Vector ba;
	const Vector ca;
	Vector normal;
	Vector n;
	const Material* material;
};


#pragma once
#include "Vector.h"
#include "IShape.h"

class Square: IShape
{
public:
	Square(const Vector a, const Vector b, const Vector c);
	~Square(void);
	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction);

private:
	Vector a;
	Vector ba;
	Vector ca;
	Vector normal;
	Vector n;
	Material* material;
};


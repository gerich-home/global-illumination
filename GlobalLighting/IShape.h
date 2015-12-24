#pragma once
#include "HitPoint.h"

class IShape
{
public:
	virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const = 0;
};


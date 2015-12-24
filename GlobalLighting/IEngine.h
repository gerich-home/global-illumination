#pragma once
#include "HitPoint.h"
#include "IShape.h"
#include "Luminance.h"

class IEngine
{
public:
	virtual GO_FLOAT L(const HitPoint* hp, const Vector& point, const Vector& direction, const IShape* shape, int colorIndex) = 0;
};
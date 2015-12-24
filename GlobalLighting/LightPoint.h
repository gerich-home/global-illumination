#pragma once
#include "defines.h"
#include "Luminance.h"
#include "Vector.h"

class LightPoint
{
public:
	LightPoint(const Vector& point, GO_FLOAT probability, GO_FLOAT Le) :
		point(point),
		probability(probability),
		Le(Le)
	{
	}

	const Vector point;
	const GO_FLOAT probability;
	const GO_FLOAT Le;
};
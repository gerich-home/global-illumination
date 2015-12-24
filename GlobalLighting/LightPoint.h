#pragma once

#include "Defines.h"
#include "Vector.h"
#include "Luminance.h"

namespace Engine
{
	class Vector;
	class Luminance;

	class LightPoint
	{
	public:
		LightPoint(const Vector& point, const Vector& normal, GO_FLOAT probability, const Luminance& Le) :
			point(point),
			normal(normal),
			probability(probability),
			Le(Le)
		{
		}
			
		const Vector point;
		const Vector normal;
		const GO_FLOAT probability;
		const Luminance Le;
	};
}
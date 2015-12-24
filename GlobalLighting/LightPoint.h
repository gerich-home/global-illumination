#pragma once

#include "Defines.h"
#include "Vector.h"

namespace Engine
{
	class LightPoint
	{
	public:
		LightPoint(const Vector& point, const Vector& normal, GO_FLOAT probability, GO_FLOAT Le) :
			point(point),
			normal(normal),
			probability(probability),
			Le(Le)
		{
		}
			
		const Vector point;
		const Vector normal;
		const GO_FLOAT probability;
		const GO_FLOAT Le;
	};
}
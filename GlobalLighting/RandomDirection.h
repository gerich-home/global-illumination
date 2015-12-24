#pragma once
#include "defines.h"
#include "Luminance.h"
#include "HitPoint.h"
#include "Vector.h"

namespace Engine
{
	class Luminance;
	class Vector;
	class HitPoint;

	class RandomDirection
	{
	public:
		RandomDirection():
			hp(NULL)
		{

		}

		RandomDirection(const Luminance& factor, const HitPoint* hp, const Vector& direction):
			factor(factor),
			hp(hp),
			direction(direction)
		{

		}

		const Luminance factor;
		const HitPoint* hp;
		const Vector direction;
	};
}
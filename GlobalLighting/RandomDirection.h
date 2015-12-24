#pragma once
#include "defines.h"
#include "Luminance.h"
#include "Vector.h"

namespace Engine
{
	class Luminance;
	class Vector;

	class RandomDirection
	{
	public:
		RandomDirection()
		{

		}

		RandomDirection(const Luminance& factor, const Vector& direction):
			factor(factor),
			direction(direction)
		{

		}

		const Luminance factor;
		const Vector direction;
	};
}
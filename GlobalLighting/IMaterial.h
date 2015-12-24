#pragma once
#include "defines.h"
#include "Vector.h"
#include "RandomDirection.h"

namespace Engine
{
	class Vector;
	class Luminance;
	class RandomDirection;

	class IMaterial
	{
	public:
		virtual const Luminance BRDF(const Vector& direction, const Vector& ndirection, const Vector& normal) const = 0;
		virtual const RandomDirection SampleDirection(const Vector& direction, const Vector& normal, GO_FLOAT ksi) const = 0;
	};
}
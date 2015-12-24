#pragma once
#include "defines.h"
#include "Vector.h"
#include "RandomDirection.h"
#include "IShape.h"

namespace Engine
{
	class Vector;
	class IShape;
	class Luminance;
	class RandomDirection;

	class IMaterial
	{
	public:
		virtual const Luminance BRDF(const Vector& direction, const Vector& ndirection, const Vector& normal) const = 0;
		virtual const RandomDirection SampleDirection(const Vector& direction, const Vector& point, const Vector& normal, const IShape& scene, GO_FLOAT absorption) const = 0;
	};
}
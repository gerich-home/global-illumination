#pragma once

#include "Luminance.h"
#include "IMaterial.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Engine;

namespace Materials
{
	class IdealMirrorMaterial: public IMaterial
	{
	public:
		IdealMirrorMaterial(GO_FLOAT rs[]) :
			rs(rs)
		{
		}

		const Luminance BRDF(const Vector& direction, const Vector& ndirection, const Vector& normal) const
		{
			return Luminance();
		}

		const RandomDirection SampleDirection(const Vector& direction, const Vector& normal, GO_FLOAT ksi) const
		{
			const Vector R = direction - 2 * normal.DotProduct(direction) * normal;

			return RandomDirection(rs, R);
		}

	private:
		const Luminance rs; //koefficient specular reflection
	};
}
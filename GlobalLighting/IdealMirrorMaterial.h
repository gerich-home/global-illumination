#pragma once

#include "Luminance.h"
#include "IMaterial.h"

#include <stdlib.h>
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

		const RandomDirection SampleDirection(const Vector& direction, const Vector& point, const Vector& normal, const IShape& scene, GO_FLOAT absorption) const
		{	
			GO_FLOAT ksi = (GO_FLOAT) rand() / RAND_MAX;

			if(ksi < absorption)
				return RandomDirection();
			
			const Vector R = direction - 2 * normal.DotProduct(direction) * normal;
			const HitPoint* nhp = scene.Intersection(point, R);
			
			if(nhp)
				return RandomDirection(rs / (1 - absorption), nhp, R);

			return RandomDirection();
		}

	private:
		const Luminance rs; //koefficient specular reflection
	};
}
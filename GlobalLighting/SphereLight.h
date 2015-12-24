#pragma once

#include "ILightSource.h"

namespace Lights
{
	using namespace Engine;

	class Sphere : public ILightSource
	{
	public:
		Sphere(const Vector& center, GO_FLOAT r, const Luminance& Le);

		virtual const LightPoint SampleLightPoint(const HitPoint& hitPoint) const;

	private:
		const GO_FLOAT r;
		const GO_FLOAT probability;
		const Vector center;
		const Luminance Le;
	};
}

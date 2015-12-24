#pragma once

#include "ILightSource.h"

namespace Lights
{
	using namespace Engine;

	class Square: public ILightSource
	{
	public:
		Square(const Vector a, const Vector b, const Vector c, const Luminance& Le);

		virtual const LightPoint SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const;

	private:
		const Vector a;
		const Vector ba;
		const Vector ca;
		const Vector normal;
		const GO_FLOAT probability;
		const Luminance Le;
	};
}
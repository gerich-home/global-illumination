#pragma once

#include "ILightSource.h"

namespace Lights
{
	using namespace Engine;

	class Triangle: public ILightSource
	{
	public:
		Triangle(const Vector a, const Vector b, const Vector c, const Luminance& le);

		virtual const LightPoint SampleLightPoint(const Vector& point) const;
		virtual void EmitPhotons(int nphotons, Photon photons[]) const;
		virtual Luminance Le() const;

	private:
		const GO_FLOAT probability;
		const Vector ba;
		const Vector ca;
		const Vector a;
		const Vector normal;
		const Luminance le;
	};
}
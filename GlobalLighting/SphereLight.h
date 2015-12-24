#pragma once

#include "ILightSource.h"

namespace Lights
{
	using namespace Engine;

	class Sphere : public ILightSource
	{
	public:
		Sphere(const Vector& center, GO_FLOAT r, const Luminance& le);

		virtual const LightPoint SampleLightPoint(const Vector& point) const;
		virtual void EmitPhotons(int nphotons, Photon photons[]) const;
		virtual Luminance Le() const;

	private:
		const GO_FLOAT r;
		const GO_FLOAT probability;
		const Vector center;
		const Luminance le;
	};
}

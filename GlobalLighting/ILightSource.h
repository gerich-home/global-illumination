#pragma once

#include "LightPoint.h"
#include "Vector.h"
#include "Photon.h"

namespace Engine
{
	class LightPoint;
	class Vector;
	class Photon;

	class ILightSource
	{
	public:
		virtual const LightPoint SampleLightPoint(const Vector& point) const = 0;
		virtual void EmitPhotons(int nphotons, Photon photons[]) const = 0;
		virtual Luminance Le() const = 0;
	};
}


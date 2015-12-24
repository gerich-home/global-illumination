#pragma once

#include "ILightSource.h"

namespace Lights
{
	using namespace Engine;

	class CompositeLightSource : public ILightSource
	{
	public:
		CompositeLightSource(int nlights, const ILightSource* lights[]);
		CompositeLightSource(int nlights, const ILightSource* lights[], GO_FLOAT probabilities[]);
		~CompositeLightSource();

		virtual const LightPoint SampleLightPoint(const Vector& point) const;
		virtual void EmitPhotons(int nphotons, Photon photons[]) const;
		virtual Luminance Le() const;

	private:
		const ILightSource** lights;
		GO_FLOAT* probabilities;
		int nlights;
	};
}
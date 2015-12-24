#pragma once

#include "LightPoint.h"
#include "HitPoint.h"

namespace Engine
{
	class ILightSource
	{
	public:
		virtual const LightPoint SampleLightPoint(const HitPoint& hitPoint) const = 0;
	};
}


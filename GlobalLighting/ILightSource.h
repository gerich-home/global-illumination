#pragma once

#include "LightPoint.h"
#include "Vector.h"

namespace Engine
{
	class LightPoint;
	class Vector;

	class ILightSource
	{
	public:
		virtual const LightPoint SampleLightPoint(const Vector& point) const = 0;
	};
}


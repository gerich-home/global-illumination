#pragma once

#include "HitPoint.h"
#include "IShape.h"
#include "ILightSource.h"

namespace Engine
{
	class Vector;
	class HitPoint;
	class IShape;
	class ILightSource;

	class IEngine
	{
	public:
		virtual Luminance L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape& scene, const ILightSource& lights) const = 0;
	};
}
#pragma once

#include "IEngine.h"

namespace Engine
{
	class Vector;
	class Luminance;
	class IEngine;
	class ILightSource;
	class IShape;

	class SimpleTracing: public IEngine
	{
	public:
		virtual Luminance L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape& scene, const ILightSource& lights) const;
	};
}
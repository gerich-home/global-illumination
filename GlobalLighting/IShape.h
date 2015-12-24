#pragma once

#include "HitPoint.h"

namespace Engine
{
	class Vector;
	class HitPoint;

	class IShape
	{
	public:
		virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const = 0;
	};
}

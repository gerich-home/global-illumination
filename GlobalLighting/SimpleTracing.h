#pragma once

#include "IEngine.h"

namespace Engine
{
	class SimpleTracing: public IEngine
	{
	public:
		SimpleTracing();
		~SimpleTracing();
		virtual Luminance L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape* scene, const ILightSource* lights);
		
	private:
		Vector Transform(const Vector& axis, const Vector& direction) const;
	};
}
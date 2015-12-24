#pragma once

#include "Defines.h"
#include "Vector.h"
#include "Material.h"

namespace Engine
{
	class HitPoint
	{
	public:
		HitPoint(GO_FLOAT t, const Vector& normal, const Material* material) :
			t(t),
			normal(normal),
			material(material)
		{
		}

		GO_FLOAT t;
		const Vector normal;
		const Material* material;
	};
}
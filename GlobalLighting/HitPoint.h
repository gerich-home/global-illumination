#pragma once

#include "Defines.h"
#include "Vector.h"
#include "IMaterial.h"

namespace Engine
{
	class Vector;
	class IMaterial;

	class HitPoint
	{
	public:
		HitPoint(GO_FLOAT t, const Vector& normal, const IMaterial* material) :
			t(t),
			normal(normal),
			material(material)
		{
		}

		GO_FLOAT t;
		Vector normal;
		const IMaterial* material;
	};
}
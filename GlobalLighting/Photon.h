#pragma once

#include "Defines.h"
#include "Vector.h"

namespace Engine
{
	class Vector;

	class Photon
	{
	public:
		Photon(const Vector& point, const Vector& normal, const Vector& direction, GO_FLOAT energy) :
			point(point),
			normal(normal),
			direction(direction),
			energy(energy)
		{
		}
			
		Vector point;
		Vector normal;
		Vector direction;
		GO_FLOAT energy;
	};
}
#pragma once

#include "Defines.h"
#include "Vector.h"
#include "Luminance.h"

namespace Engine
{
	class Vector;
	class Luminance;

	class Photon
	{
	public:
		Photon()
		{
		}

		Photon(const Vector& point, const Vector& normal, const Vector& direction, const Luminance& energy) :
			point(point),
			normal(normal),
			direction(direction),
			energy(energy)
		{
		}
			
		Vector point;
		Vector normal;
		Vector direction;
		Luminance energy;
	};
}
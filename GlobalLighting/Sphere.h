#pragma once

#include "IShape.h"

namespace Shapes
{
	using namespace Engine;

	class Sphere : public IShape
	{
	public:
		Sphere(const Vector& center, GO_FLOAT r, const IMaterial* material);
	
		virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

	private:
		const GO_FLOAT r2;
		const GO_FLOAT rinv;
		const Vector center;
		const IMaterial* material;
	};
}
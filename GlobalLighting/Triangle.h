#pragma once

#include "IShape.h"

namespace Shapes
{
	using namespace Engine;

	class Triangle: public IShape
	{
	public:
		Triangle(const Vector a, const Vector b, const Vector c, const IMaterial* material);

		virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

	private:
		const Vector normal;
		const Vector n;
		const Vector ba;
		const Vector ca;
		const Vector a;
		const IMaterial* material;
	};
}
#pragma once

#include "IShape.h"
#include "ITexturedMaterial.h"

namespace Shapes
{
	using namespace Engine;

	class Square: public IShape
	{
	public:
		Square(const Vector a, const Vector b, const Vector c, const ITexturedMaterial* material);
		Square(const Vector a, const Vector b, const Vector c, const IMaterial* material);

		virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

	private:
		const Vector a;
		const Vector ba;
		const Vector ca;
		const Vector normal;
		const Vector n;
		const ITexturedMaterial* material;
	};
}

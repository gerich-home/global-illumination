#pragma once

#include "IShape.h"

namespace Shapes
{
	using namespace Engine;

	class Plane : public IShape
	{
	public:
		Plane(const Vector& normal, GO_FLOAT d, const IMaterial* material);
		Plane(const Vector& a, const Vector& b, const Vector& A, const IMaterial* material);
		Plane(GO_FLOAT a, GO_FLOAT b, GO_FLOAT c, GO_FLOAT d, const IMaterial* material);

		virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

	private:
		GO_FLOAT d;
		const Vector normal;
		const Vector A;
		const IMaterial* material;
	};
};
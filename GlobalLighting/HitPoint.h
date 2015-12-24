#pragma once
#include "Vector.h"
#include "Material.h"

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
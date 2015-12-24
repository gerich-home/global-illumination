#pragma once

#include "IShape.h"

namespace Shapes
{
	using namespace Engine;

	class Scene : public IShape
	{
	public:
		Scene(int nshapes, const IShape* shapes[]);
		~Scene();
	
		virtual const HitPoint* Intersection(const Vector& start, const Vector& direction) const;

	private:
		const IShape** shapes;
		int nshapes;
	};
}
#pragma once

#include "IEngine.h"
#include "Luminance.h"

namespace Engine
{
	class Vector;
	class Luminance;
	class HitPoint;
	class IEngine;
	class ILightSource;
	class IShape;

	Luminance ColorAtPixel(GO_FLOAT px, GO_FLOAT py, int width, int height, GO_FLOAT cam_z, GO_FLOAT cam_size, const IShape& scene, const IShape& diffuse, const IShape& glossy, const ILightSource& lights, const IEngine& engine)
	{
		GO_FLOAT lx = cam_size * ((GO_FLOAT) 2 * px / width - 1);
		GO_FLOAT ly = cam_size * ((GO_FLOAT) (height - 2 * py) / width);
		const Vector start(lx, ly, 0);
		const Vector direction(Vector(lx, ly, cam_z).Normalize());
		const HitPoint* hp = scene.Intersection(start, direction);
	
		if(!hp)
		{
			return Luminance(0, 0, 0);
		}

		const Vector point(start + direction * hp->t);

		const Luminance& l = engine.L(*hp, point, direction, scene, diffuse, glossy, lights);
	
		delete hp;

		return l;
	}
}
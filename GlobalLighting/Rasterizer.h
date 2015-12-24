#pragma once

#include "IEngine.h"
#include "Luminance.h"

namespace Engine
{
	Luminance ColorAtPixel(GO_FLOAT px, GO_FLOAT py, int width, int height, GO_FLOAT cam, IShape* scene, ILightSource* lights, IEngine* engine)
	{
		GO_FLOAT lx = (GO_FLOAT) 2 * px / width - 1;
		GO_FLOAT ly = (GO_FLOAT) (height - 2 * py) / width;
		const Vector start(lx, ly, 0);
		const Vector direction(Vector(lx, ly, cam).Normalize());
		const HitPoint* hp = scene->Intersection(start, direction);
	
		if(!hp)
		{
			return Luminance(0, 0, 0);
		}

		const Vector point(start + direction * hp->t);
		GO_FLOAT r = engine->L(*hp, point, direction, scene, lights, L_R);
		GO_FLOAT g = engine->L(*hp, point, direction, scene, lights, L_G);
		GO_FLOAT b = engine->L(*hp, point, direction, scene, lights, L_B);
	
		delete hp;

		return Luminance(r, g, b);
	}
}
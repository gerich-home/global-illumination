#pragma once

#include "IEngine.h"
#include "PhotonMap.h"

	
class Engine::Vector;
class Engine::Luminance;
class Engine::IEngine;
class Engine::ILightSource;
class Engine::IShape;
class Engine::PhotonMap;

namespace Engines
{
	using namespace Engine;

	class PhotonMapTracing: public IEngine
	{
	public:
		PhotonMapTracing(const PhotonMap* globalMap, const PhotonMap* causticsMap) :
			globalMap(globalMap),
			causticsMap(causticsMap)
		{
		}

		virtual Luminance L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape& scene, const IShape& diffuse, const IShape& glossy, const ILightSource& lights) const;

	private:
		const PhotonMap* globalMap;
		const PhotonMap* causticsMap;
	};
}
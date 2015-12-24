#pragma once

#include "PhotonMap.h"
#include "IShape.h"
#include "ILightSource.h"

namespace Engine
{
	class PhotonMap;
	class IShape;
	class ILightSource;

	class IPhotonMapBuilder
	{
	public:
		virtual const PhotonMap BuildPhotonMap(const IShape& scene, const IShape& diffuse, const IShape& glossy, const ILightSource& lights) const = 0;
	};
}
#include "stdafx.h"

#include "CausticPhotonMapBuilder.h"

#define NPHOTONS 100
using namespace Engine;

/*
const PhotonMap PhotonMapBuilders::CausticPhotonMapBuilder::BuildPhotonMap(const IShape& scene, const IShape& diffuse, const IShape& glossy, const ILightSource& lights) const
{
	Photon* emitted_photons = new Photon[NPHOTONS];
	int nphotons = 0;

	lights.EmitPhotons(NPHOTONS, emitted_photons);

	for(int i = 0; i < NPHOTONS; i++)
	{
		const HitPoint* ghp = glossy.Intersection(emitted_photons[i].point, emitted_photons[i].direction);
		
		if(!ghp)
		{
			continue;
		}

		const HitPoint* dhp = diffuse.Intersection(emitted_photons[i].point, emitted_photons[i].direction);
		
		if(dhp)
		{
			delete ghp;
			delete dhp;
			continue;
		}

		ghp->material->

		if(i != nphotons)
		{
			emitted_photons[nphotons] = emitted_photons[i];
		}
		
		emitted_photons[nphotons].normal = 0;

		nphotons++;
	}

	const PhotonMap& pm = PhotonMap(nphotons, emitted_photons);
	delete[] emitted_photons;

	return pm;
}*/
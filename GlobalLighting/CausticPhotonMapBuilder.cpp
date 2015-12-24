#include "stdafx.h"

#include "CausticPhotonMapBuilder.h"

#define NPHOTONS 100
#define ABSOPTION 0.3

using namespace Engine;


const PhotonMap PhotonMapBuilders::CausticPhotonMapBuilder::BuildPhotonMap(const IShape& scene, const IShape& diffuse, const IShape& glossy, const ILightSource& lights) const
{
	PhotonMap pm = PhotonMap(NPHOTONS);
	Photon* emitted_photons = new Photon[NPHOTONS];

	lights.EmitPhotons(NPHOTONS, emitted_photons);

	for(int i = 0; i < NPHOTONS; i++)
	{
		bool isDiffuse = false;
		Photon current_photon = emitted_photons[i];
		
		const HitPoint* ghp = glossy.Intersection(current_photon.point, current_photon.direction);
		
		if(!ghp)
		{
			continue;
		}
		
		const HitPoint* dhp = diffuse.Intersection(current_photon.point, current_photon.direction);
		
		if(dhp)
		{
			if(dhp->t < ghp->t)
			{
				delete ghp;
				delete dhp;
				continue;
			}
			delete dhp;
		}

		bool isNotFull = true;

		while(isNotFull)
		{
			isDiffuse = false;

			const HitPoint* hp;

			const HitPoint* ghp = glossy.Intersection(current_photon.point, current_photon.direction);
			const HitPoint* dhp = diffuse.Intersection(current_photon.point, current_photon.direction);
		
			if(dhp)
			{
				if(ghp)
				{
					if(dhp->t <= ghp->t)
					{
						isDiffuse = true;
						delete ghp;
						hp = dhp;
					}
					else
					{
						delete dhp;
						hp = ghp;
					}
				}
				else
				{
					isDiffuse = true;
					delete ghp;
					hp = dhp;
				}
			}
			else
			{
				if(ghp)
				{
					hp = ghp;
				}
				else
				{
					break;
				}
			}

			GO_FLOAT ksi = (GO_FLOAT) rand() / (RAND_MAX + 1);

			if(ksi < ABSOPTION)
			{
				delete hp;
				break;
			}

			ksi = (ksi - ABSOPTION) / (1 - ABSOPTION);

			RandomDirection rndd = hp->material->SampleDirection(current_photon.direction, hp->normal, ksi);
		
			if(rndd.factor.colors[L_R] == 0 && rndd.factor.colors[L_G] == 0 && rndd.factor.colors[L_B] == 0)
			{
				delete hp;
				break;
			}
			

			current_photon.point += hp->t * current_photon.direction;
			current_photon.direction = rndd.direction;
			current_photon.energy *= rndd.factor / (1 - ABSOPTION);
			
			if(isDiffuse)
			{
				current_photon.normal = hp->normal;
				if(!pm.Add(current_photon))
				{
					isNotFull = false;
					break;
				}
			}
			
			delete hp;
		}
		
	}

	delete[] emitted_photons;

	pm.Build();
	return pm;
}
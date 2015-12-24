#include "StdAfx.h"
#include "PhotonMapTracing.h"

using namespace Engine;

#define SHADOW_RAYS 10
#define ABSOPTION 0.01
/*
Luminance Engines::PhotonMapTracing::L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape& scene, const IShape& diffuse, const IShape& glossy, const ILightSource& lights) const
{
	Luminance result;
	Luminance factor(1, 1, 1);
	Vector current_point = point;
	Vector current_direction = direction;
	HitPoint current_hp = hp;

	while(true)
	{
		Luminance direct;

		for(int i = 0; i < SHADOW_RAYS; i++)
		{	
			const LightPoint& lp = lights.SampleLightPoint(current_point);
			Vector ndirection = lp.point - current_point;

			GO_FLOAT cos_dir_normal = current_hp.normal.DotProduct(ndirection);

			if(cos_dir_normal < 0)
			{
				continue;
			}

			GO_FLOAT cos_dir_lnormal = -(ndirection.DotProduct(lp.normal));
			if(cos_dir_lnormal < 0)
			{
				continue;
			}

			GO_FLOAT l = ndirection.Length();
			if(l * l < GO_FLOAT_EPSILON)
			{
				continue;
			}

			GO_FLOAT linv = 1 / l;
			ndirection *= linv;
			cos_dir_normal *= linv;
			cos_dir_lnormal *= linv;

			const HitPoint* nhp = scene.Intersection(current_point, ndirection);

			if(nhp)
			{
				if(nhp->t > l - GO_FLOAT_EPSILON)
				{
					delete nhp;
				}
				else
				{
					delete nhp;
					continue;
				}
			}

			direct += lp.Le * current_hp.material->BRDF(current_direction, ndirection, current_hp.normal) * (cos_dir_normal * cos_dir_lnormal / (lp.probability * l * l));
		}
		direct /= SHADOW_RAYS;
		
		result += factor * direct;
		
		//Compute indirect luminancy
		
		const RandomDirection rndd = current_hp.material->SampleDirection(current_direction, current_point, current_hp.normal, scene, ABSOPTION);
			
		if(!rndd.hp)
		{
			break;
		}

		if(rndd.factor.colors[L_R] == 0 && rndd.factor.colors[L_G] == 0 && rndd.factor.colors[L_B] == 0)
		{
			delete rndd.hp;
			break;
		}

		factor *= rndd.factor;
		
		current_direction = rndd.direction;
		current_hp = *rndd.hp;
		current_point += current_direction * current_hp.t;

		delete rndd.hp;
	}

	return result;
}*/
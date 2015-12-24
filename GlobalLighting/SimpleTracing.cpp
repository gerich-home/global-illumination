#include "StdAfx.h"
#include "SimpleTracing.h"
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>


#define N 10
#define SHADOW_RAYS 10
#define MAX_DEEP 4

Engine::SimpleTracing::SimpleTracing(void)
{
	srand(time(0));
	currentDeep = 0;
}

Engine::SimpleTracing::~SimpleTracing(void)
{
}

GO_FLOAT Engine::SimpleTracing::L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape* scene, const ILightSource* lights, int colorIndex)
{
	GO_FLOAT direct = 0;
	GO_FLOAT indirect = 0;

	GO_FLOAT cos_dir_normal = -hp.normal.DotProduct(direction);

	currentDeep++;

	if(currentDeep < MAX_DEEP)
	{
		for(int i = 0; i < N; i++)
		{
			GO_FLOAT ksi = (GO_FLOAT) rand() / RAND_MAX;
			
			GO_FLOAT ax;
			GO_FLOAT ay;
			GO_FLOAT az;

			GO_FLOAT factor;
			Vector ndirection;

			if(ksi < hp.material->rd[colorIndex])
			{
				GO_FLOAT cosa = (GO_FLOAT) rand() / RAND_MAX;
				GO_FLOAT sina = sqrt(1 - cosa * cosa);
				GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

				ax = sina * cos(b);
				ay = sina * sin(b);
				az = cosa;

				if(az == 0)
				{
					continue;
				}
	
				Vector M1;
				Vector M2;
		
				if(hp.normal.z == 1)
				{
					M1 = Vector(1, 0, 0);
					M2 = Vector(0, 1, 0);
				}
				else if(hp.normal.z == -1)
				{
					M1 = Vector(-1, 0, 0);
					M2 = Vector(0, -1, 0);
				}
				else
				{
					M1 = hp.normal.CrossProduct(Vector(0, 0, 1)).Normalize();
					M2 = hp.normal.CrossProduct(M1);
				}
					
				ndirection = Vector(
					ax * M1.x + ay * M2.x + az * hp.normal.x,
					ax * M1.y + ay * M2.y + az * hp.normal.y,
					ax * M1.z + ay * M2.z + az * hp.normal.z);

				const HitPoint* nhp = scene->Intersection(point, ndirection);

				if(!nhp)
				{
					continue;
				}

				const Vector npoint(point + ndirection * nhp->t);

				indirect += 2 * L(*nhp, npoint, ndirection, scene, lights, colorIndex);
				
				delete nhp;
			}
			else if(ksi - hp.material->rd[colorIndex] < 2 * M_PI * hp.material->ks[colorIndex] / (hp.material->n[colorIndex] + 2))
			{
				GO_FLOAT cosa = (GO_FLOAT) rand() / RAND_MAX;
				GO_FLOAT sina = sqrt(1 - cosa * cosa);
				GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

				ax = sina * cos(b);
				ay = sina * sin(b);
				az = cosa;

				if(az == 0)
				{
					continue;
				}
	
				Vector M1;
				Vector M2;
		
				if(hp.normal.z == 1)
				{
					M1 = Vector(1, 0, 0);
					M2 = Vector(0, 1, 0);
				}
				else if(hp.normal.z == -1)
				{
					M1 = Vector(-1, 0, 0);
					M2 = Vector(0, -1, 0);
				}
				else
				{
					M1 = hp.normal.CrossProduct(Vector(0, 0, 1)).Normalize();
					M2 = hp.normal.CrossProduct(M1);
				}
					
				ndirection = Vector(
					ax * M1.x + ay * M2.x + az * hp.normal.x,
					ax * M1.y + ay * M2.y + az * hp.normal.y,
					ax * M1.z + ay * M2.z + az * hp.normal.z);

				const HitPoint* nhp = scene->Intersection(point, ndirection);

				if(!nhp)
				{
					continue;
				}

				const Vector npoint(point + ndirection * nhp->t);

				indirect += (hp.material->n[colorIndex] + 2) * pow(hp.normal.DotProduct((ndirection - direction).Normalize()), hp.material->n[colorIndex]) * L(*nhp, npoint, ndirection, scene, lights, colorIndex);
				
				delete nhp;
			}
		}


		indirect /= N;
	}

	
	for(int i = 0; i < SHADOW_RAYS; i++)
	{
		const LightPoint& lp = lights->SampleLightPoint(hp, colorIndex);
		Vector ndirection = lp.point - point;

		GO_FLOAT cos_dir_lnormal = ndirection.DotProduct(lp.normal);
		if(cos_dir_lnormal > 0)
		{
			continue;
		}

		GO_FLOAT l = ndirection.Length();
		if(l < GO_FLOAT_EPSILON)
		{
			continue;
		}
		ndirection /= l;
		cos_dir_lnormal /= l;

		const HitPoint* nhp = scene->Intersection(point, ndirection);

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

		GO_FLOAT brdf = hp.material->rd[colorIndex] / M_PI;
		if(hp.material->ks[colorIndex] > 0)
		{
			brdf += hp.material->ks[colorIndex] * pow(hp.normal.DotProduct((ndirection - direction).Normalize()), hp.material->n[colorIndex]);
		}

		direct -= lp.Le * brdf * cos_dir_normal * cos_dir_lnormal / (lp.probability * l * l);
				
	}

	direct /= SHADOW_RAYS;

	currentDeep--;
	return direct + indirect;
}
#include "StdAfx.h"
#include "SimpleTracing.h"
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Engine;
#define SHADOW_RAYS 3
#define MIN_ABSOPTION 0.01

SimpleTracing::SimpleTracing(void)
{
}

SimpleTracing::~SimpleTracing(void)
{
}

Luminance SimpleTracing::L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape* scene, const ILightSource* lights)
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
			const LightPoint& lp = lights->SampleLightPoint(current_hp);
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

			const HitPoint* nhp = scene->Intersection(current_point, ndirection);

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

			const Vector R = 2 * current_hp.normal.DotProduct(ndirection) * current_hp.normal - ndirection;
			const GO_FLOAT cosphi = -current_direction.DotProduct(R);
			
			Luminance BRDF = Luminance(current_hp.material->rd) / M_PI; 
			
			if(cosphi > 0 )
			{
				BRDF += Luminance(
					current_hp.material->rs[L_R] == 0 ? 0 : current_hp.material->rs[L_R] * (current_hp.material->n[L_R] + 2) * pow(cosphi, current_hp.material->n[L_R]),
					current_hp.material->rs[L_G] == 0 ? 0 : current_hp.material->rs[L_G] * (current_hp.material->n[L_G] + 2) * pow(cosphi, current_hp.material->n[L_G]),
					current_hp.material->rs[L_B] == 0 ? 0 : current_hp.material->rs[L_B] * (current_hp.material->n[L_B] + 2) * pow(cosphi, current_hp.material->n[L_B])
					) / (2 * M_PI);
			}

			direct += lp.Le * BRDF * (cos_dir_normal * cos_dir_lnormal / (lp.probability * l * l));
		}
		direct /= SHADOW_RAYS;
		
		result += factor * direct;
		

		//Compute indirect luminancy

		GO_FLOAT qd = (current_hp.material->rd[L_R] + current_hp.material->rd[L_G] + current_hp.material->rd[L_B]) / 3;
		GO_FLOAT qs = (current_hp.material->rs[L_R] + current_hp.material->rs[L_G] + current_hp.material->rs[L_B]) / 3;

		if(qd + qs + MIN_ABSOPTION > 1)
		{
			GO_FLOAT k = (1 - MIN_ABSOPTION) / (qd + qs);
			qd *= k;
			qs *= k;
		}

		GO_FLOAT ksi = (GO_FLOAT) rand() / RAND_MAX;

		if(ksi < qd)
		{
			GO_FLOAT cosa = (GO_FLOAT) rand() / RAND_MAX;
			GO_FLOAT sina = sqrt(1 - cosa * cosa);
			GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

			Vector ndirection = Transform(current_hp.normal, Vector(sina * cos(b), sina * sin(b), cosa));

			const HitPoint* nhp = scene->Intersection(current_point, ndirection);

			if(!nhp)
			{
				break;
			}

			const Vector npoint(current_point + ndirection * nhp->t);

			factor *= Luminance(current_hp.material->rd) / (2 * qd);

			current_direction = ndirection;
			current_hp = *nhp;
			current_point = npoint;

			delete nhp;
		}
		else if(ksi - qd < qs)
		{
			GO_FLOAT maxn = min(current_hp.material->n[L_R], min(current_hp.material->n[L_G], current_hp.material->n[L_B]));
		
			GO_FLOAT cosa = pow((GO_FLOAT) rand() / RAND_MAX, 1 / (maxn + 1));
			GO_FLOAT sina = sqrt(1 - cosa * cosa);
			GO_FLOAT b = 2 * M_PI * (GO_FLOAT) rand() / RAND_MAX;

			const Vector R = current_direction - 2 * current_hp.normal.DotProduct(current_direction) * current_hp.normal;
			const Vector ndirection = Transform(R, Vector(sina * cos(b), sina * sin(b), cosa));

			if(current_hp.normal.DotProduct(ndirection) <= 0)
			{
				break;
			}

			const HitPoint* nhp = scene->Intersection(current_point, ndirection);

			if(!nhp)
			{
				break;
			}

			const Vector npoint(current_point + ndirection * nhp->t);

			factor *= Luminance(
				current_hp.material->rs[L_R] == 0 ? 0 : current_hp.material->rs[L_R] * (current_hp.material->n[L_R] + 2) * pow(cosa, current_hp.material->n[L_R] - maxn),
				current_hp.material->rs[L_G] == 0 ? 0 : current_hp.material->rs[L_G] * (current_hp.material->n[L_G] + 2) * pow(cosa, current_hp.material->n[L_G] - maxn),
				current_hp.material->rs[L_B] == 0 ? 0 : current_hp.material->rs[L_B] * (current_hp.material->n[L_B] + 2) * pow(cosa, current_hp.material->n[L_B] - maxn)
				) * current_hp.normal.DotProduct(ndirection) / (qs * (maxn + 2));

			current_direction = ndirection;
			current_hp = *nhp;
			current_point = npoint;

			delete nhp;
		}
		else
		{
			break;
		}
	}

	return result;
}

Vector SimpleTracing::Transform(const Vector& axis, const Vector& direction) const
{
	Vector t = axis;
	Vector M1;
	Vector M2;

	if(abs(axis.x) < abs(axis.y))
	{
		if(abs(axis.x) < abs(axis.z))
			t.x = 1;
		else
			t.z = 1;
	}
	else
	{
		if(abs(axis.y) < abs(axis.z))
			t.y = 1;
		else
			t.z = 1;
	}
	
	M1 = axis.CrossProduct(t).Normalize();
	M2 = axis.CrossProduct(M1);
	

	return Vector(
		direction.x * M1.x + direction.y * M2.x + direction.z * axis.x,
		direction.x * M1.y + direction.y * M2.y + direction.z * axis.y,
		direction.x * M1.z + direction.y * M2.z + direction.z * axis.z);
}
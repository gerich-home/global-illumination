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
	srand(time(0));
}

SimpleTracing::~SimpleTracing(void)
{
}

Luminance SimpleTracing::L(const HitPoint& hp, const Vector& point, const Vector& direction, const IShape* scene, const ILightSource* lights)
{
	Luminance result;
	Luminance direct;
	Luminance factor(1, 1, 1);
	Vector current_point = point;
	Vector current_direction = direction;
	HitPoint current_hp = hp;

	while(true)
	{
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
			if(l < GO_FLOAT_EPSILON)
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

			const GO_FLOAT cosphi = current_hp.normal.DotProduct((ndirection - current_direction).Normalize());

			direct += lp.Le * (Luminance(current_hp.material->rd) / M_PI + Luminance(
				current_hp.material->ks[L_R] == 0 ? 0 : current_hp.material->ks[L_R] * pow(cosphi, current_hp.material->n[L_R]),
				current_hp.material->ks[L_G] == 0 ? 0 : current_hp.material->ks[L_G] * pow(cosphi, current_hp.material->n[L_G]),
				current_hp.material->ks[L_B] == 0 ? 0 : current_hp.material->ks[L_B] * pow(cosphi, current_hp.material->n[L_B])
				)) * (cos_dir_normal * cos_dir_lnormal / (lp.probability * l * l));
		}
		direct /= SHADOW_RAYS;
		
		result += factor * direct;

		//Compute indirect luminancy

		GO_FLOAT qd = (current_hp.material->rd[L_R] + current_hp.material->rd[L_G] + current_hp.material->rd[L_B]) / 3;
		GO_FLOAT qs = (current_hp.material->ks[L_R] + current_hp.material->ks[L_G] + current_hp.material->ks[L_B]) / 3;

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

			factor *= Luminance(current_hp.material->rd) / qd;

			delete nhp;
		}
		else if(ksi - qd < qs)
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

			const GO_FLOAT cosphi = current_hp.normal.DotProduct((ndirection - current_direction).Normalize());

			factor *= Luminance(
				current_hp.material->ks[L_R] == 0 ? 0 : current_hp.material->ks[L_R] * pow(cosphi, current_hp.material->n[L_R]),
				current_hp.material->ks[L_G] == 0 ? 0 : current_hp.material->ks[L_G] * pow(cosphi, current_hp.material->n[L_G]),
				current_hp.material->ks[L_B] == 0 ? 0 : current_hp.material->ks[L_B] * pow(cosphi, current_hp.material->n[L_B])
				) * (M_PI / (2 * qs));

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
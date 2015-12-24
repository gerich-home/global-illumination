#pragma once

#include "Luminance.h"
#include "IMaterial.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Engine;

namespace Materials
{
	class IdealRefractorMaterial: public IMaterial
	{
	public:
		IdealRefractorMaterial(GO_FLOAT rreflect[], GO_FLOAT rrefract[], GO_FLOAT refract) :
			rreflect(rreflect),
			rrefract(rrefract),
			refract(refract)
		{
		}

		const Luminance BRDF(const Vector& direction, const Vector& ndirection, const Vector& normal) const
		{
			GO_FLOAT cosa = -direction.DotProduct(normal);
			
			
			GO_FLOAT cosb = 1 - (1 - cosa * cosa) * refract * refract;
			if(cosb < 0)
				return Luminance();

			cosb = sqrt(cosb);

			Vector R;
			if(cosa > 0)
			{
				R = -cosb * normal + refract * (cosa * normal + direction);
			}
			else	
			{
				R = cosb * normal + refract * (cosa * normal + direction);
			}
			
			const GO_FLOAT cosphi = ndirection.DotProduct(R);
			int n = 1000;
			
			if(cosphi > 0 )
			{
				return Luminance(
					rrefract.colors[L_R] == 0 ? 0 : rrefract.colors[L_R] * (n + 2) * pow(cosphi, n),
					rrefract.colors[L_G] == 0 ? 0 : rrefract.colors[L_G] * (n + 2) * pow(cosphi, n),
					rrefract.colors[L_B] == 0 ? 0 : rrefract.colors[L_B] * (n + 2) * pow(cosphi, n)
					) / (2 * M_PI);
			}

			return Luminance();
		}

		const RandomDirection SampleDirection(const Vector& direction, const Vector& point, const Vector& normal, const IShape& scene, GO_FLOAT absorption) const
		{	
			GO_FLOAT qreflect = (rreflect.colors[L_R] + rreflect.colors[L_G] + rreflect.colors[L_B]) / 3;
			GO_FLOAT qrefract = (rrefract.colors[L_R] + rrefract.colors[L_G] + rrefract.colors[L_B]) / 3;

			if(qreflect + qrefract + absorption > 1)
			{
				GO_FLOAT k = (1 - absorption) / (qreflect + qrefract);
				qreflect *= k;
				qrefract *= k;
			}

			GO_FLOAT ksi = (GO_FLOAT) rand() / RAND_MAX;

			if(ksi < absorption)
				return RandomDirection();
			
			GO_FLOAT cosa = -direction.DotProduct(normal);
			
			if(ksi - absorption < qreflect)
			{
				const Vector R = direction + 2 * cosa * normal;

				const HitPoint* nhp = scene.Intersection(point, R);			
				if(nhp)
					return RandomDirection(rreflect / qreflect, nhp, R);	
			}
			else
			{

				GO_FLOAT cosb = 1 - (1 - cosa * cosa) * refract * refract;
				if(cosb < 0)
					return RandomDirection();

				cosb = sqrt(cosb);

				Vector R;
				if(cosa > 0)
				{
					R = -cosb * normal + refract * (cosa * normal + direction);
				}
				else	
				{
					R = cosb * normal + refract * (cosa * normal + direction);
				}
				
				const HitPoint* nhp = scene.Intersection(point, R);			
				if(nhp)
					return RandomDirection(rrefract / qrefract, nhp, R);
			}

			return RandomDirection();
		}

	private:
		const Luminance rreflect;
		const Luminance rrefract;
		const GO_FLOAT refract;
	};
}
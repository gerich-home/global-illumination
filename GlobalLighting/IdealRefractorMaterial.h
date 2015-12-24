#pragma once

#include "Luminance.h"
#include "IMaterial.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Engine;

namespace Materials
{
	class IdealRefractorMaterial: public IMaterial
	{
	public:
		IdealRefractorMaterial(GO_FLOAT rd[], GO_FLOAT refract) :
			rd(rd),
			refract(refract)
		{
		}

		const Luminance BRDF(const Vector& direction, const Vector& ndirection, const Vector& normal) const
		{
			int n = 500;

			GO_FLOAT cosa = -direction.DotProduct(normal);
			GO_FLOAT factor = refract;
			if(cosa < 0)
			{
				factor = 1 / factor;
			}

			GO_FLOAT cosb = 1 - (1 - cosa * cosa) * factor * factor;

			if(cosb < 0)
			{
				const Vector R = direction + 2 * cosa * normal;
				
				const GO_FLOAT cosphi = ndirection.DotProduct(R);
			
				if(cosphi > 0)
				{
					return Luminance(
						rd.colors[L_R] == 0 ? 0 : rd.colors[L_R] * (n + 2) * pow(cosphi, n),
						rd.colors[L_G] == 0 ? 0 : rd.colors[L_G] * (n + 2) * pow(cosphi, n),
						rd.colors[L_B] == 0 ? 0 : rd.colors[L_B] * (n + 2) * pow(cosphi, n)
						) / (2 * M_PI);	
				}
				else
				{
					return Luminance();
				}
			}

			cosb = sqrt(cosb);

			GO_FLOAT cosabs = abs(cosa);
			GO_FLOAT Rs = (factor * cosabs - cosb) / (factor * cosabs  + cosb);
			Rs *= Rs;

			GO_FLOAT Rt = (factor * cosb - cosabs) / (factor * cosb + cosabs);
			Rt *= Rt;
			
			GO_FLOAT qreflect = (Rs + Rt) / 2;
			
			Luminance result;
			
			{
				const Vector R = direction + 2 * cosa * normal;
				const GO_FLOAT cosphi = ndirection.DotProduct(R);
			
				if(cosphi > 0)
				{
					result = qreflect * Luminance(
						rd.colors[L_R] == 0 ? 0 : rd.colors[L_R] * (n + 2) * pow(cosphi, n),
						rd.colors[L_G] == 0 ? 0 : rd.colors[L_G] * (n + 2) * pow(cosphi, n),
						rd.colors[L_B] == 0 ? 0 : rd.colors[L_B] * (n + 2) * pow(cosphi, n)
						) / (2 * M_PI);
				}
			}

			{
				Vector R;
				if(cosa > 0)
				{
					R = -cosb * normal + factor * (cosa * normal + direction);
				}
				else	
				{
					R = cosb * normal + factor * (cosa * normal + direction);
				}
				
				const GO_FLOAT cosphi = ndirection.DotProduct(R);
			
				if(cosphi > 0)
				{
					result = (1 - qreflect) * Luminance(
						rd.colors[L_R] == 0 ? 0 : rd.colors[L_R] * (n + 2) * pow(cosphi, n),
						rd.colors[L_G] == 0 ? 0 : rd.colors[L_G] * (n + 2) * pow(cosphi, n),
						rd.colors[L_B] == 0 ? 0 : rd.colors[L_B] * (n + 2) * pow(cosphi, n)
						) / (2 * M_PI);
				}
			}

			return result;
		}

		const RandomDirection SampleDirection(const Vector& direction, const Vector& normal, GO_FLOAT ksi) const
		{	
			GO_FLOAT cosa = -direction.DotProduct(normal);
			GO_FLOAT factor = refract;
			if(cosa < 0)
			{
				factor = 1 / factor;
			}

			GO_FLOAT cosb = 1 - (1 - cosa * cosa) * factor * factor;

			if(cosb < 0)
			{
				const Vector R = direction + 2 * cosa * normal;
				return RandomDirection(rd, R);	
			}

			cosb = sqrt(cosb);

			GO_FLOAT cosabs = abs(cosa);
			GO_FLOAT Rs = (factor * cosabs - cosb) / (factor * cosabs  + cosb);
			Rs *= Rs;

			GO_FLOAT Rt = (factor * cosb - cosabs) / (factor * cosb + cosabs);
			Rt *= Rt;
			
			GO_FLOAT qreflect = (Rs + Rt) / 2;
			
			if(ksi < qreflect)
			{
				const Vector R = direction + 2 * cosa * normal;
				return RandomDirection(rd, R);	
			}
			else
			{
				Vector R;
				if(cosa > 0)
				{
					R = -cosb * normal + factor * (cosa * normal + direction);
				}
				else
				{
					R = cosb * normal + factor * (cosa * normal + direction);
				}
				
				return RandomDirection(rd, R);
			}
		}

	private:
		const Luminance rd;
		const GO_FLOAT refract;
	};
}
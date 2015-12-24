#include "StdAfx.h"
#include "SimpleTracing.h"
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>


#define N 40
#define MAX_DEEP 4

SimpleTracing::SimpleTracing(void)
{
	srand(time(0));
	currentDeep = 0;
}

SimpleTracing::~SimpleTracing(void)
{
}

GO_FLOAT SimpleTracing::L(const HitPoint* hp, const Vector& point, const Vector& direction, const IShape* shape, int colorIndex)
{
	GO_FLOAT result = 0;

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

			if(ksi < hp->material->rd[colorIndex])
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
		
				if(hp->normal.z == 1)
				{
					M1 = Vector(1, 0, 0);
					M2 = Vector(0, 1, 0);
				}
				else if(hp->normal.z == -1)
				{
					M1 = Vector(-1, 0, 0);
					M2 = Vector(0, -1, 0);
				}
				else
				{
					M1 = hp->normal.CrossProduct(Vector(0, 0, 1)).Normalize();
					M2 = hp->normal.CrossProduct(M1);
				}
					
				ndirection = Vector(
					ax * M1.x + ay * M2.x + az * hp->normal.x,
					ax * M1.y + ay * M2.y + az * hp->normal.y,
					ax * M1.z + ay * M2.z + az * hp->normal.z);

				const HitPoint* nhp = shape->Intersection(point, ndirection);

				if(!nhp)
				{
					continue;
				}

				const Vector npoint(point + ndirection * nhp->t);

				result += 2 * L(nhp, npoint, ndirection, shape, colorIndex);
				
				delete nhp;
			}
			else if(ksi - hp->material->rd[colorIndex] < 2 * M_PI * hp->material->ks[colorIndex] / (hp->material->n[colorIndex] + 2))
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
		
				if(hp->normal.z == 1)
				{
					M1 = Vector(1, 0, 0);
					M2 = Vector(0, 1, 0);
				}
				else if(hp->normal.z == -1)
				{
					M1 = Vector(-1, 0, 0);
					M2 = Vector(0, -1, 0);
				}
				else
				{
					M1 = hp->normal.CrossProduct(Vector(0, 0, 1)).Normalize();
					M2 = hp->normal.CrossProduct(M1);
				}
					
				ndirection = Vector(
					ax * M1.x + ay * M2.x + az * hp->normal.x,
					ax * M1.y + ay * M2.y + az * hp->normal.y,
					ax * M1.z + ay * M2.z + az * hp->normal.z);

				const HitPoint* nhp = shape->Intersection(point, ndirection);

				if(!nhp)
				{
					continue;
				}

				const Vector npoint(point + ndirection * nhp->t);

				result += (hp->material->n[colorIndex] + 2) * pow(hp->normal.DotProduct((ndirection - direction).Normalize()), hp->material->n[colorIndex]) * L(nhp, npoint, ndirection, shape, colorIndex);
				
				delete nhp;
			}
		}

		result /= N;
	}

	//result += hp->material->Le[colorIndex] * (-direction.DotProduct(hp->normal));

	currentDeep--;
	return result;
}
#include "StdAfx.h"
#include "Scene.h"

using namespace Engine;

Shapes::Scene::Scene(int nshapes, const IShape* shapes[]) :
	nshapes(nshapes)
{
	this->shapes = new const IShape*[nshapes];

	for(int i = 0; i < nshapes; i++)
	{
		this->shapes[i] = shapes[i];
	}
}

Shapes::Scene::~Scene()
{
	delete[] shapes;
}

const HitPoint* Shapes::Scene::Intersection(const Vector& start, const Vector& direction) const
{
	const HitPoint* bestHitPoint = NULL;
	const HitPoint* hitPoint;

	for(int i = 0; i < nshapes; i++)
	{
		hitPoint = shapes[i]->Intersection(start, direction);
		if(hitPoint != NULL && (bestHitPoint ? hitPoint->t < bestHitPoint->t : TRUE))
		{
			delete bestHitPoint;
			bestHitPoint = hitPoint;
		}
		else
		{
			delete hitPoint;
		}
	}

	return bestHitPoint;
}

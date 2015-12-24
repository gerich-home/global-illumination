#include "StdAfx.h"
#include "CompositeLightSource.h"

CompositeLightSource::CompositeLightSource(int nlights, const ILightSource* lights[], GO_FLOAT probabilities[]) :
	nlights(nlights)
{
	this->lights = new const ILightSource*[nlights];
	this->probabilities = new GO_FLOAT[nlights];
	
	GO_FLOAT sum = 0;

	for(int i = 0; i < nlights; i++)
	{
		this->lights[i] = lights[i];
		this->probabilities[i] = probabilities[i];
		sum += probabilities[i];
	}
	
	sum = 1 / sum;
	for(int i = 0; i < nlights; i++)
	{
		this->probabilities[i] *= sum;
	}
}

CompositeLightSource::~CompositeLightSource()
{
	delete[] lights;
	delete[] probabilities;
}

const LightPoint CompositeLightSource::SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const
{
	GO_FLOAT ksi = (GO_FLOAT) rand() / RAND_MAX;

	for(int i = 0; i < nlights; i++)
	{
		if(ksi < probabilities[i])
		{
			const LightPoint& lp = lights[i]->SampleLightPoint(hitPoint, colorIndex);
			return LightPoint(lp.point, probabilities[i] * lp.probability, lp.Le);
		}
		else
		{
			ksi -= probabilities[i];
		}
	}
}
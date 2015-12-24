#include "StdAfx.h"
#include "CompositeLightSource.h"

using namespace Engine;

Lights::CompositeLightSource::CompositeLightSource(int nlights, const ILightSource* lights[]) :
	nlights(nlights)
{
	this->lights = new const ILightSource*[nlights];
	this->probabilities = new GO_FLOAT[nlights];
	
	GO_FLOAT p = 1 / (GO_FLOAT)nlights;

	for(int i = 0; i < nlights; i++)
	{
		this->lights[i] = lights[i];
		this->probabilities[i] = p;
	}
}

Lights::CompositeLightSource::CompositeLightSource(int nlights, const ILightSource* lights[], GO_FLOAT probabilities[]) :
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

Lights::CompositeLightSource::~CompositeLightSource()
{
	delete[] lights;
	delete[] probabilities;
}

const LightPoint Lights::CompositeLightSource::SampleLightPoint(const Vector& point) const
{
	GO_FLOAT ksi = (GO_FLOAT) rand() / (RAND_MAX + 1);

	for(int i = 0; i < nlights; i++)
	{
		if(ksi < probabilities[i])
		{
			const LightPoint& lp = lights[i]->SampleLightPoint(point);
			return LightPoint(lp.point, lp.normal, probabilities[i] * lp.probability, lp.Le);
		}
		else
		{
			ksi -= probabilities[i];
		}
	}
}

void Lights::CompositeLightSource::EmitPhotons(int nphotons, Photon photons[]) const
{
	GO_FLOAT* energy = new GO_FLOAT[nlights];
	
	Luminance totalLe;
	for(int i = 0; i < nlights; i++)
	{
		const Luminance lei = lights[i]->Le();
		totalLe += lei;
		energy[i] = (lei.r() + lei.g() + lei.b()) / 3;
	}

	GO_FLOAT factor = nphotons * 3 / (totalLe.r() + totalLe.g() + totalLe.b());

	int* nphotonsPerLight = new int[nlights];
	int remainedPhotons = 0;

	for(int i = 0; i < nlights; i++)
	{
		nphotonsPerLight[i] = factor * energy[i];
		remainedPhotons += nphotonsPerLight[i];
	}
	
	delete[] energy;

	remainedPhotons = nphotons - remainedPhotons;
	
	for(int i = 0; i < remainedPhotons; i++)
	{
		nphotonsPerLight[i]++;
	}

	int offset = 0;

	for(int i = 0; i < nlights; i++)
	{
		lights[i]->EmitPhotons(nphotonsPerLight[i], photons + offset);
		offset += nphotonsPerLight[i];
	}

	delete[] nphotonsPerLight;
}

Luminance Lights::CompositeLightSource::Le() const
{
	Luminance Le;

	for(int i = 0; i < nlights; i++)
	{
		Le += lights[i]->Le();
	}
	
	return Le;
}

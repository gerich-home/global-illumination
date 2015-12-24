#pragma once
#include "ILightSource.h"

class CompositeLightSource : public ILightSource
{
public:
	CompositeLightSource(int nlights, const ILightSource* lights[]);
	CompositeLightSource(int nlights, const ILightSource* lights[], GO_FLOAT probabilities[]);
	~CompositeLightSource();

	virtual const LightPoint SampleLightPoint(const HitPoint& hitPoint, int colorIndex) const;

private:
	const ILightSource** lights;
	GO_FLOAT* probabilities;
	int nlights;
};


#pragma once
#include "IEngine.h"
class SimpleTracing: public IEngine
{
public:
	SimpleTracing();
	~SimpleTracing();
	virtual GO_FLOAT L(const HitPoint* hp, const Vector& point, const Vector& direction, const IShape* shape, int colorIndex);

private:
	int currentDeep;
};


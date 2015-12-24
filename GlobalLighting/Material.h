#pragma once
#include "Luminance.h"

class Material
{
public:
	Material(GO_FLOAT rd[], GO_FLOAT ks[], int n[])
	{
		this->rd[L_R] = rd[L_R];
		this->rd[L_G] = rd[L_G];
		this->rd[L_B] = rd[L_B];

		this->ks[L_R] = ks[L_R];
		this->ks[L_G] = ks[L_G];
		this->ks[L_B] = ks[L_B];

		this->n[L_R] = n[L_R];
		this->n[L_G] = n[L_G];
		this->n[L_B] = n[L_B];
	}

	GO_FLOAT rd[3]; //koefficient diffuse reflection
	GO_FLOAT ks[3]; //koefficient specular reflection
	int n[3];
};
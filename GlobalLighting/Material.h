#pragma once

#include "Luminance.h"

namespace Engine
{
	class Material
	{
	public:
		Material(GO_FLOAT rd[], GO_FLOAT rs[], int n[])
		{
			this->rd[L_R] = rd[L_R];
			this->rd[L_G] = rd[L_G];
			this->rd[L_B] = rd[L_B];

			this->rs[L_R] = rs[L_R];
			this->rs[L_G] = rs[L_G];
			this->rs[L_B] = rs[L_B];

			this->n[L_R] = n[L_R];
			this->n[L_G] = n[L_G];
			this->n[L_B] = n[L_B];
		}

		GO_FLOAT rd[3]; //koefficient diffuse reflection
		GO_FLOAT rs[3]; //koefficient specular reflection
		int n[3];
	};
}
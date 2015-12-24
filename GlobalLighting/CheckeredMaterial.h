#pragma once

#include "ITexturedMaterial.h"
#include "IMaterial.h"

using namespace Engine;

namespace Materials
{
	class CheckeredMaterial: public ITexturedMaterial
	{
	public:
		CheckeredMaterial(int N, int M, const IMaterial* m1, const IMaterial* m2) :
			N(N),
			M(M),
			m1(m1),
			m2(m2)
		{
		}

		virtual const IMaterial* MaterialAt(GO_FLOAT t1, GO_FLOAT t2) const
		{
			if(((int)(t1 * N) + (int)(t2 * M)) % 2)
			{
				return m1;
			}

			return m2;
		}

	private:
		const int N;
		const int M;
		const IMaterial* m1;
		const IMaterial* m2;
	};
}
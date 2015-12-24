#pragma once

#include "ITexturedMaterial.h"
#include "IMaterial.h"

using namespace Engine;

namespace Materials
{
	class TexturedMaterialAdapter: public ITexturedMaterial
	{
	public:
		TexturedMaterialAdapter(const IMaterial* m) :
			m(m)
		{
		}

		virtual const IMaterial* MaterialAt(GO_FLOAT t1, GO_FLOAT t2) const
		{
			return m;
		}

	private:
		const IMaterial* m;
	};
}
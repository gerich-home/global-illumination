#pragma once
#include "defines.h"
#include "IMaterial.h"

namespace Engine
{
	class IMaterial;

	class ITexturedMaterial
	{
	public:
		virtual const IMaterial* MaterialAt(GO_FLOAT t1, GO_FLOAT t2) const = 0;
	};
}
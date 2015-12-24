#pragma once

#include "Defines.h"
#include "Photon.h"
#include "Vector.h"

namespace Engine
{
	class Photon;
	class PhotonMapNode;

	class ParamsForFind
	{
	public:
		ParamsForFind(const Vector& x, int count, Photon** result):
			x(x),
			count(count),
			result(result)
		{
		}
		
		~ParamsForFind()
		{
		}

		const Vector x;
		int count; 
		int currentCount; 
		Photon** result;
		GO_FLOAT* resultDistances;
	};

	class PhotonMap
	{
	public:
		PhotonMap(int nphotons, Photon* photons);
		~PhotonMap();

		void FindNearest(const Vector& x, int count, Photon** result) const;

	private:
		void QSort(int left, int right, short axis);
		PhotonMapNode* CreateSubTree(int left, int right);
		void GoDown(GO_FLOAT max[3], GO_FLOAT min[3], PhotonMapNode* node, const ParamsForFind& paramsForFind) const;
		PhotonMapNode* root;
		Photon* photons;
		int* indexes[3];
	};
}
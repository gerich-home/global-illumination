#pragma once

#include "Defines.h"
#include "Photon.h"
#include "Vector.h"

namespace Engine
{
	class Photon;
	class PhotonMapNode;

	class ParamsForFind;

	class PhotonMap
	{
	public:
		PhotonMap(int nphotons, Photon* photons);
		~PhotonMap();

		GO_FLOAT FindNearest(const Vector& x, int count, Photon** result) const;

	private:
		void QSort(int left, int right, short axis);
		PhotonMapNode* CreateSubTree(int left, int right);
		void GoDown(PhotonMapNode* node, ParamsForFind& paramsForFind) const;
		PhotonMapNode* root;
		Photon* photons;
		int* indexes[3];
	};
}
#pragma once

#include "Defines.h"
#include "Photon.h"
#include "Vector.h"

namespace Engine
{
	class Photon;
	class PhotonMapNode;

	class PhotonMap
	{
	public:
		PhotonMap(int nphotons, const Photon photons[]);
		~PhotonMap();

		const Photon* FindNearest(const Vector& x, int count) const;

	private:
		void QSortX(int left, int right);
		void QSortY(int left, int right);
		void QSortZ(int left, int right);
		PhotonMapNode* root;
		Photon* photons;
		int* indexes_in_x;
		int* indexes_in_y;
		int* indexes_in_z;

	};
}
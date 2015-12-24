#include "PhotonMap.h"

using namespace Engine;

class PhotonMapNode
{
	Photon photon;
	PhotonMapNode* left;
	PhotonMapNode* right;
};


void PhotonMap::QSortX(int left, int right)
{
    int l = left;
    int r = right;
    int m = left;

    while (l <= r)
    {
		while (photons[indexes_in_x[l]].point.x < photons[indexes_in_x[m]].point.x && l < right) l++;
        while (photons[indexes_in_x[m]].point.x < photons[indexes_in_x[r]].point.x && r > left) r--;

        if (l <= r)
        {
			int tmp = indexes_in_x[l];
			indexes_in_x[l] = indexes_in_x[r];
			indexes_in_x[r] = tmp;
            l++;
            r--;
        }
    }

    if (left < r) QSortX(left, r);
    if (l < right) QSortX(l, right);
}

void PhotonMap::QSortY(int left, int right)
{
    int l = left;
    int r = right;
    int m = left;

    while (l <= r)
    {
		while (photons[indexes_in_y[l]].point.y < photons[indexes_in_y[m]].point.y && l < right) l++;
        while (photons[indexes_in_y[m]].point.y < photons[indexes_in_y[r]].point.y && r > left) r--;

        if (l <= r)
        {
			int tmp = indexes_in_y[l];
			indexes_in_y[l] = indexes_in_y[r];
			indexes_in_y[r] = tmp;
            l++;
            r--;
        }
    }

    if (left < r) QSortY(left, r);
    if (l < right) QSortY(l, right);
}

void PhotonMap::QSortZ(int left, int right)
{
    int l = left;
    int r = right;
    int m = left;

    while (l <= r)
    {
		while (photons[indexes_in_z[l]].point.z < photons[indexes_in_z[m]].point.z && l < right) l++;
        while (photons[indexes_in_z[m]].point.z < photons[indexes_in_z[r]].point.z && r > left) r--;

        if (l <= r)
        {
			int tmp = indexes_in_z[l];
			indexes_in_z[l] = indexes_in_z[r];
			indexes_in_z[r] = tmp;
            l++;
            r--;
        }
    }

    if (left < r) QSortZ(left, r);
    if (l < right) QSortZ(l, right);
}
PhotonMap::PhotonMap(int nphotons, const Photon photons[])
{
	
}

PhotonMap::~PhotonMap()
{

}

const Photon* PhotonMap::FindNearest(const Vector& x, int count) const
{

}
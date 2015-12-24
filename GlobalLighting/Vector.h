#pragma once

#include <math.h>
#include "Defines.h"

namespace Engine
{
	class Vector
	{
	public:
		Vector() :
			x(0),
			y(0),
			z(0)
		{
		}

		Vector(GO_FLOAT x, GO_FLOAT y, GO_FLOAT z) :
			x(x),
			y(y),
			z(z)
		{
		}

		~Vector() {}

		Vector Normalize() const
		{
			GO_FLOAT normFactor = 1 / Length();
			return Vector(x * normFactor, y * normFactor, z * normFactor);
		}

		GO_FLOAT Norm() const
		{
			return x * x + y * y + z * z;
		}

		GO_FLOAT Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}
	
		Vector operator +(const Vector& vector) const
		{
			return Vector(x + vector.x, y + vector.y, z + vector.z);
		}
	
		Vector& operator +=(const Vector& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		Vector operator -() const
		{
			return Vector(-x, -y, -z);
		}

		Vector operator -(const Vector& vector) const
		{
			return Vector(x - vector.x, y - vector.y, z - vector.z);
		}
	
		Vector& operator -=(const Vector& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}

		Vector operator *(GO_FLOAT alpha) const
		{
			return Vector(alpha * x, alpha * y, alpha * z);
		}

		Vector& operator *=(GO_FLOAT alpha)
		{
			x *= alpha;
			y *= alpha;
			z *= alpha;
			return *this;
		}

		Vector operator /(GO_FLOAT alpha) const
		{
			GO_FLOAT factor = 1 / alpha;
			return Vector(x * factor, alpha * factor, alpha * factor);
		}

		Vector& operator /=(GO_FLOAT alpha)
		{
			GO_FLOAT factor = 1 / alpha;
			x *= factor;
			y *= factor;
			z *= factor;
			return *this;
		}

		Vector& operator =(const Vector& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			return *this;
		}
		
		const GO_FLOAT& operator[](short index) const
		{
			switch(index)
			{
			case 0:
				return x;
			break;
			case 1:
				return y;
			break;
			case 2:
				return z;
			break;
			}
		}

		Vector CrossProduct(const Vector& vector) const
		{
			return Vector(y * vector.z - vector.y * z, z * vector.x - vector.z * x, x * vector.y - vector.x * y);
		}

		GO_FLOAT DotProduct(const Vector& vector) const
		{
			return vector.x * x + vector.y * y + vector.z * z;
		}

		Vector Transform(const Vector& axis) const
		{
			Vector t = axis;
			Vector M1;
			Vector M2;

			if(abs(axis.x) < abs(axis.y))
			{
				if(abs(axis.x) < abs(axis.z))
					t.x = 1;
				else
					t.z = 1;
			}
			else
			{
				if(abs(axis.y) < abs(axis.z))
					t.y = 1;
				else
					t.z = 1;
			}
	
			M1 = axis.CrossProduct(t).Normalize();
			M2 = axis.CrossProduct(M1);
	

			return Vector(
				x * M1.x + y * M2.x + z * axis.x,
				x * M1.y + y * M2.y + z * axis.y,
				x * M1.z + y * M2.z + z * axis.z);
		}

		GO_FLOAT x;
		GO_FLOAT y;
		GO_FLOAT z;
	};

	inline Vector operator *(GO_FLOAT alpha, const Vector& vector)
	{
		return Vector(alpha * vector.x, alpha * vector.y, alpha * vector.z);
	}
}
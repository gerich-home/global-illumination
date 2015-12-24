#pragma once
#include <math.h>

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

	Vector CrossProduct(const Vector& vector) const
	{
		return Vector(y * vector.z - vector.y * z, z * vector.x - vector.z * x, x * vector.y - vector.x * y);
	}

	GO_FLOAT DotProduct(const Vector& vector) const
	{
		return vector.x * x + vector.y * y + vector.z * z;
	}

	GO_FLOAT x;
	GO_FLOAT y;
	GO_FLOAT z;
};

inline Vector operator *(GO_FLOAT alpha, const Vector& vector)
{
	return Vector(alpha * vector.x, alpha * vector.y, alpha * vector.z);
}
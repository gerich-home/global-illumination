#pragma once

#define L_R 0
#define L_G 1
#define L_B 2

class Luminance
{
public:
	Luminance(): 
		r(0),
		g(0),
		b(0)
	{

	}

	Luminance(GO_FLOAT r, GO_FLOAT g, GO_FLOAT b): 
		r(r),
		g(g),
		b(b)
	{

	}
		
	Luminance operator +(const Luminance& l) const
	{
		return Luminance(r + l.r, g + l.g, b + l.b);
	}
	
	Luminance& operator +=(const Luminance& l)
	{
		r += l.r;
		g += l.g;
		b += l.b;
		return *this;
	}
	
	Luminance operator /(GO_FLOAT alpha) const
	{
		GO_FLOAT factor = 1 / alpha;
		return Luminance(factor * r, factor * g, factor * b);
	}
	
	Luminance& operator /=(GO_FLOAT alpha)
	{
		GO_FLOAT factor = 1 / alpha;
		r *= factor;
		g *= factor;
		b *= factor;
		return *this;
	}
	
	Luminance operator *(GO_FLOAT alpha) const
	{
		return Luminance(alpha * r, alpha * g, alpha * b);
	}
	
	Luminance& operator *=(GO_FLOAT alpha)
	{
		r *= alpha;
		g *= alpha;
		b *= alpha;
		return *this;
	}
		
	Luminance operator -(const Luminance& l) const
	{
		return Luminance(r - l.r, g - l.g, b - l.b);
	}

	GO_FLOAT r;
	GO_FLOAT g;
	GO_FLOAT b;
};
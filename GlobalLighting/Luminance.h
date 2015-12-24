#pragma once

#define L_R 0
#define L_G 1
#define L_B 2

class Luminance
{
public:
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
	
	Luminance& operator /=(GO_FLOAT alpha)
	{
		GO_FLOAT factor = 1 / alpha;
		r *= factor;
		g *= factor;
		b *= factor;
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
#pragma once

#define L_R 0
#define L_G 1
#define L_B 2

class Luminance
{
public:
	Luminance()
	{
		colors[L_R] = 0;
		colors[L_G] = 0;
		colors[L_B] = 0;
	}

	Luminance(GO_FLOAT r, GO_FLOAT g, GO_FLOAT b)
	{
		colors[L_R] = r;
		colors[L_G] = g;
		colors[L_B] = b;
	}

	Luminance(GO_FLOAT colors[])
	{
		this->colors[L_R] = colors[L_R];
		this->colors[L_G] = colors[L_G];
		this->colors[L_B] = colors[L_B];
	}
		
	Luminance operator +(const Luminance& l) const
	{
		return Luminance(colors[L_R] + l.colors[L_R], colors[L_G] + l.colors[L_G], colors[L_B] + l.colors[L_B]);
	}
	
	Luminance& operator +=(const Luminance& l)
	{
		colors[L_R] += l.colors[L_R];
		colors[L_G] += l.colors[L_G];
		colors[L_B] += l.colors[L_B];
		return *this;
	}
	
	Luminance operator -(const Luminance& l) const
	{
		return Luminance(colors[L_R] - l.colors[L_R], colors[L_G] - l.colors[L_G], colors[L_B] - l.colors[L_B]);
	}
	
	Luminance& operator -=(const Luminance& l)
	{
		colors[L_R] -= l.colors[L_R];
		colors[L_G] -= l.colors[L_G];
		colors[L_B] -= l.colors[L_B];
		return *this;
	}
	
	Luminance operator /(GO_FLOAT alpha) const
	{
		GO_FLOAT factor = 1 / alpha;
		return Luminance(factor * colors[L_R], factor * colors[L_G], factor * colors[L_B]);
	}
	
	Luminance& operator /=(GO_FLOAT alpha)
	{
		GO_FLOAT factor = 1 / alpha;
		colors[L_R] *= factor;
		colors[L_G] *= factor;
		colors[L_B] *= factor;
		return *this;
	}
	
	Luminance operator *(GO_FLOAT alpha) const
	{
		return Luminance(alpha * colors[L_R], alpha * colors[L_G], alpha * colors[L_B]);
	}
	
	Luminance& operator *=(GO_FLOAT alpha)
	{
		colors[L_R] *= alpha;
		colors[L_G] *= alpha;
		colors[L_B] *= alpha;
		return *this;
	}

	
	GO_FLOAT r() const { return colors[L_R]; }
	GO_FLOAT g() const { return colors[L_G]; }
	GO_FLOAT b() const { return colors[L_B]; }
	
	GO_FLOAT colors[3];
};
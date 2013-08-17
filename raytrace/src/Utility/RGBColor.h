#ifndef RAYTRACER_RGBCOLOR_H
#define RAYTRACER_RGBCOLOR_H

class RGBColor
{
public:
	float r, g, b;

public:
	static const RGBColor BLACK;
	static const RGBColor WHITE;
	static const RGBColor RED;
	static const RGBColor GREEN;
	static const RGBColor BLUE;

public:
	RGBColor();
	RGBColor(float _r, float _g, float _b);
	RGBColor(const RGBColor& c);
	~RGBColor();

	RGBColor powc(float p) const;		// raise components to a power
	float average() const;					// the average of the components
	
	RGBColor& operator=(const RGBColor& rhs);
	RGBColor& operator+=(const RGBColor& c);
	RGBColor& operator*=(float a);
	RGBColor& operator/=(float a);

	friend RGBColor operator+(const RGBColor& a, const RGBColor& b);
	friend RGBColor operator*(const RGBColor& a, const RGBColor& b);
	friend RGBColor operator*(const RGBColor& c, float a);
	friend RGBColor operator*(float a, const RGBColor& c);
	friend RGBColor operator/(const RGBColor& c, float a);

	friend bool operator==(const RGBColor& a, const RGBColor& b);
};

inline RGBColor& RGBColor::operator+=(const RGBColor& c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	return (*this);
}

inline RGBColor& RGBColor::operator*=(float a)
{
	r *= a;
	g *= a;
	b *= a;
	return (*this);
}

inline RGBColor& RGBColor::operator/=(float a)
{
	r /= a;
	g /= a;
	b /= a;
	return (*this);
}

inline RGBColor operator+(const RGBColor& a, const RGBColor& b)
{
	return RGBColor(a.r+b.r, a.g+b.g, a.b+b.b);
}

inline RGBColor operator*(const RGBColor& a, const RGBColor& b)
{
	return RGBColor(a.r*b.r, a.g*b.g, a.b*b.b);
}

inline RGBColor operator*(const RGBColor& c, float a)
{
	return RGBColor(c.r*a, c.g*a, c.b*a);
}

inline RGBColor operator*(float a, const RGBColor& c)
{
	return RGBColor(c.r*a, c.g*a, c.b*a);
}

inline RGBColor operator/(const RGBColor& c, float a)
{
	return RGBColor(c.r/a, c.g/a, c.b/a);
}

inline bool operator==(const RGBColor& a, const RGBColor& b)
{
	return (a.r == b.r && a.g == b.g && a.b == b.b);
}

inline float RGBColor::average() const
{
	return (0.333333333333 * (r+g+b));
}

#endif

#ifndef RAYTRACE_POINT2D_H
#define RAYTRACE_POINT2D_H

class Point2D
{
public:
	float x, y;

public:
	Point2D();
	Point2D(float arg);
	Point2D(float x1, float y1);
	Point2D(const Point2D& p);
	~Point2D() {}

	Point2D& operator=(const Point2D& rhs);

	friend Point2D operator*(const Point2D& p, const float a);
};

inline Point2D operator*(const Point2D& p, const float a)
{
	return Point2D(p.x*a, p.y*a);
}

#endif

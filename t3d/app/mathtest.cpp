#include "t3dmath.h"
#include "t3dunittest.h"
#include <math.h>

// ---------------------------------------------------
// Sin/Cos
// ---------------------------------------------------

DEFINE_TESTFUNC(testFastSinAndCos)
{
	ASSERT_TRUE(Fast_Sin(50.2f) - 0.768284f <= 0.001f);
	ASSERT_TRUE(Fast_Cos(50.2f) - 0.640110f <= 0.001f);
}

// ---------------------------------------------------
// Polar 2D
// ---------------------------------------------------

DEFINE_TESTFUNC(testPolar2D)
{
	POLAR2D pp = {5, PI_DIV_4};
	POINT2D pr = {{0, 0}};
	float x, y;
	POLAR2D_To_POINT2D(&pp, &pr);
	POLAR2D_To_RectXY(&pp, &x, &y);
	ASSERT_TRUE(almostEqual(pr.x, 3.535534f));
	ASSERT_TRUE(almostEqual(pr.y, 3.535534f));
	ASSERT_TRUE(almostEqual(x, 3.535534f));
	ASSERT_TRUE(almostEqual(y, 3.535534f));

	memset(&pp, 0, sizeof(pp));
	float r, theta;
	POINT2D_To_POLAR2D(&pr, &pp);
	POINT2D_To_PolarRTh(&pr, &r, &theta);
	ASSERT_TRUE(almostEqual(pp.r, 5.0f));
	ASSERT_TRUE(almostEqual(pp.theta, PI_DIV_4));
}

DEFINE_TESTFUNC(testCylindrical3D)
{
	CYLINDRICAL3D pc = {10, PI/5, 20};
	POINT3D pr = {{0,0,0}};
	CYLINDRICAL3D_To_POINT3D(&pc, &pr);
	ASSERT_TRUE(almostEqual(pr.x, 8.090170f));
	ASSERT_TRUE(almostEqual(pr.y, 5.877853f));
	ASSERT_TRUE(almostEqual(pr.z, 20.f));

	memset(&pc, 0, sizeof(pc));
	POINT3D_To_CYLINDRICAL3D(&pr, &pc);
	ASSERT_TRUE(almostEqual(pc.r, 10.f));
	ASSERT_TRUE(almostEqual(pc.theta, PI/5));
	ASSERT_TRUE(almostEqual(pc.z, 20.f));
}

DEFINE_TESTFUNC(testSpherical3D)
{
	SPHERICAL3D ps = {1, PI_DIV_4, PI_DIV_2};
	POINT3D pr = {{0,0,0}};
	SPHERICAL3D_To_POINT3D(&ps, &pr);
	ASSERT_TRUE(almostEqual(pr.x, 0.f));
	ASSERT_TRUE(almostEqual(pr.y, 0.707107f));
	ASSERT_TRUE(almostEqual(pr.z, 0.707107f));

	memset(&ps, 0, sizeof(ps));
	POINT3D_To_SPHERICAL3D(&pr, &ps);
	ASSERT_TRUE(almostEqual(ps.p, 1.f));
	ASSERT_TRUE(almostEqual(ps.theta, PI_DIV_4));
	ASSERT_TRUE(almostEqual(ps.phi, PI_DIV_2));
}

// ---------------------------------------------------
// Vector 2D
// ---------------------------------------------------

DEFINE_TESTFUNC(testVector2DAdd)
{
	VECTOR2D a = {{1.f, 2.f}};
	VECTOR2D b = {{3.f, 4.f}};
	VECTOR2D c;
	VECTOR2D_Add(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, 4.f));
	ASSERT_TRUE(almostEqual(c.y, 6.f));

	c = VECTOR2D_Add(&a, &b);
	ASSERT_TRUE(almostEqual(c.x, 4.f));
	ASSERT_TRUE(almostEqual(c.y, 6.f));
}

DEFINE_TESTFUNC(testVector2DSub)
{
	VECTOR2D a = {{1.f, 6.4f}};
	VECTOR2D b = {{3.f, 4.f}};
	VECTOR2D c;
	VECTOR2D_Sub(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, -2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.4f));

	c = VECTOR2D_Sub(&a, &b);
	ASSERT_TRUE(almostEqual(c.x, -2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.4f));
}

DEFINE_TESTFUNC(testVector2DScale)
{
	VECTOR2D a = {{2.3f, 6.7f}};
	VECTOR2D b;
	const float k = 1.2f;
	VECTOR2D_Scale(k, &a, &b);
	ASSERT_TRUE(almostEqual(b.x, 1.2f*2.3f));
	ASSERT_TRUE(almostEqual(b.y, 1.2f*6.7f));

	VECTOR2D_Scale(k, &a);
	ASSERT_TRUE(almostEqual(a.x, 1.2f*2.3f));
	ASSERT_TRUE(almostEqual(a.y, 1.2f*6.7f));
}

DEFINE_TESTFUNC(testVector2DDot)
{
	VECTOR2D a = {{1.2f, 2.3f}};
	VECTOR2D b = {{3.4f, 4.5f}};
	float v = VECTOR2D_Dot(&a, &b);
	ASSERT_TRUE(almostEqual(v, 1.2f*3.4f + 2.3f*4.5f));
}

DEFINE_TESTFUNC(testVector2DLength)
{
	VECTOR2D a = {{3.f, 4.f}};
	float length = VECTOR2D_Length(&a);
	ASSERT_TRUE(almostEqual(length, 5.f));
}

DEFINE_TESTFUNC(testVector2DNormalize)
{
	VECTOR2D a = {{3.f, 4.f}};
	VECTOR2D n;
	VECTOR2D_Normalize(&a, &n);
	ASSERT_TRUE(almostEqual(n.x, 3.f/5.f));
	ASSERT_TRUE(almostEqual(n.y, 4.f/5.f));

	VECTOR2D_Normalize(&a);
	ASSERT_TRUE(almostEqual(a.x, 3.f/5.f));
	ASSERT_TRUE(almostEqual(a.y, 4.f/5.f));
}

DEFINE_TESTFUNC(testVector2DBuild)
{
	VECTOR2D a = {{1.f, 2.f}};
	VECTOR2D b = {{3.f, 4.f}};
	VECTOR2D c;
	VECTOR2D_Build(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, 2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.f));
}

DEFINE_TESTFUNC(testVector2DCosTh)
{
	VECTOR2D a = {{1.f, 0.f}};
	VECTOR2D b = {{1.f, 1.f}};
	float v = VECTOR2D_CosTh(&a, &b);
	ASSERT_TRUE(almostEqual(DEG_TO_RAD(45), v));
}

// ---------------------------------------------------
// Vector 3D
// ---------------------------------------------------

DEFINE_TESTFUNC(testVector3DAdd)
{
	VECTOR3D a = {{1.f, 2.f, 3.f}};
	VECTOR3D b = {{3.f, 4.f, 5.f}};
	VECTOR3D c;
	VECTOR3D_Add(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, 4.f));
	ASSERT_TRUE(almostEqual(c.y, 6.f));
	ASSERT_TRUE(almostEqual(c.z, 8.f));

	c = VECTOR3D_Add(&a, &b);
	ASSERT_TRUE(almostEqual(c.x, 4.f));
	ASSERT_TRUE(almostEqual(c.y, 6.f));
	ASSERT_TRUE(almostEqual(c.z, 8.f));
}

DEFINE_TESTFUNC(testVector3DSub)
{
	VECTOR3D a = {{1.f, 6.4f, 7.f}};
	VECTOR3D b = {{3.f, 4.f, 3.f}};
	VECTOR3D c;
	VECTOR3D_Sub(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, -2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.4f));
	ASSERT_TRUE(almostEqual(c.z, 4.f));

	c = VECTOR3D_Sub(&a, &b);
	ASSERT_TRUE(almostEqual(c.x, -2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.4f));
	ASSERT_TRUE(almostEqual(c.z, 4.f));
}

DEFINE_TESTFUNC(testVector3DScale)
{
	VECTOR3D a = {{2.3f, 6.7f, 5.2f}};
	VECTOR3D b;
	const float k = 1.2f;
	VECTOR3D_Scale(k, &a, &b);
	ASSERT_TRUE(almostEqual(b.x, 1.2f*2.3f));
	ASSERT_TRUE(almostEqual(b.y, 1.2f*6.7f));
	ASSERT_TRUE(almostEqual(b.z, 1.2f*5.2f));

	VECTOR3D_Scale(k, &a);
	ASSERT_TRUE(almostEqual(a.x, 1.2f*2.3f));
	ASSERT_TRUE(almostEqual(a.y, 1.2f*6.7f));
	ASSERT_TRUE(almostEqual(a.z, 1.2f*5.2f));
}

DEFINE_TESTFUNC(testVector3DDot)
{
	VECTOR3D a = {{1.2f, 2.3f, 0.2f}};
	VECTOR3D b = {{3.4f, 4.5f, 7.8f}};
	float v = VECTOR3D_Dot(&a, &b);
	ASSERT_TRUE(almostEqual(v, 1.2f*3.4f + 2.3f*4.5f + 0.2f*7.8f));
}

DEFINE_TESTFUNC(testVector3DLength)
{
	VECTOR3D a = {{3.f, 4.f, 5.f}};
	float length = VECTOR3D_Length(&a);
	ASSERT_TRUE(almostEqual(length, sqrtf(50.f)));
}

DEFINE_TESTFUNC(testVector3DNormalize)
{
	VECTOR3D a = {{3.f, 4.f, 5.f}};
	VECTOR3D n;
	VECTOR3D_Normalize(&a, &n);
	ASSERT_TRUE(almostEqual(n.x, 3.f/sqrtf(50.f)));
	ASSERT_TRUE(almostEqual(n.y, 4.f/sqrtf(50.f)));
	ASSERT_TRUE(almostEqual(n.z, 5.f/sqrtf(50.f)));

	VECTOR3D_Normalize(&a);
	ASSERT_TRUE(almostEqual(a.x, 3.f/sqrtf(50.f)));
	ASSERT_TRUE(almostEqual(a.y, 4.f/sqrtf(50.f)));
	ASSERT_TRUE(almostEqual(a.z, 5.f/sqrtf(50.f)));
}

DEFINE_TESTFUNC(testVector3DBuild)
{
	VECTOR3D a = {{1.f, 2.f, 3.f}};
	VECTOR3D b = {{3.f, 4.f, 4.7}};
	VECTOR3D c;
	VECTOR3D_Build(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, 2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.f));
	ASSERT_TRUE(almostEqual(c.z, 1.7f));
}

DEFINE_TESTFUNC(testVector3DCosTh)
{
	VECTOR3D a = {{1.f, 0.f, 0.f}};
	VECTOR3D b = {{0.f, 1.f, 0.f}};
	float v = VECTOR3D_CosTh(&a, &b);
	ASSERT_TRUE(almostEqual(DEG_TO_RAD(90), v));
}

// ---------------------------------------------------
// Vector 4D
// ---------------------------------------------------

DEFINE_TESTFUNC(testVector4DAdd)
{
	VECTOR4D a = {{1.f, 2.f, 3.f, 4.f}};
	VECTOR4D b = {{3.f, 4.f, 5.f, 6.f}};
	VECTOR4D c;
	VECTOR4D_Add(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, 4.f));
	ASSERT_TRUE(almostEqual(c.y, 6.f));
	ASSERT_TRUE(almostEqual(c.z, 8.f));
	ASSERT_TRUE(almostEqual(c.w, 10.f));

	c = VECTOR4D_Add(&a, &b);
	ASSERT_TRUE(almostEqual(c.x, 4.f));
	ASSERT_TRUE(almostEqual(c.y, 6.f));
	ASSERT_TRUE(almostEqual(c.z, 8.f));
	ASSERT_TRUE(almostEqual(c.w, 10.f));
}

DEFINE_TESTFUNC(testVector4DSub)
{
	VECTOR4D a = {{1.f, 6.4f, 7.f, 2.3f}};
	VECTOR4D b = {{3.f, 4.f, 3.f, 6.6f}};
	VECTOR4D c;
	VECTOR4D_Sub(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, -2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.4f));
	ASSERT_TRUE(almostEqual(c.z, 4.f));
	ASSERT_TRUE(almostEqual(c.w, -4.3f));

	c = VECTOR4D_Sub(&a, &b);
	ASSERT_TRUE(almostEqual(c.x, -2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.4f));
	ASSERT_TRUE(almostEqual(c.z, 4.f));
	ASSERT_TRUE(almostEqual(c.w, -4.3f));
}

DEFINE_TESTFUNC(testVector4DScale)
{
	VECTOR4D a = {{2.3f, 6.7f, 5.2f, 2.3f}};
	VECTOR4D b;
	const float k = 1.2f;
	VECTOR4D_Scale(k, &a, &b);
	ASSERT_TRUE(almostEqual(b.x, 1.2f*2.3f));
	ASSERT_TRUE(almostEqual(b.y, 1.2f*6.7f));
	ASSERT_TRUE(almostEqual(b.z, 1.2f*5.2f));
	ASSERT_TRUE(almostEqual(b.w, 1.2f*2.3f));

	VECTOR4D_Scale(k, &a);
	ASSERT_TRUE(almostEqual(a.x, 1.2f*2.3f));
	ASSERT_TRUE(almostEqual(a.y, 1.2f*6.7f));
	ASSERT_TRUE(almostEqual(a.z, 1.2f*5.2f));
	ASSERT_TRUE(almostEqual(a.w, 1.2f*2.3f));
}

DEFINE_TESTFUNC(testVector4DDot)
{
	VECTOR4D a = {{1.2f, 2.3f, 0.2f, 1.3f}};
	VECTOR4D b = {{3.4f, 4.5f, 7.8f, 6.4f}};
	float v = VECTOR4D_Dot(&a, &b);
	ASSERT_TRUE(almostEqual(v, 1.2f*3.4f + 2.3f*4.5f + 0.2f*7.8f + 1.3f*6.4f));
}

DEFINE_TESTFUNC(testVector4DLength)
{
	VECTOR4D a = {{3.f, 4.f, 5.f, 6.f}};
	float length = VECTOR4D_Length(&a);
	ASSERT_TRUE(almostEqual(length, sqrtf(86.f)));
}

DEFINE_TESTFUNC(testVector4DNormalize)
{
	VECTOR4D a = {{3.f, 4.f, 5.f, 6.f}};
	VECTOR4D n;
	VECTOR4D_Normalize(&a, &n);
	ASSERT_TRUE(almostEqual(n.x, 3.f/sqrtf(86.f)));
	ASSERT_TRUE(almostEqual(n.y, 4.f/sqrtf(86.f)));
	ASSERT_TRUE(almostEqual(n.z, 5.f/sqrtf(86.f)));
	ASSERT_TRUE(almostEqual(n.w, 6.f/sqrtf(86.f)));

	VECTOR4D_Normalize(&a);
	ASSERT_TRUE(almostEqual(a.x, 3.f/sqrtf(86.f)));
	ASSERT_TRUE(almostEqual(a.y, 4.f/sqrtf(86.f)));
	ASSERT_TRUE(almostEqual(a.z, 5.f/sqrtf(86.f)));
	ASSERT_TRUE(almostEqual(a.w, 6.f/sqrtf(86.f)));
}

DEFINE_TESTFUNC(testVector4DBuild)
{
	VECTOR4D a = {{1.f, 2.f, 3.f, 4.f}};
	VECTOR4D b = {{3.f, 4.f, 4.7, 5.f}};
	VECTOR4D c;
	VECTOR4D_Build(&a, &b, &c);
	ASSERT_TRUE(almostEqual(c.x, 2.f));
	ASSERT_TRUE(almostEqual(c.y, 2.f));
	ASSERT_TRUE(almostEqual(c.z, 1.7f));
	ASSERT_TRUE(almostEqual(c.w, 1.f));
}

DEFINE_TESTFUNC(testVector4DCosTh)
{
	VECTOR4D a = {{1.f, 0.f, 0.f, 0.f}};
	VECTOR4D b = {{0.f, 1.f, 0.f, 0.f}};
	float v = VECTOR4D_CosTh(&a, &b);
	ASSERT_TRUE(almostEqual(DEG_TO_RAD(90), v));
}

// ---------------------------------------------------
// Main
// ---------------------------------------------------

int main()
{
	Build_Sin_Cos_Tables();

	RUN_ALL_TEST();
	return 0;
}


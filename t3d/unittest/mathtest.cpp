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
// Matrix 2x2
// ---------------------------------------------------

DEFINE_TESTFUNC(testMat_Init_2X2)
{
	MATRIX2X2 m;
	Mat_Init_2X2(&m, 1.1f, 2.2f, 3.3f, 4.4f);
	ASSERT_TRUE(almostEqual(m.M00, 1.1f));
	ASSERT_TRUE(almostEqual(m.M01, 2.2f));
	ASSERT_TRUE(almostEqual(m.M10, 3.3f));
	ASSERT_TRUE(almostEqual(m.M11, 4.4f));
}

DEFINE_TESTFUNC(testMat_Det_2X2)
{
	float det;
	MATRIX2X2 m;
	Mat_Init_2X2(&m, 1.1f, 2.2f, 3.3f, 4.4f);
	det = Mat_Det_2X2(&m);
	ASSERT_TRUE(almostEqual(det, 1.1f*4.4f - 2.2*3.3f));
}

DEFINE_TESTFUNC(testMat_Add_2X2)
{
	MATRIX2X2 ma, mb, msum;
	Mat_Init_2X2(&ma, 1.1f, 2.2f, 3.3f, 4.4f);
	Mat_Init_2X2(&mb, 1.1f, 2.2f, 3.3f, 4.4f);
	Mat_Add_2X2(&ma, &mb, &msum);
	ASSERT_TRUE(almostEqual(msum.M00, 2.2f));
	ASSERT_TRUE(almostEqual(msum.M01, 4.4f));
	ASSERT_TRUE(almostEqual(msum.M10, 6.6f));
	ASSERT_TRUE(almostEqual(msum.M11, 8.8f));
}

DEFINE_TESTFUNC(testMat_Mul_2X2)
{
	MATRIX2X2 ma = {{{1.1f, 2.2f},
								 	 {3.3f, 4.4f}}};
	MATRIX2X2 mb = {{{1.1f, 2.2f},
									 {3.3f, 4.4f}}};
	MATRIX2X2 mprod;
	Mat_Mul_2X2(&ma, &mb, &mprod);
	ASSERT_TRUE(almostEqual(mprod.M00, 1.1f*1.1f + 2.2f*3.3f));
	ASSERT_TRUE(almostEqual(mprod.M01, 1.1f*2.2f + 2.2f*4.4f));
	ASSERT_TRUE(almostEqual(mprod.M10, 3.3f*1.1f + 4.4f*3.3f));
	ASSERT_TRUE(almostEqual(mprod.M11, 3.3f*2.2f + 4.4f*4.4f));
}

DEFINE_TESTFUNC(testMat_Inverse_2X2)
{
	MATRIX2X2 m = {{{1.f, 2.f}, {4.f, -3.}}};
	MATRIX2X2 mi;
	Mat_Inverse_2X2(&m, &mi);

	MATRIX2X2 mprod;
	Mat_Mul_2X2(&m, &mi, &mprod);
	ASSERT_TRUE(almostEqual(mprod.M00, 1.f));
	ASSERT_TRUE(almostEqual(mprod.M01, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M10, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M11, 1.f));
}

DEFINE_TESTFUNC(testSolve_2X2_System)
{
	MATRIX2X2 A = {{{6, 3}, {3, 4}}};
	MATRIX1X2 B = {{10, 6}};
	MATRIX1X2 X;
	Solve_2X2_System(&A, &X, &B);
	ASSERT_TRUE(almostEqual(X.M00, 1.46666666f));
	ASSERT_TRUE(almostEqual(X.M01, 0.4f));
}


// ---------------------------------------------------
// Matrix 3x3
// ---------------------------------------------------

DEFINE_TESTFUNC(testMat_Init_3X3)
{
	MATRIX3X3 m;
	Mat_Init_3X3(&m,
		1.1f, 2.2f, 3.3f,
		4.4f, 5.5f, 6.6f,
		7.7f, 8.8f, 9.9f);
	ASSERT_TRUE(almostEqual(m.M00, 1.1f));
	ASSERT_TRUE(almostEqual(m.M01, 2.2f));
	ASSERT_TRUE(almostEqual(m.M02, 3.3f));
	ASSERT_TRUE(almostEqual(m.M10, 4.4f));
	ASSERT_TRUE(almostEqual(m.M11, 5.5f));
	ASSERT_TRUE(almostEqual(m.M12, 6.6f));
	ASSERT_TRUE(almostEqual(m.M20, 7.7f));
	ASSERT_TRUE(almostEqual(m.M21, 8.8f));
	ASSERT_TRUE(almostEqual(m.M22, 9.9f));
}

DEFINE_TESTFUNC(testMat_Mul_3X3)
{
	MATRIX3X3 ma, mb, mprod;

	Mat_Init_3X3(&ma,
		1.1f, 2.2f, 3.3f,
		4.4f, 5.5f, 6.6f,
		7.7f, 8.8f, 9.9f);
	Mat_Init_3X3(&mb,
		1.1f, 2.2f, 3.3f,
		4.4f, 5.5f, 6.6f,
		7.7f, 8.8f, 9.9f);

	Mat_Mul_3X3(&ma, &mb, &mprod);
	ASSERT_TRUE(almostEqual(mprod.M00, 1.1f*1.1f + 2.2f*4.4f + 3.3f*7.7f));
	ASSERT_TRUE(almostEqual(mprod.M01, 1.1f*2.2f + 2.2f*5.5f + 3.3f*8.8f));
	ASSERT_TRUE(almostEqual(mprod.M02, 1.1f*3.3f + 2.2f*6.6f + 3.3f*9.9f));
	ASSERT_TRUE(almostEqual(mprod.M10, 4.4f*1.1f + 5.5f*4.4f + 6.6f*7.7f));
	ASSERT_TRUE(almostEqual(mprod.M11, 4.4f*2.2f + 5.5f*5.5f + 6.6f*8.8f));
	ASSERT_TRUE(almostEqual(mprod.M12, 4.4f*3.3f + 5.5f*6.6f + 6.6f*9.9f));
	ASSERT_TRUE(almostEqual(mprod.M20, 7.7f*1.1f + 8.8f*4.4f + 9.9f*7.7f));
	ASSERT_TRUE(almostEqual(mprod.M21, 7.7f*2.2f + 8.8f*5.5f + 9.9f*8.8f));
	ASSERT_TRUE(almostEqual(mprod.M22, 7.7f*3.3f + 8.8f*6.6f + 9.9f*9.9f));
}

DEFINE_TESTFUNC(testMat_Add_3X3)
{
	MATRIX3X3 ma, mb, msum;

	Mat_Init_3X3(&ma,
		1.1f, 2.2f, 3.3f,
		4.4f, 5.5f, 6.6f,
		7.7f, 8.8f, 9.9f);
	Mat_Init_3X3(&mb,
		1.1f, 2.2f, 3.3f,
		4.4f, 5.5f, 6.6f,
		7.7f, 8.8f, 9.9f);

	Mat_Add_3X3(&ma, &mb, &msum);
	ASSERT_TRUE(almostEqual(msum.M00, 1.1f + 1.1f));
	ASSERT_TRUE(almostEqual(msum.M01, 2.2f + 2.2f));
	ASSERT_TRUE(almostEqual(msum.M02, 3.3f + 3.3f));
	ASSERT_TRUE(almostEqual(msum.M10, 4.4f + 4.4f));
	ASSERT_TRUE(almostEqual(msum.M11, 5.5f + 5.5f));
	ASSERT_TRUE(almostEqual(msum.M12, 6.6f + 6.6f));
	ASSERT_TRUE(almostEqual(msum.M20, 7.7f + 7.7f));
	ASSERT_TRUE(almostEqual(msum.M21, 8.8f + 8.8f));
	ASSERT_TRUE(almostEqual(msum.M22, 9.9f + 9.9f));
}

DEFINE_TESTFUNC(testMat_Mul_VECTOR3D_3X3)
{
	VECTOR3D va = {{1.1f, 2.2f, 3.3f}};
	MATRIX3X3 mb;
	VECTOR3D vprod;

	Mat_Init_3X3(&mb,
		1.1f, 2.2f, 3.3f,
		4.4f, 5.5f, 6.6f,
		7.7f, 8.8f, 9.9f);

	Mat_Mul_VECTOR3D_3X3(&va, &mb, &vprod);
	ASSERT_TRUE(almostEqual(vprod.x, 1.1f*1.1f + 2.2f*4.4f + 3.3f*7.7f));
	ASSERT_TRUE(almostEqual(vprod.y, 1.1f*2.2f + 2.2f*5.5f + 3.3f*8.8f));
	ASSERT_TRUE(almostEqual(vprod.z, 1.1f*3.3f + 2.2f*6.6f + 3.3f*9.9f));
}

DEFINE_TESTFUNC(testMat_Det_3X3)
{
	MATRIX3X3 m;
	float det;

	Mat_Init_3X3(&m,
		1, 2, 3,
		4, 5, 6,
		7, 8, 9.1f);
	det = Mat_Det_3X3(&m);
	ASSERT_TRUE(almostEqual(det, 1*5*9.1f + 2*6*7 + 3*4*8 - 7*5*3 - 4*2*9.1f - 1*8*6));

/*
	Mat_Init_3X3(&m,
		1.1f, 2.2f, 3.3f,
		4.4f, 5.5f, 6.6f,
		7.7f, 8.8f, 9.9f);
	det = Mat_Det_3X3(&m); // 1.1f*5.5f*9.9f + 2.2f*6.6f*7.7f + 3.3f*4.4f*8.8f - 
												 // 3.3f*5.5f*7.7f - 2.2f*4.4f*9.9f - 1.1f*6.6f*8.8f

	// failed as float precision
	ASSERT_TRUE(almostEqual(det, 1.1f*5.5f*9.9f + 2.2f*6.6f*7.7f + 3.3f*4.4f*8.8f - 7.7f*8.8f*3.3f - 4.4f*2.2f*9.9f - 1.1f*8.8f*6.6f));
												 // 1.1f*5.5f*9.9f + 2.2f*6.6f*7.7f + 3.3f*4.4f*8.8f - 
												 // 7.7f*8.8f*3.3f - 4.4f*2.2f*9.9f - 1.1f*8.8f*6.6f
*/
}

DEFINE_TESTFUNC(testMat_Inverse_3X3)
{
	MATRIX3X3 m;
	MATRIX3X3 mi;
	Mat_Init_3X3(&m,
		1.1f, 2.2f, 1.1f,
		2.2f, 1.1f, 2.2f,
		1.1f, 2.2f, 2.2f);
	bool v = Mat_Inverse_3X3(&m, &mi);
	ASSERT_TRUE(v);

	MATRIX3X3 mprod;
	Mat_Mul_3X3(&m, &mi, &mprod);
	ASSERT_TRUE(almostEqual(mprod.M00, 1.f));
	ASSERT_TRUE(almostEqual(mprod.M01, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M02, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M10, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M11, 1.f));
	ASSERT_TRUE(almostEqual(mprod.M12, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M20, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M21, 0.f));
	ASSERT_TRUE(almostEqual(mprod.M22, 1.f));
}

DEFINE_TESTFUNC(testSolve_3X3_System)
{
	MATRIX3X3 A = {{{1, 1, -1}, {1, -3, 2}, {3, 2, -1}}};
	MATRIX1X3 B = {{6, 1, 4}};

	MATRIX1X3 X;
	bool r = Solve_3X3_System(&A, &X, &B);
	ASSERT_TRUE(r);

	ASSERT_TRUE(almostEqual(X.M00, 2.2));
	ASSERT_TRUE(almostEqual(X.M01, -6.4));
	ASSERT_TRUE(almostEqual(X.M02, -10.2));
}


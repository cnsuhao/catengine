#include "t3dmath.h"
#include <math.h>
#include <stdio.h>

// ---------------------------------------------------
// Sin/Cos
// ---------------------------------------------------

static float cos_look[361];
static float sin_look[361];

void Build_Sin_Cos_Tables()
{
	int i;

	for (i = 0; i < 360; i++)
	{
		sin_look[i] = sinf(DEG_TO_RAD(i));
		cos_look[i] = cosf(DEG_TO_RAD(i));
	}

	sin_look[360] = sin_look[0];
	cos_look[360] = cos_look[0];
}

float Fast_Sin(float theta)
{
	// this function uses the sin_look[] lookup table, but
	// has logic to handle negative angles as well as fractional
	// angles via interpolation, use this for a more robust
	// sin computation that the blind lookup, but with a slight
	// hit in speed

	// convert to 0-359
	theta = fmodf(theta, 360);
	if (theta < 0) theta += 360.0f;

	int theta_int = (int)theta;
	float thread_frac = theta - theta_int;

	return (sin_look[theta_int] + thread_frac*(sin_look[theta_int+1] - sin_look[theta_int]));
}

float Fast_Cos(float theta)
{
	// this function uses the sin_look[] lookup table, but
	// has logic to handle negative angles as well as fractional
	// angles via interpolation, use this for a more robust
	// sin computation that the blind lookup, but with a slight
	// hit in speed

	// convert to 0-359
	theta = fmodf(theta, 360);
	if (theta < 0) theta += 360.0f;

	int theta_int = (int)theta;
	float thread_frac = theta - theta_int;

	return (cos_look[theta_int] + thread_frac*(cos_look[theta_int+1] - cos_look[theta_int]));
}


// ---------------------------------------------------
// Polar 2D
// ---------------------------------------------------
void POLAR2D_To_RectXY(POLAR2D_PTR polar, float *x, float *y)
{
	*x = polar->r * Fast_Cos(RAD_TO_DEG(polar->theta));
	*y = polar->r * Fast_Sin(RAD_TO_DEG(polar->theta));
}

void POLAR2D_To_POINT2D(POLAR2D_PTR polar, POINT2D_PTR rect)
{
	POLAR2D_To_RectXY(polar, &rect->x, &rect->y);
}

void POINT2D_To_PolarRTh(POINT2D_PTR rect, float *r, float *theta)
{
	if (rect->x < EPSILON_E6)
	{
		*r     = rect->y;
		*theta = rect->y > EPSILON_E6 ? PI_DIV_2 : -PI_DIV_2;
		return;
	}

	*r     = sqrtf(rect->x*rect->x + rect->y*rect->y);
	*theta = atanf(rect->y / rect->x);
}

void POINT2D_To_POLAR2D(POINT2D_PTR rect, POLAR2D_PTR polar)
{
	POINT2D_To_PolarRTh(rect, &polar->r, &polar->theta);
}

// ---------------------------------------------------
// Cylindrical 3D
// ---------------------------------------------------
void CYLINDRICAL3D_To_RectXYZ(CYLINDRICAL3D_PTR cyl, float *x, float *y, float *z)
{
	*x = cyl->r * Fast_Cos(RAD_TO_DEG(cyl->theta));
	*y = cyl->r * Fast_Sin(RAD_TO_DEG(cyl->theta));
	*z = cyl->z;
}

void CYLINDRICAL3D_To_POINT3D(CYLINDRICAL3D_PTR cyl, POINT3D_PTR rect)
{
	CYLINDRICAL3D_To_RectXYZ(cyl, &rect->x, &rect->y, &rect->z);
}

void POINT3D_To_CylindricalRThZ(POINT3D_PTR rect, float *r, float *theta, float *z)
{
	if (rect->x < EPSILON_E6)
	{
		*r     = rect->y;
		*theta = rect->y > EPSILON_E6 ? PI_DIV_2 : -PI_DIV_2;
		*z     = rect->z;
		return;
	}

	*r     = sqrtf(rect->x*rect->x + rect->y*rect->y);
	*theta = atanf(rect->y / rect->x);
	*z     = rect->z;
}

void POINT3D_To_CYLINDRICAL3D(POINT3D_PTR rect, CYLINDRICAL3D_PTR cyl)
{
	POINT3D_To_CylindricalRThZ(rect, &cyl->r, &cyl->theta, &cyl->z);
}

void SPHERICAL3D_To_RectXYZ(SPHERICAL3D_PTR sph, float *x, float *y, float *z)
{
	float r  = sph->p * sinf(sph->theta);
	*x = r * cosf(sph->phi);
	*y = r * sinf(sph->phi);
	*z = sph->p * cosf(sph->theta);
}

void SPHERICAL3D_To_POINT3D(SPHERICAL3D_PTR sph, POINT3D_PTR rect)
{
	SPHERICAL3D_To_RectXYZ(sph, &rect->x, &rect->y, &rect->z);
}

void POINT3D_To_SphericalPThPh(POINT3D_PTR rect, float *p, float *theta, float *phi)
{
	float xxyy = rect->x*rect->x + rect->y*rect->y;
	float r = sqrt(xxyy);
	*p = sqrt(xxyy + rect->z*rect->z);
	if (*p > EPSILON_E6)
	{
		if (r > EPSILON_E6)
		{
			if (rect->x > EPSILON_E6)
			{
				*phi = acosf(r / rect->x);
			}
			else
			{
				*phi = rect->y > EPSILON_E6 ? PI_DIV_2 : -PI_DIV_2;
			}
			*theta = acosf(rect->z / *p);
		}
		else
		{
			*phi   = 0.f;
			*theta = rect->z > EPSILON_E6 ? 0.f : PI;
		}
	}
	else
	{
		*p = 0.f;
		*theta = 0.f;
		*phi = 0.f;
	}
}

void POINT3D_To_SPHERICAL3D(POINT3D_PTR rect, SPHERICAL3D_PTR sph)
{
	POINT3D_To_SphericalPThPh(rect, &sph->p, &sph->theta, &sph->phi);
}


// ---------------------------------------------------
// Vector 2D
// ---------------------------------------------------
void VECTOR2D_Add(VECTOR2D_PTR va, VECTOR2D_PTR vb, VECTOR2D_PTR vsum)
{
	vsum->x = va->x + vb->x;
	vsum->y = va->y + vb->y;
}

VECTOR2D VECTOR2D_Add(VECTOR2D_PTR va, VECTOR2D_PTR vb)
{
	VECTOR2D vsum;
	VECTOR2D_Add(va, vb, &vsum);
	return vsum;
}

void VECTOR2D_Sub(VECTOR2D_PTR va, VECTOR2D_PTR vb, VECTOR2D_PTR vdiff)
{
	vdiff->x = va->x - vb->x;
	vdiff->y = va->y - vb->y;
}

VECTOR2D VECTOR2D_Sub(VECTOR2D_PTR va, VECTOR2D_PTR vb)
{
	VECTOR2D vdiff;
	VECTOR2D_Sub(va, vb, &vdiff);
	return vdiff;
}

void VECTOR2D_Scale(float k, VECTOR2D_PTR va)
{
	va->x = va->x * k;
	va->y = va->y * k;
}

void VECTOR2D_Scale(float k, VECTOR2D_PTR va, VECTOR2D_PTR vscaled)
{
	vscaled->x = va->x * k;
	vscaled->y = va->y * k;
}

float VECTOR2D_Dot(VECTOR2D_PTR va, VECTOR2D_PTR vb)
{
	return va->x*vb->x + va->y*vb->y;
}

float VECTOR2D_Length(VECTOR2D_PTR va)
{
	return sqrtf(va->x*va->x + va->y*va->y);
}

void VECTOR2D_Normalize(VECTOR2D_PTR va)
{
	float det = VECTOR2D_Length(va);
	if (fabs(det) > EPSILON_E6)
	{
		va->x /= det;
		va->y /= det;
	}
}

void VECTOR2D_Normalize(VECTOR2D_PTR va, VECTOR2D_PTR vn)
{
	float det = VECTOR2D_Length(va);
	if (det > EPSILON_E6)
	{
		vn->x = va->x / det;
		vn->y = va->y / det;
	}
}

void VECTOR2D_Build(VECTOR2D_PTR init, VECTOR2D_PTR term, VECTOR2D_PTR result)
{
	result->x = term->x - init->x;
	result->y = term->y - init->y;
}

float VECTOR2D_CosTh(VECTOR2D_PTR va, VECTOR2D_PTR vb)
{
	float a = VECTOR2D_Dot(va, vb);
	float b = VECTOR2D_Length(va) * VECTOR2D_Length(vb);
	if (b > EPSILON_E6)
		return acosf(a/b);
	else
		return 0.f;
}

void VECTPR2D_Print(VECTOR2D_PTR va, const char *name)
{
	fprintf(stderr, "VECTOR2D: %s, (%.3f, %.3f)\n", name, va->x, va->y);
}


// ---------------------------------------------------
// Vector 3D
// ---------------------------------------------------
void VECTOR3D_Add(VECTOR3D_PTR va, VECTOR3D_PTR vb, VECTOR3D_PTR vsum)
{
	vsum->x = va->x + vb->x;
	vsum->y = va->y + vb->y;
	vsum->z = va->z + vb->z;
}

VECTOR3D VECTOR3D_Add(VECTOR3D_PTR va, VECTOR3D_PTR vb)
{
	VECTOR3D vsum;
	VECTOR3D_Add(va, vb, &vsum);
	return vsum;
}

void VECTOR3D_Sub(VECTOR3D_PTR va, VECTOR3D_PTR vb, VECTOR3D_PTR vdiff)
{
	vdiff->x = va->x - vb->x;
	vdiff->y = va->y - vb->y;
	vdiff->z = va->z - vb->z;
}

VECTOR3D VECTOR3D_Sub(VECTOR3D_PTR va, VECTOR3D_PTR vb)
{
	VECTOR3D vdiff;
	VECTOR3D_Sub(va, vb, &vdiff);
	return vdiff;
}

void VECTOR3D_Scale(float k, VECTOR3D_PTR va)
{
	va->x = va->x * k;
	va->y = va->y * k;
	va->z = va->z * k;
}

void VECTOR3D_Scale(float k, VECTOR3D_PTR va, VECTOR3D_PTR vscaled)
{
	vscaled->x = va->x * k;
	vscaled->y = va->y * k;
	vscaled->z = va->z * k;
}

float VECTOR3D_Dot(VECTOR3D_PTR va, VECTOR3D_PTR vb)
{
	return va->x*vb->x + va->y*vb->y + va->z*vb->z;
}

float VECTOR3D_Length(VECTOR3D_PTR va)
{
	return sqrtf(va->x*va->x + va->y*va->y + va->z*va->z);
}

void VECTOR3D_Normalize(VECTOR3D_PTR va)
{
	float det = VECTOR3D_Length(va);
	if (det > EPSILON_E6)
	{
		va->x /= det;
		va->y /= det;
		va->z /= det;
	}
}

void VECTOR3D_Normalize(VECTOR3D_PTR va, VECTOR3D_PTR vn)
{
	float det = VECTOR3D_Length(va);
	if (det > EPSILON_E6)
	{
		vn->x = va->x / det;
		vn->y = va->y / det;
		vn->z = va->z / det;
	}
}

void VECTOR3D_Build(VECTOR3D_PTR init, VECTOR3D_PTR term, VECTOR3D_PTR result)
{
	result->x = term->x - init->x;
	result->y = term->y - init->y;
	result->z = term->z - init->z;
}

float VECTOR3D_CosTh(VECTOR3D_PTR va, VECTOR3D_PTR vb)
{
	float a = VECTOR3D_Dot(va, vb);
	float b = VECTOR3D_Length(va) * VECTOR3D_Length(vb);
	if (b > EPSILON_E6)
		return acosf(a/b);
	else
		return 0.f;
}

void VECTPR3D_Print(VECTOR3D_PTR va, const char *name)
{
	fprintf(stderr, "VECTOR3D: %s, (%.3f, %.3f, %.3f)\n", name,
		va->x, va->y, va->z);
}


// ---------------------------------------------------
// Vector 4D
// ---------------------------------------------------
void VECTOR4D_Add(VECTOR4D_PTR va, VECTOR4D_PTR vb, VECTOR4D_PTR vsum)
{
	vsum->x = va->x + vb->x;
	vsum->y = va->y + vb->y;
	vsum->z = va->z + vb->z;
	vsum->w = va->w + vb->w;
}

VECTOR4D VECTOR4D_Add(VECTOR4D_PTR va, VECTOR4D_PTR vb)
{
	VECTOR4D vsum;
	VECTOR4D_Add(va, vb, &vsum);
	return vsum;
}

void VECTOR4D_Sub(VECTOR4D_PTR va, VECTOR4D_PTR vb, VECTOR4D_PTR vdiff)
{
	vdiff->x = va->x - vb->x;
	vdiff->y = va->y - vb->y;
	vdiff->z = va->z - vb->z;
	vdiff->w = va->w - vb->w;
}

VECTOR4D VECTOR4D_Sub(VECTOR4D_PTR va, VECTOR4D_PTR vb)
{
	VECTOR4D vdiff;
	VECTOR4D_Sub(va, vb, &vdiff);
	return vdiff;
}

void VECTOR4D_Scale(float k, VECTOR4D_PTR va)
{
	va->x = va->x * k;
	va->y = va->y * k;
	va->z = va->z * k;
	va->w = va->w * k;
}

void VECTOR4D_Scale(float k, VECTOR4D_PTR va, VECTOR4D_PTR vscaled)
{
	vscaled->x = va->x * k;
	vscaled->y = va->y * k;
	vscaled->z = va->z * k;
	vscaled->w = va->w * k;
}

float VECTOR4D_Dot(VECTOR4D_PTR va, VECTOR4D_PTR vb)
{
	return va->x*vb->x + va->y*vb->y + va->z*vb->z + va->w*vb->w;
}

float VECTOR4D_Length(VECTOR4D_PTR va)
{
	return sqrtf(va->x*va->x + va->y*va->y + va->z*va->z + va->w*va->w);
}

void VECTOR4D_Normalize(VECTOR4D_PTR va)
{
	float det = VECTOR4D_Length(va);
	if (det > EPSILON_E6)
	{
		va->x /= det;
		va->y /= det;
		va->z /= det;
		va->w /= det;
	}
}

void VECTOR4D_Normalize(VECTOR4D_PTR va, VECTOR4D_PTR vn)
{
	float det = VECTOR4D_Length(va);
	if (det > EPSILON_E6)
	{
		vn->x = va->x / det;
		vn->y = va->y / det;
		vn->z = va->z / det;
		vn->w = va->w / det;
	}
}

void VECTOR4D_Build(VECTOR4D_PTR init, VECTOR4D_PTR term, VECTOR4D_PTR result)
{
	result->x = term->x - init->x;
	result->y = term->y - init->y;
	result->z = term->z - init->z;
	result->w = term->w - init->w;
}

float VECTOR4D_CosTh(VECTOR4D_PTR va, VECTOR4D_PTR vb)
{
	float a = VECTOR4D_Dot(va, vb);
	float b = VECTOR4D_Length(va) * VECTOR4D_Length(vb);
	if (b > EPSILON_E6)
		return acosf(a/b);
	else
		return 0.f;
}

void VECTPR4D_Print(VECTOR4D_PTR va, const char *name)
{
	fprintf(stderr, "VECTOR4D: %s, (%.3f, %.3f, %.3f, %.3f)\n", name,
		va->x, va->y, va->z, va->w);
}


// ---------------------------------------------------
// Matrix 2x2
// ---------------------------------------------------

void Mat_Init_2X2(MATRIX2X2_PTR ma, float m00, float m01, float m10, float m11)
{
	ma->M00 = m00;
	ma->M01 = m01;
	ma->M10 = m10;
	ma->M11 = m11;
}

void Print_Mat_2X2(MATRIX2X2_PTR ma, const char *name)
{
	fprintf(stderr, "MATRIX2X2: %s\n", name);
	fprintf(stderr, "[%.3f, %.3f]\n", ma->M00, ma->M01);
	fprintf(stderr, "[%.3f, %.3f]\n", ma->M10, ma->M11);
}

float Mat_Det_2X2(MATRIX2X2_PTR m)
{
	return (m->M00*m->M11 - m->M01*m->M10);
}

void Mat_Add_2X2(MATRIX2X2_PTR ma, MATRIX2X2_PTR mb, MATRIX2X2_PTR msum)
{
	msum->M00 = ma->M00 + mb->M00;
	msum->M01 = ma->M01 + mb->M01;
	msum->M10 = ma->M10 + mb->M10;
	msum->M11 = ma->M11 + mb->M11;
}

void Mat_Mul_2X2(MATRIX2X2_PTR ma, MATRIX2X2_PTR mb, MATRIX2X2_PTR mprod)
{
	mprod->M00 = ma->M00*mb->M00 + ma->M01*mb->M10;
	mprod->M01 = ma->M00*mb->M01 + ma->M01*mb->M11;
	mprod->M10 = ma->M10*mb->M00 + ma->M11*mb->M10;
	mprod->M11 = ma->M10*mb->M01 + ma->M11*mb->M11;
}

bool Mat_Inverse_2X2(MATRIX2X2_PTR m, MATRIX2X2_PTR mi)
{
	float det = Mat_Det_2X2(m);
	if (fabs(det) < EPSILON_E6)
		return false;

	mi->M00 = m->M11 / det;
	mi->M01 = -m->M01 / det;
	mi->M10 = -m->M10 / det;
	mi->M11 = m->M00 / det;
	return true;
}

bool Solve_2X2_System(MATRIX2X2_PTR A, MATRIX1X2_PTR X, MATRIX1X2_PTR B)
{
	MATRIX2X2 Ai;
	if (!Mat_Inverse_2X2(A, &Ai))
		return false;

	X->M00 = Ai.M00*B->M00 + Ai.M01*B->M01;
	X->M01 = Ai.M10*B->M00 + Ai.M11*B->M01;
	return true;
}


// ---------------------------------------------------
// Matrix 3x3
// ---------------------------------------------------
void Mat_Init_3X3(MATRIX3X3_PTR ma,
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22)
{
	ma->M00 = m00;
	ma->M01 = m01;
	ma->M02 = m02;
	ma->M10 = m10;
	ma->M11 = m11;
	ma->M12 = m12;
	ma->M20 = m20;
	ma->M21 = m21;
	ma->M22 = m22;
}

void Mat_Mul_3X3(MATRIX3X3_PTR ma, MATRIX3X3_PTR mb, MATRIX3X3_PTR mprod)
{
	mprod->M00 = ma->M00*mb->M00 + ma->M01*mb->M10 + ma->M02*mb->M20;
	mprod->M01 = ma->M00*mb->M01 + ma->M01*mb->M11 + ma->M02*mb->M21;
	mprod->M02 = ma->M00*mb->M02 + ma->M01*mb->M12 + ma->M02*mb->M22;
	mprod->M10 = ma->M10*mb->M00 + ma->M11*mb->M10 + ma->M12*mb->M20;
	mprod->M11 = ma->M10*mb->M01 + ma->M11*mb->M11 + ma->M12*mb->M21;
	mprod->M12 = ma->M10*mb->M02 + ma->M11*mb->M12 + ma->M12*mb->M22;
	mprod->M20 = ma->M20*mb->M00 + ma->M21*mb->M10 + ma->M22*mb->M20;
	mprod->M21 = ma->M20*mb->M01 + ma->M21*mb->M11 + ma->M22*mb->M21;
	mprod->M22 = ma->M20*mb->M02 + ma->M21*mb->M12 + ma->M22*mb->M22;
}

void Mat_Add_3X3(MATRIX3X3_PTR ma, MATRIX3X3_PTR mb, MATRIX3X3_PTR msum)
{
	msum->M00 = ma->M00 + mb->M00;
	msum->M01 = ma->M01 + mb->M01;
	msum->M02 = ma->M02 + mb->M02;
	msum->M10 = ma->M10 + mb->M10;
	msum->M11 = ma->M11 + mb->M11;
	msum->M12 = ma->M12 + mb->M12;
	msum->M20 = ma->M20 + mb->M20;
	msum->M21 = ma->M21 + mb->M21;
	msum->M22 = ma->M22 + mb->M22;
}

void Mat_Mul_VECTOR3D_3X3(VECTOR3D_PTR va, MATRIX3X3_PTR mb, VECTOR3D_PTR vprod)
{
	vprod->x = va->x*mb->M00 + va->y*mb->M10 + va->z*mb->M20;
	vprod->y = va->x*mb->M01 + va->y*mb->M11 + va->z*mb->M21;
	vprod->z = va->x*mb->M02 + va->y*mb->M12 + va->z*mb->M22;
}

float Mat_Det_3X3(MATRIX3X3_PTR m)
{
	return m->M00*m->M11*m->M22 + m->M01*m->M12*m->M20 + m->M02*m->M10*m->M21 -
		m->M02*m->M11*m->M20 - m->M01*m->M10*m->M22 - m->M00*m->M12*m->M21;
}

bool Mat_Inverse_3X3(MATRIX3X3_PTR m, MATRIX3X3_PTR mi)
{
	float det = Mat_Det_3X3(m);
	if (fabs(det) < EPSILON_E6)
		return false;

	mi->M00 = (m->M11*m->M22 - m->M12*m->M21) / det;
	mi->M01 = (m->M02*m->M21 - m->M01*m->M22) / det;
	mi->M02 = (m->M01*m->M12 - m->M02*m->M11) / det;
	mi->M10 = (m->M12*m->M20 - m->M10*m->M22) / det;
	mi->M11 = (m->M00*m->M22 - m->M02*m->M20) / det;
	mi->M12 = (m->M02*m->M10 - m->M00*m->M12) / det;
	mi->M20 = (m->M10*m->M21 - m->M11*m->M20) / det;
	mi->M21 = (m->M01*m->M20 - m->M00*m->M21) / det;
	mi->M22 = (m->M00*m->M11 - m->M01*m->M10) / det;
	return true;
}

bool Solve_3X3_System(MATRIX3X3_PTR A, MATRIX1X3_PTR X, MATRIX1X3_PTR B)
{
	MATRIX3X3 m;
	float dx, dy, dz;
	float det = Mat_Det_3X3(A);
	if (fabs(det) < EPSILON_E6)
		return false;

	Mat_Init_3X3(&m,
		B->M00, A->M01, A->M02,
		B->M01, A->M11, A->M12,
		B->M02, A->M21, A->M22);
	dx = Mat_Det_3X3(&m);

	Mat_Init_3X3(&m,
		A->M00, B->M00, A->M02,
		A->M10, B->M01, A->M12,
		A->M20, B->M02, A->M22);
	dy = Mat_Det_3X3(&m);

	Mat_Init_3X3(&m,
		A->M00, A->M01, B->M00,
		A->M10, A->M11, B->M01,
		A->M20, A->M21, B->M02);
	dz = Mat_Det_3X3(&m);

	X->M00 = dx / det;
	X->M01 = dy / det;
	X->M02 = dz / det;
	return true;
}

void Print_Mat_3X3(MATRIX3X3_PTR ma, const char *name)
{
	fprintf(stderr, "MATRIX3X3: %s\n", name);
	fprintf(stderr, "[%.3f, %.3f, %.3f]\n", ma->M00, ma->M01, ma->M02);
	fprintf(stderr, "[%.3f, %.3f, %.3f]\n", ma->M10, ma->M11, ma->M12);
	fprintf(stderr, "[%.3f, %.3f, %.3f]\n", ma->M20, ma->M21, ma->M22);
}


// ---------------------------------------------------
// Matrix 4x4
// ---------------------------------------------------
void Mat_Init_4X4(MATRIX4X4_PTR ma,
					float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33)
{
	ma->M00 = m00;
	ma->M01 = m01;
	ma->M02 = m02;
	ma->M03 = m03;
	ma->M10 = m10;
	ma->M11 = m11;
	ma->M12 = m12;
	ma->M13 = m13;
	ma->M20 = m20;
	ma->M21 = m21;
	ma->M22 = m22;
	ma->M23 = m23;
	ma->M30 = m30;
	ma->M31 = m31;
	ma->M32 = m32;
	ma->M33 = m33;
}

void Mat_Add_4X4(MATRIX4X4_PTR ma, MATRIX4X4_PTR mb, MATRIX4X4_PTR msum)
{
	msum->M00 = ma->M00 + mb->M00;
	msum->M01 = ma->M01 + mb->M01;
	msum->M02 = ma->M02 + mb->M02;
	msum->M03 = ma->M03 + mb->M03;
	msum->M10 = ma->M10 + mb->M10;
	msum->M11 = ma->M11 + mb->M11;
	msum->M12 = ma->M12 + mb->M12;
	msum->M13 = ma->M13 + mb->M13;
	msum->M20 = ma->M20 + mb->M20;
	msum->M21 = ma->M21 + mb->M21;
	msum->M22 = ma->M22 + mb->M22;
	msum->M23 = ma->M23 + mb->M23;
	msum->M30 = ma->M30 + mb->M30;
	msum->M31 = ma->M31 + mb->M31;
	msum->M32 = ma->M32 + mb->M32;
	msum->M33 = ma->M33 + mb->M33;
}

void Print_Mat_4X4(MATRIX4X4_PTR ma, char *name)
{
	fprintf(stderr, "MATRIX4X4: %s\n", name);
	fprintf(stderr, "[%.3f, %.3f, %.3f, %.3f]\n", ma->M00, ma->M01, ma->M02, ma->M03);
	fprintf(stderr, "[%.3f, %.3f, %.3f, %.3f]\n", ma->M10, ma->M11, ma->M12, ma->M13);
	fprintf(stderr, "[%.3f, %.3f, %.3f, %.3f]\n", ma->M20, ma->M21, ma->M22, ma->M23);
	fprintf(stderr, "[%.3f, %.3f, %.3f, %.3f]\n", ma->M30, ma->M31, ma->M32, ma->M33);
}


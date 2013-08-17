#ifndef T3D_MATH_H
#define T3D_MATH_H

#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------
// Vectors
// ---------------------------------------------------
typedef union VECTOR2D_TYP
{
	float M[2];
	struct { float x, y; };
} VECTOR2D, POINT2D, *VECTOR2D_PTR, *POINT2D_PTR;

typedef union VECTOR3D_TYP
{
	float M[3];
	struct { float x, y, z; };
} VECTOR3D, POINT3D, *VECTOR3D_PTR, *POINT3D_PTR;

typedef union VECTOR4D_TYP
{
	float M[4];
	struct { float x, y, z, w; };
} VECTOR4D, POINT4D, *VECTOR4D_PTR, *POINT4D_PTR;


// ---------------------------------------------------
// Lines
// ---------------------------------------------------
typedef struct PARMLINE2D_TYP
{
	POINT2D p0;
	POINT2D p1;
	VECTOR2D v; // direction vector of line segment, |v| = |p1 - p0|
} PARMLINE2D, *PARMLINE2D_PTR;

typedef struct PARMLINE3D_TYP
{
	POINT3D p0;
	POINT3D p1;
	VECTOR3D v; // direction vector of line segment, |v| = |p1 - p0|
} PARMLINE3D, *PARMLINE3D_PTR;


// ---------------------------------------------------
// Plane
// ---------------------------------------------------
typedef struct PLANE3D_TYP
{
	POINT3D p0;	// point on the plane
	VECTOR3D n;	// normal to the plane (not necessarily a unit vector)
} PLANE3D, *PLANE3D_PTR;


// ---------------------------------------------------
// Matrices
// ---------------------------------------------------
typedef union MATRIX4X4_TYP
{
	float M[4][4];
	struct
	{
		float M00, M01, M02, M03;
		float M10, M11, M12, M13;
		float M20, M21, M22, M23;
		float M30, M31, M32, M33;
	};
} MATRIX4X4, *MATRIX4X4_PTR;

typedef union MATRIX4X3_TYP
{
	float M[4][3];
	struct
	{
		float M00, M01, M02;
		float M10, M11, M12;
		float M20, M21, M22;
		float M30, M31, M32;
	};
} MATRIX4X3, *MATRIX4X3_PTR;

typedef union MATRIX1X4_TYP
{
	float M[4];
	struct { float M00, M01, M02, M03; };
} MATRIX1X4, *MATRIX1X4_PTR;

typedef union MATRIX3X3_TYP
{
	float M[3][3];
	struct
	{
		float M00, M01, M02;
		float M10, M11, M12;
		float M20, M21, M22;
	};
} MATRIX3X3, *MATRIX3X3_PTR;

typedef union MATRIX1X3_TYP
{
	float M[3];
	struct { float M00, M01, M02; };
} MATRIX1X3, *MATRIX1X3_PTR;

typedef union MATRIX3X2_TYP
{
	float M[3][2];
	struct
	{
		float M00, M01;
		float M10, M11;
		float M20, M21;
	};
} MATRIX3X2, *MATRIX3X2_PTR;

typedef union MATRIX2X2_TYP
{
	float M[2][2];
	struct
	{
		float M00, M01;
		float M10, M11;
	};
} MATRIX2X2, *MATRIX2X2_PTR;

typedef union MATRIX1X2_TYP
{
	float M[2];
	struct { float M00, M01; };
} MATRIX1X2, *MATRIX1X2_PTR;

// ---------------------------------------------------
// Quaternion
// ---------------------------------------------------
typedef struct QUAT_TYP
{
	union
	{
		float M[4];
		struct
		{
			float q0;			// the real part
			VECTOR3D qv;	// the imaginary part xi + yj + zk
		};
		struct
		{
			float w, x, y, z;
		};
	};
} QUAT, *QUAT_PTR;


// ---------------------------------------------------
// Coordinates
// ---------------------------------------------------

// 2D polar
//        ^
//        |----+ (x, y)
//        |   *|
//        |  * |
//        | *  |
//        |*t  |
// -------+--------->
//        |
// t == theta
// length of * == r
// x = r * sin(theta)
// y = r * cos(theta)
typedef struct POLAR2D_TYP
{
	float r;
	float theta;	// the angles in rads
} POLAR2D, *POLAR2D_PTR;

// 3D cylindrical
typedef struct CYLINDRICAL3D_TYP
{
	float r;
	float theta;
	float z;			// the z-height of the point
} CYLINDRICAL3D, *CYLINDRICAL3D_PTR;

// 3D spherical
typedef struct SPHERICAL3D_TYP
{
	float p;			// rho, the distance to the point from the origin
	float theta;	// the angle from the z-axis and the line segment o->p
	float phi;		// the angle from the projection if o->p onto the x-y plane and the x-axis
} SPHERICAL3D, *SPHERICAL3D_PTR;


// ---------------------------------------------------
// Fixed Point
// ---------------------------------------------------

// | whole part (16-bit) | decimal part (16-bit) |
typedef int FIXP16;
typedef int *FIXP16_PTR;


// ---------------------------------------------------
// Math constants
// ---------------------------------------------------

// pi defines
#define PI					(3.141592654f)
#define PI2					(6.283185307f)
#define PI_DIV_2		(1.570796327f)
#define	PI_DIV_4		(0.785398163f)
#define PI_INV			(0.318309886f)

// fixed point math constants
#define FIXP16_SHIFT			16
#define FIXP16_MAG				65536
#define FIXP16_DP_MASK		0x0000ffff
#define FIXP16_WP_MASK		0xffff0000
#define FIXP16_ROUND_UP		0x00008000

// defines for small numbers
#define EPSILON_E4		((float)(1e-4))
#define EPSILON_E5		((float)(1e-5))
#define	EPSILON_E6		((float)(1e-6))
inline bool almostEqual(float a, float b)
{
	float v = (a > b) ? (a - b) : (b - a);
	return v < EPSILON_E6;
}

// defines for parametric line intersections
#define PARM_LINE_NO_INTERSECT						0
#define PARM_LINE_INTERSECT_IN_SEGMENT		1
#define	PARM_LINE_INTERSECT_OUT_SEGMENT		2
#define	PARM_LINE_INTERSECT_EVERYWHERE		3

// identity matrices

// 4x4 identity matrix
const MATRIX4X4 IMAT_4X4 = {{
	{1,0,0,0,},
	{0,1,0,0,},
	{0,0,1,0,},
	{0,0,0,1,},
}};

// 4x3 identity matrix (note this is not correct mathematically)
// but later we may use 4x3 matrices with the assumption that
// the last column is always [0 0 0 1]t
const MATRIX4X3 IMAT_4X3 = {{
	{1,0,0,},
	{0,1,0,},
	{0,0,1,},
	{0,0,0,},
}};

// 3x3 identity matrix
const MATRIX3X3 IMAT_3X3 = {{
	{1,0,0,},
	{0,1,0,},
	{0,0,1,},
}};

// 2x3 identity matrix
const MATRIX2X2 IMAT_2X2 = {{
	{1,0,},
	{0,1,},
}};


// ---------------------------------------------------
// Utility
// ---------------------------------------------------

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define SWAP(a, b, t) {t=a; a=b; b=t;}

#define DEG_TO_RAD(ang)  ((ang)*PI/180.0f)
#define RAD_TO_DEG(rads) ((rads)*180.0f/PI)

#define RAND_RANGE(x,y)  ((x) + (rand()%((y)-(x)+1)))


// ---------------------------------------------------
// Vector/Point Func
// ---------------------------------------------------

inline void VECTOR2D_ZERO(VECTOR2D_PTR v)
{ (v)->x = (v)->y = 0.0f; }

inline void VECTOR3D_ZERO(VECTOR3D_PTR v)
{ (v)->x = (v)->y = (v)->z = 0.0f; }

inline void VECTOR4D_ZERO(VECTOR4D_PTR v)
{ (v)->x = (v)->y = (v)->z = 0.0f; (v)->w = 1.0f; }

// initialize vectors with explicit components
inline void VECTOR2D_INITXY(VECTOR2D_PTR v, float x, float y)
{ (v)->x = (x); (v)->y = (y); }

inline void VECTOR3D_INITXY(VECTOR3D_PTR v, float x, float y, float z)
{ (v)->x = (x); (v)->y = (y); (v)->z = (z); }

inline void VECTOR4D_INITXY(VECTOR4D_PTR v, float x, float y, float z)
{ (v)->x = (x); (v)->y = (y); (v)->z = (z); (v)->w = 1.0f; }

// initialize with other vectors
inline void VECTOR2D_INIT(VECTOR2D_PTR vdst, VECTOR2D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; }

inline void VECTOR3D_INIT(VECTOR3D_PTR vdst, VECTOR3D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; }

inline void VECTOR4D_INIT(VECTOR4D_PTR vdst, VECTOR4D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; (vdst)->w = (vsrc)->w; }

// vector copying
inline void VECTOR2D_COPY(VECTOR2D_PTR vdst, VECTOR2D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; }

inline void VECTOR3D_COPY(VECTOR3D_PTR vdst, VECTOR3D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; }

inline void VECTOR4D_COPY(VECTOR4D_PTR vdst, VECTOR4D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; (vdst)->w = (vsrc)->w; }

// point initialization
inline void POINT2D_INIT(POINT2D_PTR vdst, POINT2D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; }

inline void POINT3D_INIT(POINT3D_PTR vdst, POINT3D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; }

inline void POINT4D_INIT(POINT4D_PTR vdst, POINT4D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; (vdst)->w = (vsrc)->w; }

// point copying
inline void POINT2D_COPY(POINT2D_PTR vdst, POINT2D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; }

inline void POINT3D_COPY(POINT3D_PTR vdst, POINT3D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; }

inline void POINT4D_COPY(POINT4D_PTR vdst, POINT4D_PTR vsrc)
{ (vdst)->x = (vsrc)->x; (vdst)->y = (vsrc)->y; (vdst)->z = (vsrc)->z; (vdst)->w = (vsrc)->w; }


// ---------------------------------------------------
// Matrix Func
// ---------------------------------------------------

#define MAT_ZERO_2X2(m) { memset((void*)(m), 0, sizeof(MATRIX2X2)); }
#define MAT_ZERO_3X3(m) { memset((void*)(m), 0, sizeof(MATRIX3X3)); }
#define MAT_ZERO_4X4(m) { memset((void*)(m), 0, sizeof(MATRIX4X4)); }
#define MAT_ZERO_4X3(m) { memset((void*)(m), 0, sizeof(MATRIX4X3)); }

#define MAT_IDENTITY_2X2(m) { memcpy((void*)(m), (void*)&MAT_2X2, sizeof(MATRIX2X2)); }
#define MAT_IDENTITY_3X3(m) { memcpy((void*)(m), (void*)&MAT_3X3, sizeof(MATRIX3X3)); }
#define MAT_IDENTITY_4X4(m) { memcpy((void*)(m), (void*)&MAT_4X4, sizeof(MATRIX4X4)); }
#define MAT_IDENTITY_4X3(m) { memcpy((void*)(m), (void*)&MAT_4X3, sizeof(MATRIX4X3)); }

#define MAT_COPY_2X2(src, dest) { memcpy((void*)(dest), (void*)(src), sizeof(MATRIX2X2)); }
#define MAT_COPY_3X3(src, dest) { memcpy((void*)(dest), (void*)(src), sizeof(MATRIX3X3)); }
#define MAT_COPY_4X4(src, dest) { memcpy((void*)(dest), (void*)(src), sizeof(MATRIX4X4)); }
#define MAT_COPY_4X3(src, dest) { memcpy((void*)(dest), (void*)(src), sizeof(MATRIX4X3)); }

inline void MAT_TRANSPOSE_ME_3X3(MATRIX3X3_PTR m)
{
	MATRIX3X3 mat;
	mat.M00 = m->M00; mat.M01 = m->M10; mat.M02 = m->M20;
	mat.M10 = m->M01; mat.M11 = m->M11; mat.M12 = m->M21;
	mat.M20 = m->M02; mat.M21 = m->M12; mat.M22 = m->M22;
	MAT_COPY_3X3(m, &mat);
}

inline void MAT_TRANSPOSE_ME_4X4(MATRIX4X4_PTR m)
{
	MATRIX4X4 mat;
	mat.M00 = m->M00; mat.M01 = m->M10; mat.M02 = m->M20; mat.M03 = m->M30;
	mat.M10 = m->M01; mat.M11 = m->M11; mat.M12 = m->M21; mat.M13 = m->M31;
	mat.M20 = m->M02; mat.M21 = m->M12; mat.M22 = m->M22; mat.M23 = m->M32;
	mat.M30 = m->M03; mat.M31 = m->M13; mat.M32 = m->M23; mat.M33 = m->M33;
	MAT_COPY_4X4(m, &mat);
}

inline void MAT_TRANSPOSE_3X3(MATRIX3X3_PTR m, MATRIX3X3_PTR mat)
{
	mat->M00 = m->M00; mat->M01 = m->M10; mat->M02 = m->M20;
	mat->M10 = m->M01; mat->M11 = m->M11; mat->M12 = m->M21;
	mat->M20 = m->M02; mat->M21 = m->M12; mat->M22 = m->M22;
}

inline void MAT_TRANSPOSE_4X4(MATRIX4X4_PTR m, MATRIX4X4_PTR mat)
{
	mat->M00 = m->M00; mat->M01 = m->M10; mat->M02 = m->M20; mat->M03 = m->M30;
	mat->M10 = m->M01; mat->M11 = m->M11; mat->M12 = m->M21; mat->M13 = m->M31;
	mat->M20 = m->M02; mat->M21 = m->M12; mat->M22 = m->M22; mat->M23 = m->M32;
	mat->M30 = m->M03; mat->M31 = m->M13; mat->M32 = m->M23; mat->M33 = m->M33;
}

inline void MAT_COLUMN_SWAP_2X2(MATRIX2X2_PTR m, int c, MATRIX1X2_PTR v)
{ m->M[0][c] = v->M[0]; m->M[1][c] = v->M[1]; }

inline void MAT_COLUMN_SWAP_3X3(MATRIX3X3_PTR m, int c, MATRIX1X3_PTR v)
{ m->M[0][c] = v->M[0]; m->M[1][c] = v->M[1]; m->M[2][c] = v->M[2]; }

inline void MAT_COLUMN_SWAP_4X4(MATRIX4X4_PTR m, int c, MATRIX1X4_PTR v)
{ m->M[0][c] = v->M[0]; m->M[1][c] = v->M[1]; m->M[2][c] = v->M[2]; m->M[3][c] = v->M[3]; }

inline void MAT_COLUMN_SWAP_4X3(MATRIX4X3_PTR m, int c, MATRIX1X4_PTR v)
{ m->M[0][c] = v->M[0]; m->M[1][c] = v->M[1]; m->M[2][c] = v->M[2]; }


// ---------------------------------------------------
// Quaternion Func
// ---------------------------------------------------

inline void QUAT_ZERO(QUAT_PTR q)
{ q->x = q->y = q->z = q->w = 0.0f; }

inline void QUAT_INITWXYZ(QUAT_PTR q, float w, float x, float y, float z)
{ q->w = w; q->x = x; q->y = y; q->z = z; }

inline void QUAT_INIT_VECTOR3D(QUAT_PTR q, VECTOR3D_PTR v)
{ q->w = 0.0f; q->x = v->x; q->y = v->y; q->z = v->z; }

inline void QUAT_INIT(QUAT_PTR qdst, QUAT_PTR qsrc)
{
	qdst->w = qsrc->w; qdst->x = qsrc->x;
	qdst->y = qsrc->y; qdst->z = qsrc->z;
}

inline void QUAT_COPY(QUAT_PTR qdst, QUAT_PTR qsrc)
{
	qdst->w = qsrc->w; qdst->x = qsrc->x;
	qdst->y = qsrc->y; qdst->z = qsrc->z;
}


// ---------------------------------------------------
// Fixed-Point Func
// ---------------------------------------------------

#define FIXP16_WP(fp)  ((fp) >> FIXP16_SHIFT)
#define FIXP16_DP(fp)  ((fp) && FIXP16_DP_MASK)

#define INT_TO_FIXP16(i)    ((i) << FIXP16_SHIFT)
#define FLOAT_TO_FIXP16(f)  ((FIXP16)((float)(f) * (float)FIXP16_MAG + 0.5))
#define FIXP16_TO_FLOAT(fp) (((float)fp)/FIXP16_MAG)


// ---------------------------------------------------
// Globals
// ---------------------------------------------------

void Build_Sin_Cos_Tables();
float Fast_Sin(float theta);
float Fast_Cos(float theta);

// polar, cylindrical, spherical functions
void POLAR2D_To_POINT2D(POLAR2D_PTR polar, POINT2D_PTR rect);
void POLAR2D_To_RectXY(POLAR2D_PTR polar, float *x, float *y);
void POINT2D_To_POLAR2D(POINT2D_PTR rect, POLAR2D_PTR polar);
void POINT2D_To_PolarRTh(POINT2D_PTR rect, float *r, float *theta);

void CYLINDRICAL3D_To_POINT3D(CYLINDRICAL3D_PTR cyl, POINT3D_PTR rect);
void CYLINDRICAL3D_To_RectXYZ(CYLINDRICAL3D_PTR cyl, float *x, float *y, float *z);
void POINT3D_To_CYLINDRICAL3D(POINT3D_PTR rect, CYLINDRICAL3D_PTR cyl);
void POINT3D_To_CylindricalRThZ(POINT3D_PTR rect, float *r, float *theta, float *z);

void SPHERICAL3D_To_POINT3D(SPHERICAL3D_PTR sph, POINT3D_PTR rect);
void SPHERICAL3D_To_RectXYZ(SPHERICAL3D_PTR sph, float *x, float *y, float *z);
void POINT3D_To_SPHERICAL3D(POINT3D_PTR rect, SPHERICAL3D_PTR sph);
void POINT3D_To_SphericalPThPh(POINT3D_PTR rect, float *p, float *theta, float *phi);

// 2d vector functions
void VECTOR2D_Add(VECTOR2D_PTR va, VECTOR2D_PTR vb, VECTOR2D_PTR vsum);
VECTOR2D VECTOR2D_Add(VECTOR2D_PTR va, VECTOR2D_PTR vb);
void VECTOR2D_Sub(VECTOR2D_PTR va, VECTOR2D_PTR vb, VECTOR2D_PTR vdiff);
VECTOR2D VECTOR2D_Sub(VECTOR2D_PTR va, VECTOR2D_PTR vb);
void VECTOR2D_Scale(float k, VECTOR2D_PTR va);
void VECTOR2D_Scale(float k, VECTOR2D_PTR va, VECTOR2D_PTR vscaled);
float VECTOR2D_Dot(VECTOR2D_PTR va, VECTOR2D_PTR vb);
float VECTOR2D_Length(VECTOR2D_PTR va);
//float VECTOR2D_Length_Fast(VECTOR2D_PTR va);
void VECTOR2D_Normalize(VECTOR2D_PTR va);
void VECTOR2D_Normalize(VECTOR2D_PTR va, VECTOR2D_PTR vn);
void VECTOR2D_Build(VECTOR2D_PTR init, VECTOR2D_PTR term, VECTOR2D_PTR result);
float VECTOR2D_CosTh(VECTOR2D_PTR va, VECTOR2D_PTR vb);
void VECTPR2D_Print(VECTOR2D_PTR va, const char *name);

// 3d vector functions
void VECTOR3D_Add(VECTOR3D_PTR va, VECTOR3D_PTR vb, VECTOR3D_PTR vsum);
VECTOR3D VECTOR3D_Add(VECTOR3D_PTR va, VECTOR3D_PTR vb);
void VECTOR3D_Sub(VECTOR3D_PTR va, VECTOR3D_PTR vb, VECTOR3D_PTR vdiff);
VECTOR3D VECTOR3D_Sub(VECTOR3D_PTR va, VECTOR3D_PTR vb);
void VECTOR3D_Scale(float k, VECTOR3D_PTR va);
void VECTOR3D_Scale(float k, VECTOR3D_PTR va, VECTOR3D_PTR vscaled);
float VECTOR3D_Dot(VECTOR3D_PTR va, VECTOR3D_PTR vb);
float VECTOR3D_Length(VECTOR3D_PTR va);
//float VECTOR3D_Length_Fast(VECTOR3D_PTR va);
void VECTOR3D_Normalize(VECTOR3D_PTR va);
void VECTOR3D_Normalize(VECTOR3D_PTR va, VECTOR3D_PTR vn);
void VECTOR3D_Build(VECTOR3D_PTR init, VECTOR3D_PTR term, VECTOR3D_PTR result);
float VECTOR3D_CosTh(VECTOR3D_PTR va, VECTOR3D_PTR vb);
void VECTPR3D_Print(VECTOR3D_PTR va, const char *name);

// 4d vector functions
void VECTOR4D_Add(VECTOR4D_PTR va, VECTOR4D_PTR vb, VECTOR4D_PTR vsum);
VECTOR4D VECTOR4D_Add(VECTOR4D_PTR va, VECTOR4D_PTR vb);
void VECTOR4D_Sub(VECTOR4D_PTR va, VECTOR4D_PTR vb, VECTOR4D_PTR vdiff);
VECTOR4D VECTOR4D_Sub(VECTOR4D_PTR va, VECTOR4D_PTR vb);
void VECTOR4D_Scale(float k, VECTOR4D_PTR va);
void VECTOR4D_Scale(float k, VECTOR4D_PTR va, VECTOR4D_PTR vscaled);
float VECTOR4D_Dot(VECTOR4D_PTR va, VECTOR4D_PTR vb);
float VECTOR4D_Length(VECTOR4D_PTR va);
//float VECTOR4D_Length_Fast(VECTOR4D_PTR va);
void VECTOR4D_Normalize(VECTOR4D_PTR va);
void VECTOR4D_Normalize(VECTOR4D_PTR va, VECTOR4D_PTR vn);
void VECTOR4D_Build(VECTOR4D_PTR init, VECTOR4D_PTR term, VECTOR4D_PTR result);
float VECTOR4D_CosTh(VECTOR4D_PTR va, VECTOR4D_PTR vb);
void VECTPR4D_Print(VECTOR4D_PTR va, const char *name);

// 2x2 matrix functions
void Mat_Init_2X2(MATRIX2X2_PTR ma, float m00, float m01, float m10, float m11);
void Print_Mat_2X2(MATRIX2X2_PTR ma, const char *name);
float Mat_Det_2X2(MATRIX2X2_PTR m);
void Mat_Add_2X2(MATRIX2X2_PTR ma, MATRIX2X2_PTR mb, MATRIX2X2_PTR msum);
void Mat_Mul_2X2(MATRIX2X2_PTR ma, MATRIX2X2_PTR mb, MATRIX2X2_PTR mprod);
bool Mat_Inverse_2X2(MATRIX2X2_PTR m, MATRIX2X2_PTR mi);
bool Solve_2X2_System(MATRIX2X2_PTR A, MATRIX1X2_PTR X, MATRIX1X2_PTR B);

// 3x3 matrix functions
void Mat_Init_3X2(MATRIX3X2_PTR ma,
				float m00, float m01,
				float m10, float m11,
				float m20, float m21);
void Mat_Mul_1X2_3X2(MATRIX1X2_PTR ma, MATRIX3X2_PTR mb, MATRIX1X2_PTR mprod);
void Mat_Mul_1X3_3X3(MATRIX1X3_PTR ma, MATRIX3X3_PTR mb, MATRIX1X3_PTR mprod);

void Mat_Init_3X3(MATRIX3X3_PTR ma,
				float m00, float m01, float m02,
				float m10, float m11, float m12,
				float m21, float m22, float m23);
void Mat_Mul_3X3(MATRIX3X3_PTR ma, MATRIX3X3_PTR mb, MATRIX3X3_PTR mprod);
void Mat_Add_3X3(MATRIX3X3_PTR ma, MATRIX3X3_PTR mb, MATRIX3X3_PTR msum);
void Mat_Mul_VECTOR3D_3X3(VECTOR3D_PTR va, MATRIX3X3_PTR mb, VECTOR3D_PTR vprod);
float Mat_Det_3X3(MATRIX3X3_PTR m);
bool Mat_Inverse_3X3(MATRIX3X3_PTR m, MATRIX3X3_PTR mi);
bool Solve_3X3_System(MATRIX3X3_PTR A, MATRIX1X3_PTR X, MATRIX1X3_PTR B);
void Print_Mat_3X3(MATRIX3X3_PTR ma, const char *name);

// 4x4 matrix functions
void Mat_Add_4X4(MATRIX4X4_PTR ma, MATRIX4X4_PTR mb, MATRIX4X4_PTR msum);
void Mat_Mul_4X4(MATRIX4X4_PTR ma, MATRIX4X4_PTR mb, MATRIX4X4_PTR mprod);
void Mat_Mul_1X4_4X4(MATRIX1X4_PTR ma, MATRIX4X4_PTR mb, MATRIX1X4_PTR mprod);
void Mat_Mul_VECTOR3D_4X4(VECTOR3D_PTR va, MATRIX4X4_PTR mb, VECTOR3D_PTR vprod);
void Mat_Mul_VECTOR4D_4X4(VECTOR4D_PTR va, MATRIX4X4_PTR mb, VECTOR4D_PTR vprod);
bool Mat_Inverse_4X4(MATRIX4X4_PTR m, MATRIX4X4_PTR mi);
void Mat_Init_4X4(MATRIX4X4_PTR ma,
					float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33);
void Print_Mat_4X4(MATRIX4X4_PTR ma, char *name);

#endif

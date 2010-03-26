// geometry.h : interface file
//
// General purpose computational geometry wrapper class for MS VC++
//
// Author      : Chris Maunder (cmaunder@mail.com)
// Date        : First written sometime in 1998
//
// Copyright © Chris Maunder 1998-2002. All Rights Reserved                      
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage, in any form, caused
// by this code. Use it at your own risk and as with all code expect bugs!
// It's been tested but I'm not perfect.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file.

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>
#include <float.h>


/////////////////////////////////////////////////////////////////////////////////////////
// Specify what sort of floating point data type to use

//#define USING_DOUBLE		// double precision floating point (64 bit)
#define USING_FLOAT			// single precision floating point (32 bit)


#if defined(USING_DOUBLE)

#define DEG2RAD  0.0175			// converts degrees to radians
#define RAD2DEG  57.2957795		// ...and back again.
#define EPSILON  0.001			// used for REAL comparisons and stuff
#define PI		 3.1415926535898 // pi
#define HALF_PI  PI/2.0			// pi/2
#define TWO_PI	 PI*2.0			// pi*2
#define REAL_MAX DBL_MAX		// Max number that can be represented. 

#define REAL double
#define D2Real(x) (x)					// double => REAL
#define F2Real(x) (x)					// float  => REAL
#define Real2D(x) (x)					// REAL   => double
#define Real2F(x) ((float)(x))			// REAL   => float

#define Int2Real(x) ((double)(x))		// int	  => REAL

//#define Real2Int(x) ((int)(x))			// REAL   => int
inline int Real2Int(double d0)			// REAL   => int  (faster than a (cast)).			
{													
   static double intScale = 6755399441055744.0;		
   static double d1;								
   static int *pInt = (int*) &d1;					
													
   d1 = d0 + intScale;								
   return *pInt;									
}													

#elif defined(USING_FLOAT)

#define DEG2RAD  0.0175f			 // converts degrees to radians
#define RAD2DEG  57.2957795f		 // ...and back again.
#define EPSILON  0.001f			 // used for REAL comparisons and stuff
#define PI		 3.1415926535898f	 // pi
#define HALF_PI  PI/2.0f			 // pi/2
#define TWO_PI	 PI*2.0f			 // pi*2
#define REAL_MAX FLT_MAX

#define REAL float
#define D2Real(x) ((float)(x))			// double => REAL
#define F2Real(x) (x)					// float  => REAL
#define Real2D(x) (x)					// REAL   => double
#define Real2F(x) (x)					// REAL   => float

#define Int2Real(x) ((float)(x))		// int	  => REAL
//#define Real2Int(d) ((int)(d))			// REAL   => int

// First, some magic, borrowed from Terje Mathisen, to omit
// compiler drowsiness when converting float to int:
#pragma optimize( "", off )
inline long Real2Int(float d)
{
	const double S = 65536.0;
	const double Magic = (((S * S * 16) + (S*.5)) * S);
	double dtemp = Magic + d;
	return (*(long *)&dtemp) - 0x80000000;
}
#pragma optimize( "", on )

#elif
#error Must select USING_DOUBLE or USING_FLOAT in geometry.h
#endif

/////////////////////////////////////////////////////////////////////////////////////////

#define ABS(x) ((x) < D2Real(0.0) ? -(x) : (x))

class C3Point {
// Attributes
public:
	REAL x,y,z;

//Operations
public:
	C3Point() {}
	C3Point(double a, double b, double c) { x = D2Real(a); y = D2Real(b); z = D2Real(c); }

	REAL Length2()				  { return (x*x + y*y + z*z);					}
	REAL Length()				  { return D2Real(sqrt(x*x + y*y + z*z));		}
	void Scale(REAL factor)	      { x *= factor; y *= factor; z *= factor;		}
	void Normalise();			  

	void    operator=(C3Point& P)  { x = P.x; y = P.y; z = P.z;					} // assign
	C3Point operator-(C3Point P)  { return C3Point(x-P.x, y-P.y, z-P.z);		} // subtract
	C3Point operator-()			  { return C3Point(-x, -y, -z);					} // unary -
	C3Point operator+(C3Point P)  { return C3Point(x+P.x, y+P.y, z+P.z);		} // add
	C3Point operator+=(C3Point P) { x += P.x; y += P.y; z += P.z; return *this;	} // add +=
	C3Point operator-=(C3Point P) { x -= P.x; y -= P.y; z -= P.z; return *this;	} // subtract -=
	REAL    operator*(C3Point P)  { return x*P.x + y*P.y + z*P.z;				} // dot product
	C3Point operator*(REAL f)     { return C3Point(x*f, y*f, z*f);				} // scalar product
	C3Point operator/(REAL f)     { return C3Point(x/f, y/f, z/f);				} // scalar div
	C3Point operator*=(REAL f)    { x *= f; y *= f; z *= f; return *this;		} // scalar mult *=
	C3Point operator/=(REAL f)    { x /= f; y /= f; z /= f; return *this;		} // scalar div /=
	C3Point operator^(C3Point P)  {  return C3Point(y*P.z-P.y*z, P.x*z-x*P.z, x*P.y-P.x*y); } // cross product

	BOOL    operator==(C3Point& P);							  // is equal to?
	BOOL    operator!=(C3Point& P) { return !(*this == P); }  // is not equal to?
};

typedef struct {
	REAL x,y;
} C2Point;

#define VECTOR C3Point

class CPolygon // : public CObject
{
// Attributes
private:
	int		  m_n;					// Number of vertices
	C3Point  *m_point;				// array of C3Points defining vertices

// Operations
public:
	CPolygon();
	CPolygon(int);
	~CPolygon();

	BOOL    Closed();						// Is the polygon closed?

	int		GetSize() { return m_n; }		// Number of points
	BOOL	InSpan(int, int, int);			// is point in span of polygon?
	BOOL	InSpanProper(int, int, int);	// is point in span of polygon?
	BOOL	PointIn(C3Point P);				// Is point inside polygon?
	BOOL    SetSize(int);					// Change size of polygon
	void    RemoveAll() { SetSize(0); }		// Empty polygon of all points
	BOOL    Trim(int, int);					// Trim off ends of polygon
	BOOL    Close();						// Make polygon closed
	BOOL    Add(C3Point);					// Add point to polygon
	BOOL	SetAt(int nPos, C3Point& p);	// set point nPos as p
	void    Delete(int);					// Delete a vertex
	BOOL    InsertAt(int nPosition, C3Point P);	// insert point P at pos nPosition (0..m_n-1)
	void    FreeExtra();					// Free extra memory left over after deletes
	int		PointSeparation(int Point1, int Point2);	// Distance (in pts) between 2 points
	void    Rationalise(int);				// Combine colinear edges
	REAL    SegmentLength(int,int);			// Length of a segment of the polygon
	C3Point GetClosestPoint(C3Point p, int *nIndex = NULL);
	REAL    Area();							// returns polygon area
	C3Point Centroid();						// Calculate centroid of polygon
	BOOL	GetAttributes(REAL *pArea, C3Point *pCentroid, C3Point *pNorm,
						  REAL *pSlope, REAL *pAspect);
	BOOL    Diagonal(int, int);				// Is edge a diagonal?
	virtual void Translate(VECTOR v);		// Translate polygon
	BOOL    Intersected(C3Point& p1, C3Point& p2);		// Does p1-p2 intersect polygon?
	BOOL    IntersectedProp(C3Point& p1, C3Point& p2);	// Does p1-p2 intersect polygon properly?

	BOOL Triangulate(CPolygon*);			// Triangulate: Ear clip
	BOOL CPTriangulate(CPolygon*, C3Point);	// Central point triangulation
	BOOL DelauneyTri(CPolygon*);			// Triangulate: Delauney

	// Load polygon from X-Y or X-Y-Z data file
	BOOL LoadXY(LPCTSTR Filename, REAL Zdefault = D2Real(0.0));
	BOOL LoadXY(FILE* fp, REAL Zdefault = D2Real(0.0));
	BOOL LoadXYZ(LPCTSTR Filename, BOOL bWarn = TRUE);
	BOOL LoadXYZ(FILE* fp);
	BOOL Save(LPCTSTR Filename, BOOL bAsPoints = FALSE, BOOL bWarn = TRUE);

	void NaturalSpline(double*& b, double*& c, double*& d);
	REAL Curvature(int i);
	REAL Curvature(int nIndex, int nSampleSize);

	C3Point& operator[](int index);
	C3Point& Point(int index);
	void operator=(CPolygon& P);

private:
	BOOL Diagonalie(int, int);
	BOOL InCone(int, int);
};


inline REAL Dot(C3Point V1, C3Point V2) { return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z; }
inline C3Point Cross(C3Point p1, C3Point p2) { return C3Point(p1.y*p2.z - p2.y*p1.z, 
															  p2.x*p1.z - p1.x*p2.z, 
															  p1.x*p2.y - p2.x*p1.y); }

BOOL Xor(BOOL x, BOOL y);

C3Point GetClosestPoint2D(C3Point& start, C3Point& end, C3Point& P);
REAL   Angle(C3Point, C3Point, C3Point);
REAL   Angle(VECTOR v, VECTOR u);
REAL   TriArea2(C3Point, C3Point, C3Point);
REAL   TriArea2(VECTOR u, VECTOR v);
BOOL   IntersectProp(C3Point, C3Point, C3Point, C3Point);
BOOL   Left(C3Point, C3Point, C3Point);
BOOL   LeftOn(C3Point, C3Point, C3Point);
BOOL   Colinear(C3Point, C3Point, C3Point);
BOOL   Between(C3Point, C3Point, C3Point);
BOOL   Intersect(C3Point, C3Point, C3Point, C3Point);
VECTOR Normal(C3Point p1, C3Point p2, C3Point p3);
VECTOR Scale(REAL factor, VECTOR v);


///////////////////////////////////////////////////////////////////////////////////////////
// inline functions

inline C3Point& CPolygon::operator[](int index) 
{
	ASSERT(index >= 0 && index < m_n);
	return m_point[index];
}

inline C3Point& CPolygon::Point(int index) 
{
	ASSERT(index >= 0 && index < m_n);
	return m_point[index];
}

inline BOOL	CPolygon::SetAt(int nPos, C3Point& p)
{
	if (nPos < 0 || nPos >= m_n) return FALSE;
	m_point[nPos] = p;
	return TRUE;
}

inline BOOL Left(C3Point a, C3Point b, C3Point c) 
// Returns true iff c is strictly to the left of the directed line through a to b.
{
	//return TriArea2( a, b, c ) > D2Real(0.0);		 // inefficient
	REAL CrossZ = (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
	return (CrossZ > D2Real(0.0));
}

inline BOOL LeftOn(C3Point a, C3Point b, C3Point c)
{
	//return  TriArea2(a, b, c) >= D2Real(0.0);		// inefficient
	REAL CrossZ = (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
	return (CrossZ >= D2Real(0.0));
}

inline BOOL Colinear(C3Point a, C3Point b, C3Point c)
{
	// return (ABS(TriArea2(a, b, c)) < EPSILON);	// inefficient
	REAL CrossZ = (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
	return (ABS(CrossZ) < EPSILON);
}

inline BOOL CPolygon::IntersectedProp(C3Point& p1, C3Point& p2)
{
	REAL Length = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);

	for (int i = 0; i < m_n-1; i++) {
		REAL Distance = (p1.x - m_point[i].x)*(p1.x - m_point[i].x)
					+ (p1.y - m_point[i].y)*(p1.y - m_point[i].y);
		if (Distance > Length) continue;

		if (IntersectProp(p1,p2, m_point[i], m_point[i+1])) return TRUE;
	}
	return FALSE;
}

inline BOOL CPolygon::Intersected(C3Point& p1, C3Point& p2)
{
	REAL Length = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);

	for (int i = 0; i < m_n-1; i++) {
		REAL Distance = (p1.x - m_point[i].x)*(p1.x - m_point[i].x)
					+ (p1.y - m_point[i].y)*(p1.y - m_point[i].y);
		if (Distance > Length) continue;

		if (Intersect(p1,p2, m_point[i], m_point[i+1])) return TRUE;
	}
	return FALSE;
}

#endif

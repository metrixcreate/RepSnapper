// geometry.cpp : implementation file
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

#include "stdafx.h"
#include <math.h>
#include "utils.h"
#include "geometry.h"


C3Point GetClosestPoint2D(C3Point& start, C3Point& end, C3Point& P)
// returns the point on the line defined by [start,end] that is closest to point P
// All calculations are performed in the XY plane - Z coords are ignored.
// The point calculated may lie outside [start,end]
{
	if (ABS(start.x-end.x) < EPSILON)				// start-end form a vertical line
		return C3Point(start.x, P.y, start.z);
	
	if (ABS(end.y - start.y) < EPSILON)				// start-end form a horizontal line
		return C3Point(P.x, start.y, start.z);

	REAL Slope,Intercept, X;

	Slope = (end.y - start.y) / (end.x - start.x);
	Intercept = start.y - start.x*Slope;
	X = Slope/(Slope*Slope+1) * (P.y - Intercept + P.x/Slope);

	return C3Point(X, X*Slope + Intercept, start.z);
}

REAL Angle(C3Point p1, C3Point p2, C3Point p3)
// returns the angle (in degrees) between the 2 vectors formed from p2->p1, p2->p3.
{
	double cosA;
	C3Point v,u;

	v = p2-p1;
	u = p3-p2;

	cosA = u*v / D2Real( sqrt(Real2D( u.Length2()*v.Length2() )) ); 
	return D2Real(max(0.0, acos(cosA) * RAD2DEG));
}

REAL Angle(VECTOR v, VECTOR u)
// returns the angle (in degrees) between 2 vectors
{
	REAL cosA = u*v / D2Real( sqrt(Real2D( u.Length2()*v.Length2() )) ); 
	return D2Real(max(0.0, acos(cosA) * RAD2DEG));
}

VECTOR Normal(C3Point p1, C3Point p2, C3Point p3)
// Computs the normal (NOT unit normal) of a triangle, with points in CCW direction.
// CCW = Counter ClockWise
{
	return Cross(p2-p1, p3-p1);
}

REAL TriArea2(VECTOR u, VECTOR v)
// Calculates twice the area of the 3D triangle given by p1,p2,p3, Positive if CCW
{
	VECTOR CrossP = Cross(u,v);

	if (CrossP.z < D2Real(0.0))
		return -CrossP.Length();
	else
		return CrossP.Length();
}

REAL TriArea2(C3Point p1, C3Point p2, C3Point p3)
// Calculates twice the area of the 3D triangle given by p1,p2,p3, Positive if CCW
{
	VECTOR CrossP = Cross(p2-p1, p3-p1);

	if (CrossP.z < D2Real(0.0))
		return -CrossP.Length();
	else
		return CrossP.Length();
}

inline BOOL Xor(BOOL x, BOOL y)
// XOR: Arguments are negated to ensure that they are 0/1. Then the bitwise Xor operator may 
// apply.	(This idea is due to Michael Baldwin.)
{
	return	!x ^ !y;
}

BOOL IntersectProp(C3Point a, C3Point b, C3Point c, C3Point d)
// Returns true iff ab properly intersects cd: they share a point interior to both segments.
// The properness of the intersection is ensured by using strict leftness.
{
	/* Eliminate improper cases. */
	if (Colinear(a,b,c) || Colinear(a,b,d) || Colinear(c,d,a) ||Colinear(c,d,b))
		return FALSE;

    return Xor(Left(a,b,c), Left(a,b,d))&& Xor(Left(c,d,a), Left(c,d,b));
}

BOOL Between(C3Point a, C3Point b, C3Point c)
// Returns TRUE iff (a,b,c) are collinear and point c lies on the closed segement ab.
{
	if (!Colinear(a, b, c))
		return FALSE;

	/* If ab not vertical, check betweenness on x; else on y. */
	if (a.x != b.x) 
		return	((a.x <= c.x) && (c.x <= b.x)) ||
				((a.x >= c.x) && (c.x >= b.x));
	else
		return	((a.y <= c.y) && (c.y <= b.y)) ||
				((a.y >= c.y) && (c.y >= b.y));
}

BOOL Intersect(C3Point a, C3Point b, C3Point c, C3Point d)
// Returns true iff segments ab and cd intersect, properly or improperly.
{
	if (IntersectProp(a, b, c, d))
		return TRUE;
	else if (Between(a, b, c) || Between(a, b, d) || Between(c, d, a) || Between(c, d, b))
        return TRUE;
    else    
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// General C3Point/VECTOR operations

BOOL C3Point::operator==(C3Point& P)
{
	if (ABS(x - P.x) > EPSILON) return FALSE;
	if (ABS(y - P.y) > EPSILON) return FALSE;
	if (ABS(z - P.z) > EPSILON) return FALSE;
	return TRUE;
}

void C3Point::Normalise()
{
	REAL length = Length();
	if (length == D2Real(0.0)) return;
	Scale(D2Real(1.0)/length);
}

/////////////////////////////////////////////////////////////////////////////
// Class CPolygon - constructors, destructors and operations

CPolygon::CPolygon()
{
	m_point    = NULL;
	m_n		   = 0;
	//m_bFill	   = FALSE;
	//m_crColour = 0;
}

CPolygon::CPolygon(int n)
{
	if (!n) 
		m_point = NULL;
	else {
		m_point = (C3Point*) malloc(n*sizeof(C3Point));
		if (m_point == NULL) 
			AfxMessageBox("Unable to allocate sufficient memory for polygon");
	}

//	m_crColour = 0;
//	m_bFill    = FALSE;
	m_n = (m_point == NULL)? 0 : n;
}

CPolygon::~CPolygon()
{
	if (m_point != NULL) free(m_point);
	m_point = NULL;
	m_n = 0;
}

void CPolygon::operator=(CPolygon &P)
{
	if (this == &P) return;

	SetSize(P.GetSize());

	for (int i=0; i<GetSize(); i++) m_point[i] = P[i];
//	m_crColour = P.m_crColour; 
//	m_bFill    = P.m_bFill;
}

BOOL CPolygon::Closed()
{
	if (ABS(m_point[GetSize()-1].x - m_point[0].x) > EPSILON) return FALSE;
    if (ABS(m_point[GetSize()-1].y - m_point[0].y) > EPSILON) return FALSE;
	if (ABS(m_point[GetSize()-1].z - m_point[0].z) > EPSILON) return FALSE;
	return TRUE;
}

BOOL CPolygon::SetSize(int nSize)
{
	// Case 1: Set polygon as empty
	if (nSize == 0) {
		if (m_point) free(m_point);
		m_point = NULL;
		m_n = 0;
		return TRUE;
	}

	// Case 2: Allocate new memory for polygon
	if (m_point == NULL) {
		m_point = (C3Point*) malloc(nSize*sizeof(C3Point));
		if (m_point == NULL) {
			m_n = 0;
			return Error(NULL,"Low on memory: \nUnable to allocate memory for %d points.",nSize);
		} else {
			m_n = nSize;
			return TRUE;
		}
	}

	// Case 3: Resize existing polygon

	// Try and resize memory. If it doesn't work - leave polygon
	// how it was to begin with.
	C3Point* points = (C3Point*) realloc(m_point, nSize*sizeof(C3Point));
	if (points == NULL) 
		return Error(NULL,"Low on memory:\nUnable to resize polygon to %d points.",nSize);

	m_point = points;
	m_n = nSize;
	return TRUE;
}

// Trims polygon down so that points before "Start" and after "End" are removed.
// Start and End must be in the range 0..GetSize()-1
BOOL CPolygon::Trim(int Start, int End)
{
	ASSERT((End >=0) && (End < GetSize()));
	ASSERT((Start >=0) && (Start < GetSize()));

	if (!Start) 		// Easy case
		return SetSize(End+1);

	if (Start <= End) {
		SetSize(End+1);						// Remove end stuff
		for (int i = 0; i < Start; i++)		// Delete points less than Start
			Delete(i);
		return SetSize(GetSize());			// Remove extraneous stuff left at end
	}

	// Left with case where End < Start  i.e. a section including the 0 point is to be removed
	// Going to assume that the polygon is closed becuase only idiots cut out the centre of a 
	// non-closed polygon. ALTHOUGH - this is therefor highly likely, hence work needs to be done.

	for (int i = End; i<Start; i++)
		Delete(i);
	return SetSize(GetSize());
}

BOOL CPolygon::Close()
// Make polygon closed
{
	if (!Closed()) {
		if (!SetSize(GetSize()+1)) return FALSE;
		m_point[GetSize()-1] = m_point[0];
	}
	return TRUE;
}

BOOL CPolygon::Add(C3Point P)
// Add point to polygon
{
	if (!SetSize(GetSize()+1)) return FALSE;
	m_point[GetSize()-1] = P;
	return TRUE;
}

void CPolygon::Delete(int nPosition)
{
	for (int k = nPosition; k < GetSize()-1; k++) 
		m_point[k] = m_point[k+1];
	m_n--;
}

BOOL CPolygon::InsertAt(int nPosition, C3Point P)
{
	if (!SetSize(GetSize()+1)) return FALSE;
	for (int k = GetSize()-1; k > nPosition; k--) 
		m_point[k] = m_point[k-1];
	m_point[nPosition] = P;
	return TRUE;
}

inline void CPolygon::FreeExtra()
{
	SetSize(GetSize());
}

int CPolygon::PointSeparation(int Point1, int Point2)
{
	ASSERT(Point1 >= 0 && Point1 < GetSize());
	ASSERT(Point2 >= 0 && Point2 < GetSize());

	int nDistance;

	if (!Closed()) {
		nDistance = Point2 - Point1;
	} else {
		nDistance = abs(Point2 - Point1);
		nDistance = min(nDistance, abs(GetSize()-1 - nDistance));
	}
	return nDistance;
}

BOOL CPolygon::GetAttributes(REAL *pArea, C3Point *pCentroid, C3Point *pNorm,
							 REAL *pSlope, REAL *pAspect)
// Calculates and returns the polygons Area, centroid, norm, slope and aspect.
{
	C3Point SubMidPoint;
	REAL    SubArea;
	VECTOR  SubNorm;
	int nNumUniquePoints = (Closed())? GetSize()-1 : GetSize();

	*pArea     = D2Real(0.0);        // Partial area sum
	*pNorm     = C3Point( D2Real(0.0), D2Real(0.0), D2Real(0.0) );
	*pCentroid = C3Point( D2Real(0.0), D2Real(0.0), D2Real(0.0) );

	CPolygon P(nNumUniquePoints);	// Save current polygon
	if (!P.GetSize()) return FALSE;
	for (int i=0; i < P.GetSize(); i++) P[i] = m_point[i];

    // Start triangulating
	while (P.GetSize() > 3) {
		BOOL bCornerCut = FALSE;
		for (i = 0; i < P.GetSize(); i++ ) {

			int iPlus1 = i+1;        if (iPlus1 == P.GetSize()) iPlus1 = 0;
			int iPlus2 = (iPlus1+1); if (iPlus2 == P.GetSize()) iPlus2 = 0;
			
			if (P.Diagonal(i, iPlus2)) {

				SubArea     = TriArea2(P[i], P[iPlus1], P[iPlus2]);
				SubMidPoint = P[i] + P[iPlus1] + P[iPlus2];
				SubNorm		= Normal(P[i], P[iPlus1], P[iPlus2]);

				*pArea     += SubArea;
				*pCentroid += (SubMidPoint * SubArea);
				*pNorm	   += (SubNorm * SubArea);

				P.Delete(iPlus1);
				bCornerCut = TRUE;
				break;
			}
			if (Colinear(P[i], P[iPlus1], P[iPlus2])) {
				P.Delete(iPlus1);
				bCornerCut = TRUE;
				break;
			}
		}
		if (!bCornerCut) break;		// Couldn't cut at all!
	}

	// Should be left with a single triangle
	//ASSERT(P.GetSize() == 3);

	SubArea     = TriArea2(P[0], P[1], P[2]);	*pArea     += SubArea;
	SubMidPoint = P[0] + P[1] + P[2];			*pCentroid += (SubMidPoint * SubArea);
	SubNorm		= Normal(P[0], P[1], P[2]);		*pNorm	   += (SubNorm * SubArea);

	*pCentroid /= 3.0;
	pNorm->Normalise();

	if (*pArea > EPSILON) 		// Triangle or greater
		*pCentroid /= (*pArea);
	else 						// all points coincident or colinear, so get average
	{
		*pCentroid = C3Point( D2Real(0.0), D2Real(0.0), D2Real(0.0) );
		for (i=0; i<nNumUniquePoints; i++) *pCentroid += m_point[i];
		*pCentroid /= Int2Real(nNumUniquePoints);
	}
	*pArea = (*pArea < D2Real(0.0))? D2Real(-0.5) * *pArea : D2Real(0.5) * *pArea;

	// Slope ( Slope = 1/Slope(Norm) )
	if (pNorm->z < EPSILON)
		*pSlope = REAL_MAX;
	else
		*pSlope = D2Real(sqrt( Real2D(pNorm->x*pNorm->x + pNorm->y*pNorm->y))) / pNorm->z;
	
	// Aspect
	if (*pSlope < 0.01)
		*pAspect = D2Real(0.0);
	else {
		*pAspect = D2Real(atan2(Real2D(pNorm->y), Real2D(pNorm->x))) * RAD2DEG;
		*pAspect = D2Real(90.0) - *pAspect; 
		if (*pAspect < D2Real(0.0)) *pAspect += D2Real(360.0);
	}

	return TRUE;
}

REAL CPolygon::Area()
// Returns the area of the polygon.
{
	REAL sum = D2Real(0.0);        /* Partial area sum */

    for (int i = 1; i < GetSize()-1; i++)
         sum += TriArea2(m_point[0], m_point[i], m_point[i+1]);

	if (sum < D2Real(0.0)) sum = -sum;
    return D2Real(0.5) * sum;
}

C3Point CPolygon::Centroid()
{
	static REAL TotalArea;
	static C3Point Centre;

	Centre = C3Point( D2Real(0.0), D2Real(0.0), D2Real(0.0) );
	TotalArea = D2Real(0.0);

	for (int i=0; i < GetSize()-2; i++) {
		C3Point MidPoint = (Point(0) + Point(i+1) + Point(i+2)) / 3.0;
		REAL TArea = TriArea2(Point(0), Point(i+1), Point(i+2));

		MidPoint.Scale(TArea);		// Wieght current triangle midpoint by area.
		TotalArea += TArea;
		Centre    += MidPoint;
	}

	if (TotalArea > EPSILON) 		// Triangle or greater
	{
		Centre.Scale(D2Real(1.0) / TotalArea); 
		return Centre;
	}
	else 							// all points coincident or colinear
	{
		Centre = C3Point( D2Real(0.0), D2Real(0.0), D2Real(0.0) );
		if (Closed()) {
			for (i=0; i<GetSize()-1; i++) Centre += m_point[i];
			Centre.Scale(D2Real(1.0/(double)(GetSize()-1)));
		} else {
			for (i=0; i<GetSize(); i++) Centre += m_point[i];
			Centre.Scale(D2Real(1.0/(double)GetSize()));
		}
		return Centre;
	}
}

REAL CPolygon::SegmentLength(int start, int end)
{
	int i;
	REAL Width = D2Real(0.0);
	VECTOR v;

	if ((start < 0) || (end < 0) || (start >= GetSize()) || (end > GetSize())) 
		return Width;
	
	if (!start && (end == GetSize())) {		// Full perimeter length
		for (i = 0; i < GetSize()-1; i++) {
			v = m_point[i+1] - m_point[i];
			Width += v.Length();
		}
		v = m_point[0] - m_point[GetSize()-1];
		Width += v.Length();
		return Width;
	}

	if (start > end) {
		for (i = start; i < GetSize()-1; i++) {
			v = m_point[i+1] - m_point[i];
			Width += v.Length();
		}
		v = m_point[0] - m_point[GetSize()-1];
		Width += v.Length();
		for (i = 0; i < end; i++) {
			v = m_point[i+1] - m_point[i];
			Width += v.Length();
		}
	} else if (start < end) {
		for (int i = start; i < end; i++) {
			v = m_point[i+1] - m_point[i];
			Width += v.Length();
		}
	}
	// else right == left, so do nothing and return 0.0

	return Width;
}

// Given a C3Point, returns the nearest C3Point on the given polygon, with the option
// of also returning the index into the CPolygon point array of that point.
// Proximity is based on 2D, not 3D calculations.
C3Point CPolygon::GetClosestPoint(C3Point p, int *nIndex/*=NULL*/)
{
	REAL MinDistance = REAL_MAX;
	int index;

	for (int i = 0; i < GetSize(); i++) {
		REAL Distance =  (p.x - m_point[i].x)*(p.x - m_point[i].x)
					   + (p.y - m_point[i].y)*(p.y - m_point[i].y);
		if (Distance < MinDistance) {
			MinDistance = Distance;
			index = i;
		}
	}
	if (nIndex) *nIndex = index;
	return m_point[index];
}

BOOL CPolygon::Diagonalie(int i, int j)
// Returns TRUE iff (v_i, v_j) is a proper internal *or* external diagonal of this polygon, 
// *ignoring edges incident to v_i and v_j*.
{
	/* For each edge (k,k+1) of P */
	for (int k = 0; k < GetSize(); k++ ) {

		int kPlus1 = (k+1) % GetSize();

		/* Skip edges incident to i or j */
		if ( ! ((k == i) || (kPlus1 == i) || (k == j) || (kPlus1 == j)) )
			if (Intersect(m_point[i], m_point[j], m_point[k], m_point[kPlus1]))
				return	FALSE;
	}
	return	TRUE;
}

BOOL CPolygon::InCone(int i, int j)
// 	Returns true iff the diagonal (i,j) is striclty internal to the polygon in 
//  the neighborhood of the i endpoint.
{
	int	iPlus1  = (i + 1)       % GetSize();
	int	iMinus1 = (i + GetSize() - 1) % GetSize();

	/* If P[i] is a convex vertex [ i+1 left or on (i-1,i) ]. */
	if ( LeftOn(m_point[iMinus1], m_point[i], m_point[iPlus1]) )
		return	Left( m_point[i], m_point[j], m_point[iMinus1] )
		     &&	Left( m_point[j], m_point[i], m_point[iPlus1]  );

	/* Assume (i-1,i,i+1) not collinear. */
	/* else v_i is reflex. */
	else
		return	!(	LeftOn( m_point[i], m_point[j], m_point[iPlus1]  )
		            &&	LeftOn( m_point[j], m_point[i], m_point[iMinus1] ) );
}

BOOL CPolygon::Diagonal(int i, int j)
// Returns TRUE iff (v_i, v_j) is a proper internal diagonal of P.
{
	return InCone(i,j) && Diagonalie(i,j);
}

BOOL CPolygon::Triangulate(CPolygon* TriPoly)
// Triangulates this polygon and saves triangle edges in TriPoly.
// Triangles are stored CCW, with each set of 3 consecutive points in TriPoly
// representing 1 triangle.
// Assumes this polygon is closed.
{
	if (GetSize() < 4) return FALSE;

	if (!TriPoly->SetSize((GetSize()-3)*3))	 // Resize to max size needed, but set TriPoly.GetSize()=0
		return FALSE;						 // so it can be incremented in the loop.
	TriPoly->m_n = 0;						 // This is a paranoia kludge in case the trianglulation
											 // does not find all triangles needed.

	CPolygon P(GetSize()-1);				 // Save current polygon
	if (!P.GetSize()) return FALSE;
	for (int i=0; i < P.GetSize(); i++) P[i] = m_point[i];

    // Start triangulating
	while (P.GetSize() > 3) {
		BOOL bCornerCut = FALSE;
		for (i = 0; i < P.GetSize(); i++ ) {

			int iPlus1 = i+1;        if (iPlus1 == P.GetSize()) iPlus1 = 0;
			int iPlus2 = (iPlus1+1); if (iPlus2 == P.GetSize()) iPlus2 = 0;
			
			if (P.Diagonal(i, iPlus2)) {
				
				(*TriPoly)[TriPoly->m_n++] = P[i];
				(*TriPoly)[TriPoly->m_n++] = P[iPlus1];
				(*TriPoly)[TriPoly->m_n++] = P[iPlus2];
			
				P.Delete(iPlus1);
				bCornerCut = TRUE;
				break;
			}
			if (Colinear(P[i], P[iPlus1], P[iPlus2])) {
				P.Delete(iPlus1);
				bCornerCut = TRUE;
				break;
			}
		}
		if (!bCornerCut) {		// Error - bad poly
			TriPoly->SetSize(TriPoly->GetSize());		// resize to the actual size needed.
			return FALSE;
		}
	}

	// Should be left with a single triangle
	ASSERT(P.GetSize() == 3);
	(*TriPoly)[TriPoly->m_n++] = P[0];
	(*TriPoly)[TriPoly->m_n++] = P[1];
	(*TriPoly)[TriPoly->m_n++] = P[2];

	TriPoly->SetSize(TriPoly->GetSize());		// Now resize to the actual size needed.

	return TRUE;
}

BOOL CPolygon::CPTriangulate(CPolygon* TriPoly, C3Point C)
// Triangulates polygon P and saves triangle edges in TriPoly.
// Triangles are stored CCW, with each set of 3 consecutive points in TriPoly
// representing 1 triangle.
// Assumes polygon P is closed.
{		
	if (GetSize() == 4) {
		if (!TriPoly->SetSize(3)) return FALSE;
		for (int i=0; i<3; i++) (*TriPoly)[i] = m_point[i];
	} 
	else 
	{
		if (!TriPoly->SetSize((m_n-1)*3)) return FALSE;
		TriPoly->m_n = 0;
		for (int i = 0; i < (m_n-1); i++) {
			(*TriPoly)[(TriPoly->m_n)++] = C;
			(*TriPoly)[(TriPoly->m_n)++] = m_point[i];
			(*TriPoly)[(TriPoly->m_n)++] = m_point[i+1];
		}
	}
	return TRUE;
}

void CPolygon::Rationalise(int nAngle)
// Combines adjacent line segments if the angle between them is less than nAngle.
{
	for (int i=1; i<(GetSize()-1); i++) 
		if (Angle(m_point[i-1], m_point[i], m_point[i+1]) < nAngle)
			Delete(i);

	SetSize(GetSize());
}

void CPolygon::Translate(VECTOR v)
{
	for (int j=0; j<GetSize(); j++) m_point[j] += v;
}

BOOL CPolygon::InSpan(int start, int end, int index)
{
	if ((index < 0) || (index >= GetSize())) return FALSE;

	if (start <= end) 
		return ( (index >= start) && (index <= end) );

	// (start > end) => the section spanned by [start, end] crosses over the 0 point
	return !((index > end) && (index < start));

	// Alternate (longer) method
	//if ( ((index >= start) && (index <= GetSize())) || ((index >=0) && (index <= end)) )
	//	return TRUE;
	//return FALSE;
}	

BOOL CPolygon::InSpanProper(int start, int end, int index)
{
	if ((index < 0) || (index >= GetSize())) return FALSE;

	if (start <= end) 
		return ( (index > start) && (index < end) );

	// (start > end) => the section spanned by [start, end] crosses over the 0 point
	return !((index >= end) && (index <= start));
}	

BOOL CPolygon::PointIn(C3Point P)
// Tests if point within polygon, or on an edge or vertex, by shooting a ray along x axis
{
int     j, inside_flag, xflag0 ;
REAL    dv0 ;
int     crossings, yflag0, yflag1 ;
C3Point Vertex0, Vertex1;

	Vertex0 = m_point[GetSize()-1];

	/* get test bit for above/below Y axis */
    yflag0 = ( dv0 = Vertex0.y - P.y ) >= 0.0 ;

    crossings = 0 ;
    for ( j = 0 ; j < GetSize() ; j++ ) {

       // cleverness:  bobble between filling endpoints of edges, so
       // that the previous edge's shared endpoint is maintained.
       if ( j & 0x1 ) {
           Vertex0 = m_point[j] ;
           yflag0 = ( dv0 = Vertex0.y - P.y ) >= 0.0 ;
       } else {
           Vertex1 = m_point[j] ;
           yflag1 = ( Vertex1.y >= P.y ) ;
       }

       /* check if points not both above/below X axis - can't hit ray */
       if ( yflag0 != yflag1 ) {
            /* check if points on same side of Y axis */
            if ( ( xflag0 = ( Vertex0.x >= P.x ) ) == ( Vertex1.x >= P.x ) ) {

                    if ( xflag0 ) crossings++ ;
                } else {
                    /* compute intersection of pgon segment with X ray, note
                     * if > point's X.
                     */
                    crossings += (Vertex0.x -
                        dv0*( Vertex1.x-Vertex0.x)/(Vertex1.y-Vertex0.y)) >= P.x ;
                }
            }
        }

        // test if crossings is odd
        // if all we care about is winding number > 0, then just:
        //       inside_flag = crossings > 0;

		inside_flag = crossings & 0x01 ;

    return (inside_flag) ;
}

/* OR - (not so reliable)
  int i, j, right, inside = 0;
  for (i = 0, j = n-1; i < n; j = i++) {
    if ((y[i] <= Y) != (y[j]<= Y)) {
      if ((right = x[i] >= X) != (x[j] >= X)) {
        if ((X - x[i]) * (y[j] - y[i]) < (x[j] - x[i]) * (Y - y[i]))
          inside = !inside;
      }
      else if (right) inside = !inside; 
    }
  }
*/

BOOL CPolygon::DelauneyTri(CPolygon *TriPoly)
// 2D Delauney triangulation in the X-Y plane. (Z coordinates of polygon vertices ignored)
{
	int	i, j, k, m;					// indices of four points 
	REAL xn, yn, zn;				// outward vector normal to (i,j,k) 
	int	flag;						// TRUE if m above of (i,j,k) 
	REAL *z;

	ASSERT(GetSize() > 2);

	if (!TriPoly->SetSize((GetSize()-2)*3)) // Resize to max size needed, but set 
		return FALSE;						// TriPoly.m_n=0 so it can be incremented 
	TriPoly->m_n = 0;						// in the loop.	 						
		  
	z = new REAL[GetSize()];
	if (z == NULL) return FALSE;

	for (i=0; i<GetSize(); i++)	
		z[i] = m_point[i].x*m_point[i].x + m_point[i].y*m_point[i].y;

	// For each triple (i,j,k) 
	for ( i = 0; i < GetSize() - 2; i++ )
	for ( j = i + 1; j < GetSize(); j++ )
	for ( k = i + 1; k < GetSize(); k++ ) 
	if ( j != k ) {

		// Compute normal to triangle (i,j,k). 
		xn = (m_point[j].y-m_point[i].y)*(z[k]-z[i]) - (m_point[k].y-m_point[i].y)*(z[j]-z[i]);
		yn = (m_point[k].x-m_point[i].x)*(z[j]-z[i]) - (m_point[j].x-m_point[i].x)*(z[k]-z[i]);
		zn = (m_point[j].x-m_point[i].x)*(m_point[k].y-m_point[i].y) 
									 - (m_point[k].x-m_point[i].x)*(m_point[j].y-m_point[i].y);
		flag = (zn < 0);
		if (flag)		// Only examine faces on bottom of paraboloid: zn < 0.
			for (m = 0; m < GetSize(); m++)	// For each other point m check if m above (i,j,k).
				flag = flag && 
				         ((m_point[m].x-m_point[i].x)*xn + 
								(m_point[m].y-m_point[i].y)*yn + (z[m]-z[i])*zn <= 0);
		if (flag) {
			(*TriPoly)[TriPoly->m_n++] = m_point[i];
			(*TriPoly)[TriPoly->m_n++] = m_point[j];
			(*TriPoly)[TriPoly->m_n++] = m_point[k];
		}
	}
	delete [] z;
	TriPoly->SetSize(TriPoly->m_n);		// Now resize to the actual size needed.  
	return TRUE;
}

BOOL CPolygon::LoadXY(LPCTSTR Filename, REAL Zdefault /* = D2Real(0.0) */)
// Loads the polygon in the file "Filename"
{
	float x,y;
	FILE *fp;
	int nNum;
	char buffer[100];

	// empty polygon
	RemoveAll();

	// open file for reading
	if (!FileOpen(&fp,Filename,"r"))
		return FALSE;

	// Get no. of vertices
	if (fscanf(fp,"%d", &nNum) != 1) {
		fclose(fp);
		return FALSE;
	}
	// read off rest of line
	fgets(buffer, 100, fp); 

	// Get some memory for polygon
	if (!SetSize(nNum)) {
		fclose(fp);
		return FALSE;
	}

	// read in polygon points (should do some error checking here...)
	for (int i=0; i<nNum; i++) {
		fscanf(fp,"%f %f", &x, &y);
		m_point[i] = C3Point(F2Real(x), F2Real(y), Zdefault);
	}
    fclose(fp);
	
	return TRUE;
}

BOOL CPolygon::LoadXY(FILE* fp, REAL Zdefault /* = D2Real(0.0) */)
// Loads the polygon in the already open file, leaving it open
{
	float x,y;
	int nNum;
	char buffer[100];

	RemoveAll();

	if (fscanf(fp,"%d", &nNum) != 1) return FALSE;	// get No. points in polygon
	fgets(buffer, 100, fp);							// read off rest of line
	if (!SetSize(nNum))		     return FALSE;		// get memory for polygon

	// read in polygon
	for (int i=0; i<nNum; i++) {
		fscanf(fp,"%f %f", &x, &y);
		m_point[i] = C3Point(F2Real(x), F2Real(y), Zdefault);
	}

	return TRUE;
}


BOOL CPolygon::LoadXYZ(LPCTSTR Filename, BOOL bWarn /*=TRUE*/)
// Loads the polygon in the file "Filename". If bWarn = TRUE it will post an 
// error message if the file couldn't be loaded.
{
	float x,y,z;
	FILE *fp;

	if (!FileOpen(&fp,Filename,"r", bWarn)) {
		RemoveAll();
		return FALSE;
	}

	while (fscanf(fp,"%f %f %f", &x, &y, &z) == 3)
		Add(C3Point(x,y,z));
	fclose(fp);

	return TRUE;
}

BOOL CPolygon::LoadXYZ(FILE* fp)
// Loads the polygon in the already open file, leaving it open
{
	double x,y,z;
	int nNum;
	char buffer[100];

	RemoveAll();

	if (fscanf(fp,"%d", &nNum) != 1) return FALSE;	// get No. points in polygon
	fgets(buffer, 100, fp);							// read off rest of line
	if (!SetSize(nNum))		     return FALSE;		// get memory for polygon

	// read in polygon
	for (int i=0; i<nNum; i++) {
		fscanf(fp,"%lf %lf %lf", &x, &y, &z);
		m_point[i] = C3Point(D2Real(x), D2Real(y), D2Real(z));
	}

	return TRUE;
}

BOOL CPolygon::Save(LPCTSTR Filename, BOOL bAsPoints /*= FALSE */ , BOOL bWarn /*= TRUE*/)
{
	FILE *fp;

	if (!FileOpen(&fp,Filename,"w", bWarn))
		return FALSE;

	if (bAsPoints) {
		for (int i = 0; i < GetSize(); i++)
			fprintf(fp, "%10.2f %10.2f %10.2f", m_point[i].x, m_point[i].y, m_point[i].z);
	} else {
		fprintf(fp, "%6d %10.2f\n",GetSize(), m_point[0].z);
		for (int i = 0; i < GetSize(); i++) {
			fprintf(fp,"%10.2f %10.2f", m_point[i].x, m_point[i].y);
			if ((i+1)%4 == 0) fprintf(fp,"\n");
		}
		if ((GetSize()+1)%4) fprintf(fp,"\n");
	}

	fclose(fp);
	return TRUE;
}


// Natural and Clamped Cubic Splines
//
// Input:  A CPolygon of N points (x_i,y_i), 0 <= i <= N-1, which are sampled
// from a function, y_i = f(x_i).  The function f is unknown.  For natural
// cubic splines, it is assumed f"(x_0) = f"(x_N-1) = 0.  For clamped cubic
// splines, the derivatives f'(x_0) and f'(x_N-1) are user-specified.
//
// Output: b_i, c_i, d_i, 0 <= i <= N-2, which are coefficients for the cubic
// spline S_i(x) = a_i + b_i(x-x_i) + c_i(x-x_i)^2 + d_i(x-x_i)^3 for
// x_i <= x < x_{i+1}.
//
// Algorithm implemented from
//    Numerical Analysis, 3rd edition
//    Richard L. Burden and J. Douglas Faires
//    Prindle, Weber & Schmidt
//    Boston, 1985, pp. 122-124.
//-----------------------------------------------------------------------------

void CPolygon::NaturalSpline(double*& b, double*& c, double*& d)
{
	const double oneThird = 1.0/3.0;

	int i;
	double* h = new double[GetSize()-1];
	double* hdiff = new double[GetSize()-1];
	double* alpha = new double[GetSize()-1];

	for (i = 0; i < GetSize()-1; i++)
		h[i] = m_point[i+1].x-m_point[i].x;

	for (i = 1; i < GetSize()-1; i++)
		hdiff[i] = m_point[i+1].x-m_point[i-1].x;

	for (i = 1; i < GetSize()-1; i++)
	{
		double numer = 3.0*(m_point[i+1].y*h[i-1]-m_point[i].y*hdiff[i]+m_point[i-1].y*h[i]);
		double denom = h[i-1]*h[i];
		alpha[i] = numer/denom;
	}

	double* ell = new double[GetSize()];
	double* mu = new double[GetSize()-1];
	double* z = new double[GetSize()];
	double recip;

	ell[0] = 1.0;
	mu[0] = 0.0;
	z[0] = 0.0;

	for (i = 1; i < GetSize()-1; i++)
	{
		ell[i] = 2.0*hdiff[i]-h[i-1]*mu[i-1];
		recip = 1.0/ell[i];
		mu[i] = recip*h[i];
		z[i] = recip*(alpha[i]-h[i-1]*z[i-1]);
	}
	ell[GetSize()-1] = 1.0;
	z[GetSize()-1] = 0.0;

	b = new double[GetSize()-1];
	c = new double[GetSize()];
	d = new double[GetSize()-1];

	c[GetSize()-1] = 0.0;

	for (i = GetSize()-2; i >= 0; i--)
	{
		c[i] = z[i]-mu[i]*c[i+1];
		recip = 1.0/h[i];
		b[i] = recip*(m_point[i+1].y-m_point[i].y)-h[i]*(c[i+1]+2.0*c[i])*oneThird;
		d[i] = oneThird*recip*(c[i+1]-c[i]);
	}

	delete[] h;
	delete[] hdiff;
	delete[] alpha;
	delete[] ell;
	delete[] mu;
	delete[] z;
}

REAL CPolygon::Curvature(int nIndex, int nSampleSize)
{
	ASSERT(nIndex >= 0 && nIndex < GetSize());

	// Get a range of point on the polygon to sample
	int nMinPt = (nSampleSize > nIndex)? 0 : nIndex-nSampleSize;
	int nMaxPt = (nIndex+nSampleSize >= GetSize())? GetSize()-1 : nIndex+nSampleSize;

	// Store these points in a temporary polygon
	CPolygon XVals(nMaxPt-nMinPt+1), 
		     YVals(nMaxPt-nMinPt+1);

	REAL IndexDistance = 0.0, distance = 0.0;
	for (int i = nMinPt; i <= nMaxPt; i++) {
		if (i > nMinPt)
			distance += D2Real(sqrt( (m_point[i].x-m_point[i-1].x)*(m_point[i].x-m_point[i-1].x)
								  +  (m_point[i].y-m_point[i-1].y)*(m_point[i].y-m_point[i-1].y)));

		XVals[i].x = YVals[i].x = distance;
		XVals[i].y = m_point[i].x;
		YVals[i].y = m_point[i].y;
		if (i == nIndex) 
			IndexDistance = distance;
	}

	// fit a spline to the points in the temp polygon.
	double *b1,*c1,*d1, *b2, *c2, *d2;
	XVals.NaturalSpline(b1,c1,d1);
	YVals.NaturalSpline(b2,c2,d2);

	// The point in question is nIndex-nMinPt. The spline curve for
	// this point is 
	int nPoint = nIndex-nMinPt;

	double numerator = b1[nPoint] * 2.0*c2[nPoint] - b2[nPoint] * 2.0*c1[nPoint];
	double denomenator = pow(b1[nPoint]*b1[nPoint] + b2[nPoint]*b2[nPoint], 1.5);
      
	delete [] b1; delete [] c1; delete [] d1;
	delete [] b2; delete [] c2; delete [] d2;

	if (denomenator > 0)    
		return D2Real(numerator/denomenator);    
	else    
		return D2Real(0.0);  // could be nonzero in the limit    
}

REAL CPolygon::Curvature(int i)
// Calculates the curvature for the segment i, defined by points i and i+1
{
	VECTOR dRdsA, dRdsB, CurvVector;
	REAL Length, LengthFracA, LengthFracB;

	if (!i || i==GetSize()-1) return 0.0;

	ASSERT(i > 0 && i < GetSize()-1);

	// if R(t) is a parametric curve with arc length s, then the tangent vector
	// to the curve R(t) is T(t) = R'(t) / |R(t)|, which can be rewritten as
	// T(s) = dR/ds

	// Calculate unit tangent vector to curve using points i and i-1
	Length = D2Real(sqrt( (m_point[i].x-m_point[i-1].x)*(m_point[i].x-m_point[i-1].x) +
						  (m_point[i].y-m_point[i-1].y)*(m_point[i].y-m_point[i-1].y)));
	ASSERT(Length > D2Real(0.0));

	LengthFracA = D2Real(1.0) / Length;
	dRdsA.x = (m_point[i].x-m_point[i-1].x) * LengthFracA;
	dRdsA.y = (m_point[i].y-m_point[i-1].y) * LengthFracA;

	// Calculate unit tangent vector to curve using points i and i+1
	Length = D2Real(sqrt( (m_point[i+1].x-m_point[i].x)*(m_point[i+1].x-m_point[i].x) +
						  (m_point[i+1].y-m_point[i].y)*(m_point[i+1].y-m_point[i].y)));
	ASSERT(Length > D2Real(0.0));

	LengthFracB = D2Real(1.0) / Length;
	dRdsB.x = (m_point[i+1].x-m_point[i].x) * LengthFracB;
	dRdsB.y = (m_point[i+1].y-m_point[i].y) * LengthFracB;

	// The curvature is defined as k(s) = |dT/ds| ( = |T'|/|R'|, '=d/dt)
	// Warning: dodgy averaging used here :)

	CurvVector.x = (dRdsB.x - dRdsA.x) * LengthFracA;
	CurvVector.y = (dRdsB.y - dRdsA.y) * LengthFracA;

	REAL Curvature = D2Real(sqrt(CurvVector.x*CurvVector.x + CurvVector.y*CurvVector.y));

	if (!Left(m_point[i-1],m_point[i], m_point[i+1]))
		Curvature = -Curvature;

	return Curvature;
}

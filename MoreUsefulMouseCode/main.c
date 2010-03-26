/*----------------------------------------------------------------------------------------
 *	
 *	project:	04_MoreUsefulMouseCode
 *	author:		Rob Bateman
 *	note:		
 *				The previous code was all well and good, but it wasn't very useful.
 *				To make the mouse functionality a bit more useful, we need to start storing
 *				information about which mouse buttons are held, how much the mouse has moved etc.
 *
 *				The code below doesn't do much other than show some sensible places to
 *				calculate some sensible values! At the moment the values are essentually
 *				informatioon on which buttons are pressed, the location of the cursor
 *				and the two motion functions calculate the amount that the mouse has moved
 *				since last time (dx,dy).
 *
 *				
 */

/*----------------------------------------------------------------------------------------
 *	Includes
 */

#define SHRINKSIZE 10
#define ARROWSIZE 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include "gpc.h"

#define M_PI 3.141592653589793238462643


#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include <GL/glut.h>
#include <vmmlib/vmmlib.h>

using namespace std;
using namespace vmml;

void renderBitmapString(Vector3f pos, void* font, string text)
{
	char asd[100];
	char *a = &asd[0];
	sprintf_s(asd,text.c_str());
	glRasterPos3f(pos.x, pos.y, pos.z);
	for (UINT c=0;c<text.size();c++)
		glutBitmapCharacter(font, (int)*a++);
}

struct InFillHit{
	Vector2f p;		// The intersection point
	float d;		// Distance from the infill-line start point, used for sorting hits
};

#define SMALL_NUM  0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y)
#define perp(u,v)  ((u).x * (v).y - (u).y * (v).x)  // perp product (2D)

//===================================================================

// inSegment(): determine if a point is inside a segment
//    Input:  a point P, and a collinear segment S
//    Return: 1 = P is inside S
//            0 = P is not inside S
int inSegment( const Vector2f &P, const Vector2f &p1, const Vector2f &p2)
{
	if (p1.x != p2.x) {    // S is not vertical
		if (p1.x <= P.x && P.x <= p2.x)
			return 1;
		if (p1.x >= P.x && P.x >= p2.x)
			return 1;
	}
	else {    // S is vertical, so test y coordinate
		if (p1.y <= P.y && P.y <= p2.y)
			return 1;
		if (p1.y >= P.y && P.y >= p2.y)
			return 1;
	}
	return 0;
}
// intersect2D_2Segments(): the intersection of 2 finite 2D segments
//    Input:  two finite segments S1 and S2
//    Output: *I0 = intersect point (when it exists)
//            *I1 = endpoint of intersect segment [I0,I1] (when it exists)
//    Return: 0=disjoint (no intersect)
//            1=intersect in unique point I0
//            2=overlap in segment from I0 to I1
int intersect2D_Segments( const Vector2f &p1, const Vector2f &p2, const Vector2f &p3, const Vector2f &p4, Vector2f &I0, Vector2f &I1, float &t0, float &t1 )
{
	Vector2f    u = p2 - p1;
	Vector2f    v = p4 - p3;
	Vector2f    w = p1 - p3;
	float    D = perp(u,v);

	// test if they are parallel (includes either being a point)
	if (fabs(D) < SMALL_NUM) {          // S1 and S2 are parallel
		if (perp(u,w) != 0 || perp(v,w) != 0) {
			return 0;                   // they are NOT collinear
		}
		// they are collinear or degenerate
		// check if they are degenerate points
		float du = dot(u,u);
		float dv = dot(v,v);
		if (du==0 && dv==0) {           // both segments are points
			if (p1 != p3)         // they are distinct points
				return 0;
			I0 = p1;                // they are the same point
			return 1;
		}
		if (du==0) {                    // S1 is a single point
			if (inSegment(p1, p3, p4) == 0)  // but is not in S2
				return 0;
			I0 = p1;
			return 1;
		}
		if (dv==0) {                    // S2 a single point
			if (inSegment(p3, p1,p2) == 0)  // but is not in S1
				return 0;
			I0 = p3;
			return 1;
		}
		// they are collinear segments - get overlap (or not)
		//float t0, t1;                   // endpoints of S1 in eqn for S2
		Vector2f w2 = p2 - p3;
		if (v.x != 0) {
			t0 = w.x / v.x;
			t1 = w2.x / v.x;
		}
		else {
			t0 = w.y / v.y;
			t1 = w2.y / v.y;
		}
		if (t0 > t1) {                  // must have t0 smaller than t1
			float t=t0; t0=t1; t1=t;    // swap if not
		}
		if (t0 > 1 || t1 < 0) {
			return 0;     // NO overlap
		}
		t0 = t0<0? 0 : t0;              // clip to min 0
		t1 = t1>1? 1 : t1;              // clip to max 1
		if (t0 == t1) {                 // intersect is a point
			I0 = p3 + v*t0;
			return 1;
		}

		// they overlap in a valid subsegment
		I0 = p3 + v*t0;
		I1 = p3 + v*t1;
		return 2;
	}

	// the segments are skew and may intersect in a point
	// get the intersect parameter for S1
	float     sI = perp(v,w) / D;
	if (sI < 0 || sI > 1)               // no intersect with S1
		return 0;

	// get the intersect parameter for S2
	float     tI = perp(u,w) / D;
	if (tI < 0 || tI > 1)               // no intersect with S2
		return 0;

	I0 = p1 + u * sI;               // compute S1 intersect point
	return 1;
}


// calculates intersection and checks for parallel lines.  
// also checks that the intersection point is actually on  
// the line segment p1-p2

bool IntersectXY(const Vector2f &p1, const Vector2f &p2, const Vector2f &p3, const Vector2f &p4, InFillHit &hit)
{

	if(abs(p1.x-p3.x) < 0.01 && abs(p1.y - p3.y) < 0.01)	// if vertices are the same
	{
		hit.p = p1;
		hit.d = sqrtf( (p1.x-hit.p.x) * (p1.x-hit.p.x) + (p1.y-hit.p.y) * (p1.y-hit.p.y));
		return true;
	}
	if(abs(p2.x-p3.x) < 0.01 && abs(p2.y - p3.y) < 0.01)	// if vertices are the same
	{
		hit.p = p2;
		hit.d = sqrtf( (p1.x-hit.p.x) * (p1.x-hit.p.x) + (p1.y-hit.p.y) * (p1.y-hit.p.y));
		return true;
	}
	if(abs(p1.x-p4.x) < 0.01 && abs(p1.y - p4.y) < 0.01)	// if vertices are the same
	{
		hit.p = p1;
		hit.d = sqrtf( (p1.x-hit.p.x) * (p1.x-hit.p.x) + (p1.y-hit.p.y) * (p1.y-hit.p.y));
		return true;
	}
	if(abs(p2.x-p4.x) < 0.01 && abs(p2.y - p4.y) < 0.01)	// if vertices are the same
	{
		hit.p = p2;
		hit.d = sqrtf( (p1.x-hit.p.x) * (p1.x-hit.p.x) + (p1.y-hit.p.y) * (p1.y-hit.p.y));
		return true;
	}

	InFillHit hit2;
	float t0,t1;
	if(intersect2D_Segments(p1,p2,p3,p4,hit.p, hit2.p, t0,t1) == 1)
	{
		hit.d = sqrtf( (p1.x-hit.p.x) * (p1.x-hit.p.x) + (p1.y-hit.p.y) * (p1.y-hit.p.y));
		return true;
	}
	return false;
}

class point : public Vector2f{
public:
	point(bool isValid=true){valid=isValid;parent=-1;}
	point(float x, float y, bool isValid=true) : Vector2f(x,y){valid=isValid;parent=-1;}
	point(Vector2f p, bool isValid=true) : Vector2f(p) {valid=isValid;parent=-1;}
	bool valid;
	bool disabled;
	int parent;
};

class Line
{
public:
	Line(){s=e=-1;valid=true;}
	Line(int start, int end, bool isValid, UINT parentLine){s=start;e=end;valid=isValid; parent=parentLine;}
	int s,e;
	bool valid;
	UINT parent;
};

class Poly{
public:
	Poly(){};
	void Shrink(float dist);
	void ShrinkGPC(float dist);
	void Add(Vector2f p){vert.push_back(p);}
	float angleAtVertex(int i);
	Vector2f &v(int i, bool shrinked=false);
	Vector2f e(int i, bool shrinked=false);
	Vector2f biplane(int i);
	Vector2f midpoint(int i, bool shrinked=false);
	bool isconvex(int i, bool shrinked=false);
	void draw(Vector2f offset);
	bool handleShrinkErrors(float dist);

	vector<point> vert;			// points, indices into ..... a CuttingPlane or a GCode object

	vector<Vector2f> offset_points;		// Size is the same as the vert vector
	vector<Line> raw_offset_lines;		//indices into the offset_points vector. Every 2 points makes a line
};


void Poly::draw(Vector2f offset)
{

	// validate indices
	for(UINT i=0;i<raw_offset_lines.size();i++)
	{
	if(raw_offset_lines[i].s < 0)
		raw_offset_lines[i].s += raw_offset_lines.size()-1;
	if(raw_offset_lines[i].e < 0)
		raw_offset_lines[i].e += raw_offset_lines.size()-1;
	}

/*	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	for(UINT i=0;i<vert.size();i++)
		glVertex2fv(&vert[i].x);
	glEnd();
*/

	glPointSize(4);
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	for(UINT i=0;i<offset_points.size();i++)
	{
		glVertex2fv(&offset_points[i].x);
	}
	glEnd();


	glBegin(GL_LINES);
	glColor3f(1,1,1);
	for(UINT i=0;i<vert.size();i++)
	{
		glVertex2f(v(i).x+offset.x, v(i).y+offset.y);
		glVertex2f(v(i-1).x+offset.x, v(i-1).y+offset.y);
	}
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINES);
	for(UINT i=0;i<raw_offset_lines.size();i++)
	{
		if(raw_offset_lines[i].valid)
			glColor3f(0,1,0);
		else
			glColor3f(1,0,0);
		glVertex2f(offset_points[raw_offset_lines[i].s].x+offset.x, offset_points[raw_offset_lines[i].s].y);
		glVertex2f(offset_points[raw_offset_lines[i].e].x+offset.x, offset_points[raw_offset_lines[i].e].y);
	}
	glEnd();
	// Draw parent IDs
	if(0)
	for(UINT i=0;i<raw_offset_lines.size();i++)
	{
		stringstream oss;
		oss << raw_offset_lines[i].parent;

		Vector2f a(offset_points[raw_offset_lines[i].s]);
		Vector2f b(offset_points[raw_offset_lines[i].e]);
		Vector2f p=a+((b-a)*0.5f);
		renderBitmapString(Vector3f(p.x+offset.x+5, p.y+offset.y+5, 0), GLUT_BITMAP_8_BY_13, oss.str());
	}
	// draw line numbers
	for(UINT i=0;i<raw_offset_lines.size();i++)
	{
		stringstream oss;
		oss << i ;

		Vector2f a(offset_points[raw_offset_lines[i].s]);
		Vector2f b(offset_points[raw_offset_lines[i].e]);
		Vector2f p=a+((b-a)*0.5f);
		renderBitmapString(Vector3f(p.x+offset.x+5, p.y+offset.y+5, 0), GLUT_BITMAP_8_BY_13, oss.str());
	}
	// draw vertex numbers
	for(UINT i=0;i<offset_points.size();i++)
	{
		stringstream oss;
		oss << i ;
		renderBitmapString(Vector3f(offset_points[i].x+offset.x+5, offset_points[i].y+offset.y+5, 0), GLUT_BITMAP_8_BY_13, oss.str());
	}
	
	// Draw biplane vectors
	glColor3f(0,1,0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple (1, 0x0f0f); /* dashed */
	glBegin(GL_LINES);
	if(offset_points.size() == vert.size())
		for(UINT i=0;i<vert.size();i++)
		{
			glVertex2f(v(i).x+offset.x, v(i).y+offset.y);
			glVertex2f(v(i,true).x+offset.x, v(i,true).y+offset.y);
		}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	
	// Direction arrows
	glLineWidth(1);
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	if(offset_points.size() == vert.size())
		for(UINT i=0;i<vert.size();i++)
		{
			Vector2f center = midpoint(i,true);
			Vector2f normal = e(i,true);
			normal.normalize();
			Vector2f centerOffset = center-normal*ARROWSIZE+offset;
			float tmp=normal.x;
			normal.x = normal.y;
			normal.y = -tmp;
			normal*=ARROWSIZE;
			glVertex2fv(&centerOffset.x);
			Vector2f p=center+normal+offset;
			glVertex2fv(&p.x);
			glVertex2fv(&centerOffset.x);
			p=center-normal+offset;
			glVertex2fv(&p.x);
		}
	glEnd();
	// Direction arrows, boundry lines
	glLineWidth(1);
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	if(offset_points.size() == vert.size())
		for(UINT i=0;i<vert.size();i++)
		{
			Vector2f center = midpoint(i);
			Vector2f normal = e(i);
			normal.normalize();
			Vector2f centerOffset = center-normal*ARROWSIZE+offset;
			float tmp=normal.x;
			normal.x = normal.y;
			normal.y = -tmp;
			normal*=ARROWSIZE;
			glVertex2fv(&centerOffset.x);
			Vector2f p=center+normal+offset;
			glVertex2fv(&p.x);
			glVertex2fv(&centerOffset.x);
			p=center-normal+offset;
			glVertex2fv(&p.x);
		}
	glEnd();}

float Poly::angleAtVertex(int i)
{
	Vector2f Na = v(i-1);
	Vector2f Nb = v(i);
	Vector2f Nc = Nb;
	Vector2f center = Nb;
	Vector2f Nd = v(i+1);

	Vector2f V1 = (Nb-Na);
	Vector2f V2 = (Nd-Nc);

	float dotproduct, lengtha, lengthb, result;

	dotproduct = (V1.x * V2.x) + (V1.y * V2.y);
	lengtha = sqrt(V1.x * V1.x + V1.y * V1.y);
	lengthb = sqrt(V2.x * V2.x + V2.y * V2.y);

	result = acos( dotproduct / (lengtha * lengthb) );

	if(result > 0)
		result += M_PI;
	else
		result -= M_PI;
/*	ostringstream oss;
	oss << result;
	renderBitmapString(Vector3f(Nb.x, Nb.y, 0), GLUT_BITMAP_8_BY_13, oss.str());*/
	return result;
}

Vector2f Poly::midpoint(int i, bool shrinked)
{
	Vector2f p(v(i,shrinked));
	Vector2f p2(v(i+1,shrinked));
	Vector2f delta = p2-p;
	p+= delta*0.5f;
	return p;
}

Vector2f &Poly::v(int i, bool shrinked)
{
	if(shrinked)
	{
	i+= (int)offset_points.size();
	return offset_points[i%offset_points.size()];
	}
	i+= (int)vert.size();
	return vert[i%vert.size()];
}
Vector2f Poly::e(int i, bool shrinked)
{
	return (v(i,shrinked)-v(i+1,shrinked));
}

Vector2f Poly::biplane(int i)
{
	return ( e(i).getNormalized() - e(i-1).getNormalized()).getNormalized();
}

bool Poly::isconvex(int i, bool shrinked)
{
	Vector2f v1=e(i, shrinked);
	Vector2f v2=e(i-1, shrinked);

	return v2.cross(v1) < 0;
}
#include "gpc.h"
#include "gpc.c"

/*#include "../Libraries/PolyBoolean/polybool.h"
using namespace POLYBOOLEAN;
*/
void Poly::ShrinkGPC(float dist)
{
	// PGC version

	// prep circle for ends

	int stepCount = 20;
	gpc_vertex * circle_points= new  gpc_vertex[stepCount];

	gpc_vertex_list *circle = new gpc_vertex_list;
	circle->num_vertices = stepCount;
	float angle=0;
	for(int i=0;i<stepCount;i++)
	{
		circle_points[i].x = cos(angle)*dist;
		circle_points[i].y = sin(angle)*dist;
		angle += (M_PI*2)/stepCount;
	}



	gpc_polygon all_solids;
	gpc_polygon solids;
	solids.num_contours = 0;

	if(vert.size() < 2)
		return;

	for(UINT i=0; i<vert.size();i++)
	{
		Vector2f s = v(i);
		Vector2f e = v(i+1);

		Vector2f d = e-s;
		Vector2f Normal(d.y, -d.x);

		Normal = Normal.getNormalized()*dist;

		Vector2f P1 = s+Normal;
		Vector2f P2 = e+Normal;
		Vector2f P3 = e-Normal;
		Vector2f P4 = s-Normal;

		gpc_vertex_list *vertices = new gpc_vertex_list;
		vertices->vertex = new  gpc_vertex[4];
		vertices->num_vertices = 4;

		vertices->vertex[0].x = P1.x;
		vertices->vertex[0].y = P1.y;
		vertices->vertex[1].x = P2.x;
		vertices->vertex[1].y = P2.y;
		vertices->vertex[2].x = P3.x;
		vertices->vertex[2].y = P3.y;
		vertices->vertex[3].x = P4.x;
		vertices->vertex[3].y = P4.y;

		if(solids.num_contours == 0)
		{
			solids.num_contours = 1;
			solids.hole = new int;
			*solids.hole = 0;
			solids.contour = vertices;
		}
		else
		{
			gpc_polygon new_solid;
			new_solid.num_contours = 1;
			new_solid.hole = new int;
			*new_solid.hole = 0;
			new_solid.contour = vertices;
			gpc_polygon_clip(GPC_UNION, &solids, &new_solid, &all_solids);
			solids=all_solids;
			delete new_solid.hole;
			delete new_solid.contour;
		}
		
/*		// add circles
		{
		gpc_vertex* c = new gpc_vertex[20];
		for(int j=0;j<stepCount;j++)
				{
				c[j].x = (int)((circle_points[j].x+s.x)*100);
				c[j].y = (int)((circle_points[j].y+s.y)*100);
				}
		circle->vertex = c;
		gpc_polygon new_solid;
		new_solid.num_contours = 1;
		new_solid.hole = new int;
		*new_solid.hole = 0;
		new_solid.contour = circle;
		circle->vertex = c;
		gpc_polygon_clip(GPC_UNION, &solids, &new_solid, &all_solids);
		solids=all_solids;
		delete new_solid.hole;
		delete new_solid.contour;
		}	// add circle
/*
		glBegin(GL_LINE_LOOP);
		glVertex3f(P1.x, P1.y, 0);
		glVertex3f(P2.x, P2.y, 0);
		glVertex3f(P3.x, P3.y, 0);
		glVertex3f(P4.x, P4.y, 0);
		glEnd();
*/
	}

	// draw solids


	// delete the outer contour

	for(int o=0;o<all_solids.num_contours;o++)
	{
		switch(o%6)
		{
		case 0:	glColor4f(1,0,0,1); break;
		case 1:	glColor4f(0.5f,0,0,1); break;
		case 2:	glColor4f(0,1,0,1); break;
		case 3:	glColor4f(0,0.5f,0,1); break;
		case 4:	glColor4f(0,1,1,1); break;
		case 5:	glColor4f(1,0,0.5f,1); break;
		default: glColor4f(0.2f,0.6f,0.2f,1); break;
		}
		glBegin(GL_LINE_LOOP);
		for(int i=0;i<all_solids.contour[o].num_vertices;i++)
		{
			glVertex3f(all_solids.contour[o].vertex[i].x, all_solids.contour[o].vertex[i].y, 0);
		}
		glEnd();
	}


/*    static const GRID2 a1[4] = { {-70, 80}, {-70, -30}, {20, -30}, {20, 80} };
	static const GRID2 a2[4] = { {-50, 60}, {00, 60}, {00, 00}, {-50, 00} };
    static const GRID2 b[11] = { {-50, -60}, {70,-60}, {70, 40}, {-50, 40}, {0, 0}, {0, 20}, {50, 20}, {50, -40}, {00, -40}, {00, 00}, {-50, 00} };

	PAREA * A = NULL;
	  {
	  PLINE2 * pline = NULL;

	  for (int i = 0; i < 4; i++)
		  PLINE2::Incl(&pline, a1[i]);
	  pline->Prepare();
	  { // make sure the contour is outer
	  if (not pline->IsOuter())
		  pline->Invert();
	  }
	  PAREA::InclPline(&A, pline);

	  pline = NULL;
	  for (int i = 0; i < 4; i++)
		  PLINE2::Incl(&pline, a2[i]);
	  pline->Prepare();
		  { // make sure the contour is a hole
		  if (pline->IsOuter())
			  pline->Invert();
		  }
		  PAREA::InclPline(&A, pline);
	}// init A
    PAREA * B = NULL;
	// construct 2nd polygon
	{
        PLINE2 * pline = NULL;

        for (int i = 0; i < 11; i++)
            PLINE2::Incl(&pline, b[i]);
        pline->Prepare();
        { // make sure the contour is outer
		if (not pline->IsOuter())
                pline->Invert();
        }
        PAREA::InclPline(&B, pline);
    }

	PAREA * R = NULL;
	int err = PAREA::Boolean(A, B, &R, PAREA::UN);
*/
/*
	// PolyBoolean version
	PAREA * A = NULL;
	PAREA * R = NULL;
	for(UINT i=0; i<vert.size();i++)
	{
		Vector2f s = v(i);
		Vector2f e = v(i+1);

		Vector2f d = e-s;
		Vector2f Normal(d.y, -d.x);

		Normal = Normal.getNormalized()*dist;

		Vector2f P1 = s+Normal;
		Vector2f P2 = e+Normal;
		Vector2f P3 = e-Normal;
		Vector2f P4 = s-Normal;

		PLINE2 * pline = NULL;
		GRID2 p;
		p.x = (int)(P1.x*100); p.y = (int)(P1.y*100);
		PLINE2::Incl(&pline, p);
		p.x = (int)(P2.x*100); p.y = (int)(P2.y*100);
		PLINE2::Incl(&pline, p);
		p.x = (int)(P3.x*100); p.y = (int)(P3.y*100);
		PLINE2::Incl(&pline, p);
		p.x = (int)(P4.x*100); p.y = (int)(P4.y*100);
		PLINE2::Incl(&pline, p);

	  pline->Prepare();
	  { // make sure the contour is outer
	  if (not pline->IsOuter())
		  pline->Invert();
	  }
//	  PAREA::InclPline(&A, pline);
	  if( (i==0 || R != 0) )
			{
			int err = PAREA::Boolean(A, R, &R, PAREA::UN);
			if(err != 0)
				{
				int a=0;
				}
			}
	}

	PAREA * B = NULL;

	//R->cntr is a pointer to a PLINE2;
	if(R != 0)
	{
	glBegin(GL_LINE_LOOP);
	VNODE2 *v = R->cntr->head;
	int count = R->cntr->Count;
	while(count--)
		{
		glVertex2f((float)(v->g.x/100+640), (float)(v->g.y/100));
		v=v->next;
		}
	glEnd();
	}
*/



	/*	gpc_polygon solids;
	solids.num_contours = 0;
	gpc_polygon holes;
	holes.num_contours = 0;

	gpc_polygon all_holes;
	gpc_polygon all_solids;


	// Copy vertices
	for(uint p=0; p<vert.size();p++)
	{
		gpc_vertex_list *vertices = new gpc_vertex_list;
		vertices->vertex = new  gpc_vertex[offsetPolygons[p].points.size()];
		for(int v=0;v<offsetPolygons[p].points.size();v++)
		{
			vertices->vertex[v].x = offsetVertices[offsetPolygons[p].points[v]].x;
			vertices->vertex[v].y = offsetVertices[offsetPolygons[p].points[v]].y;
		}
		vertices->num_vertices = offsetPolygons[p].points.size();

		if(offsetPolygons[p].hole == true)
		{
			if(holes.num_contours == 0)
			{
				holes.num_contours = 1;
				holes.hole = new int;
				*holes.hole = 0;
				holes.contour = vertices;
			}
			else
			{
				gpc_polygon new_hole;
				new_hole.num_contours = 1;
				new_hole.hole = new int;
				*new_hole.hole = 0;
				new_hole.contour = vertices;
				gpc_polygon_clip(GPC_UNION, &holes, &new_hole, &all_holes);
				holes=all_holes;
				delete new_hole.hole;
				delete new_hole.contour;
			}
			//				gpc_add_contour(&holes, vertices, 0);
		}
		else			// it's a solid
		{
			if(solids.num_contours == 0)
			{
				solids.num_contours = 1;
				solids.hole = new int;
				*solids.hole = 0;
				solids.contour = vertices;
			}
			else
			{
				gpc_polygon new_solid;
				new_solid.num_contours = 1;
				new_solid.hole = new int;
				*new_solid.hole = 0;
				new_solid.contour = vertices;
				gpc_polygon_clip(GPC_UNION, &solids, &new_solid, &all_solids);
				solids=all_solids;
				delete new_solid.hole;
				delete new_solid.contour;
			}
		}
	}


	// boolean the holes together

	//	gpc_polygon_clip(GPC_UNION, &holes, &holes, &all_holes);

	gpc_polygon poly_res;
	gpc_polygon_clip(GPC_DIFF, &solids, &holes, &poly_res);
*/
}

void Poly::Shrink(float dist)
{
	offset_points.clear();
	raw_offset_lines.clear();

	if(vert.size() < 2)
		return;

	for(UINT i=0;i<vert.size();i++)
	{
		Vector2f bp;
		if(isconvex(i))
		{
			glColor3f(1,0,0);
			bp = v(i)+biplane(i)*dist/cos((M_PI-angleAtVertex(i))*0.5f);
		}
		else
		{
			glColor3f(0,1,0);
			bp = v(i)-biplane(i)*dist/sin((angleAtVertex(i))*0.5f);
		}
		offset_points.push_back(bp);
		if(i>0)	// Don't add point -1->1 - we will add that in the end
			{
			Vector2f bounderyDirection = e(i-1).getNormalized();
			Vector2f offsetDirection = (offset_points[(i-1+offset_points.size())%offset_points.size()] - offset_points[i]).getNormalized();
			raw_offset_lines.push_back(Line(i-1,i, (bounderyDirection-offsetDirection).length() < 0.000001, i-1));
			}
	}
	// close the ring
	Vector2f bounderyDirection = e(vert.size()-1).getNormalized();
	Vector2f offsetDirection = (offset_points[offset_points.size()-1] - offset_points[0]).getNormalized();
	raw_offset_lines.push_back(Line(offset_points.size()-1,0, (bounderyDirection-offsetDirection).length() < 0.000001, offset_points.size()-1));

	// offset_points and raw_offset_lines vectors ready

	for(UINT i=0;i<vert.size();i++)
	{
		vert[i].valid = true;
	}

	// validate indices
	for(UINT i=0;i<raw_offset_lines.size();i++)
	{
	if(raw_offset_lines[i].s < 0)
		raw_offset_lines[i].s += raw_offset_lines.size()-1;
	if(raw_offset_lines[i].e < 0)
		raw_offset_lines[i].e += raw_offset_lines.size()-1;
	}

}



//	Invalid offset edge handling algorithm:
//	input: offset lines[]//
//	output: raw offset lines without local invalid loops//

bool Poly::handleShrinkErrors(float dist)
	{
	if(raw_offset_lines.size() < 5)
		return false;
	for(int i=0; i<raw_offset_lines.size(); ++i)
		{
		if( !raw_offset_lines[i].valid )	// This is a invalid edge, decide what to do
			{
			UINT first_invalid_line = i;
			int invalidCount = 1;
			while( i<raw_offset_lines.size() && !raw_offset_lines[i].valid)
				{
				invalidCount++;
				i++;
				}
			UINT last_invalid_line = i-1;

			int backward = (first_invalid_line-1)%raw_offset_lines.size();
			int forward = (last_invalid_line+1)%raw_offset_lines.size();

			bool fixed=false;

			// mark lines valid, so they are not processed again
			for(UINT i=first_invalid_line;i<=last_invalid_line;i++)
				raw_offset_lines[i].valid = true;


			/***********************************************************************/
			/******************************* CASE I ********************************/
			/***********************************************************************/

			if(invalidCount == 2)	// case I, there's just one invalid offset edge
				{
				// handle: remove point, adjust next point to be the intersection of backward and forward edges
				// Intersect backward and forward edge
				Vector2f P1(offset_points[raw_offset_lines[backward].s]);
				Vector2f P2(offset_points[raw_offset_lines[backward].e]);
				Vector2f P3(offset_points[raw_offset_lines[forward].s]);
				Vector2f P4(offset_points[raw_offset_lines[forward].e]);

				// extend lines
				P2 = (P2-P1).getNormalized()*6000+P1;	// End end of backwards line
				P3 = (P3-P4).getNormalized()*6000+P4;	// Start end of forwards line

				InFillHit hit;
				bool hitSomething = IntersectXY(P1,P2,P3,P4,hit);
				if(hitSomething)
					{
					offset_points[raw_offset_lines[backward].e] = hit.p;
					offset_points[raw_offset_lines[forward].s] = hit.p;
					// delete invalid line
					raw_offset_lines.erase(raw_offset_lines.begin()+first_invalid_line);
					// we would go i-- here, bu there's no need because we already know the next line is not invalid, so no need to check it
					}
				fixed=true;
				}

			/************************************************************************/
			/******************************* CASE II ********************************/
			/************************************************************************/

			else if(invalidCount > 2)	// case II, there's multiple consecutive invalid offset edge
				{
				forward = forward % raw_offset_lines.size();
				backward = (backward+raw_offset_lines.size()) % raw_offset_lines.size();

				Vector2f P1(offset_points[raw_offset_lines[backward].s]);
				Vector2f P2(offset_points[raw_offset_lines[backward].e]);
				Vector2f P3(offset_points[raw_offset_lines[forward].s]);
				Vector2f P4(offset_points[raw_offset_lines[forward].e]);

				// extend lines
				//	P2 = (P2-P1).getNormalized()*6000+P1;	// End end of backwards line
				//	P3 = (P3-P4).getNormalized()*6000+P4;	// Start end of forwards line
				//	P1 = (P1-P2).getNormalized()*6000+P2;	// Start end of backwards line
				//	P4 = (P4-P3).getNormalized()*6000+P3;	// End end of forwards line

				glColor3f(1,1,0);
				glPointSize(10);
				glBegin(GL_POINTS);
				vector<int> hits;
				// Check if the forward or backward edge hits the Boundery edge
				for(UINT i=first_invalid_line;i<=last_invalid_line;i++)
					{
					Vector2f E1 = offset_points[raw_offset_lines[i].s];
					Vector2f E2 = offset_points[raw_offset_lines[i].e];
					// backward edge test
					InFillHit hit;
					bool hitSomething = IntersectXY(P1,P2,E1,E2,hit);
					if(hitSomething)
						{
						hits.push_back(raw_offset_lines[i].parent);
						glVertex2fv(&hit.p.x);
						}
					// forward edge test
					hitSomething = IntersectXY(P3,P4,E1,E2,hit);
					if(hitSomething)
						{
						hits.push_back(raw_offset_lines[i].parent);
						glVertex2fv(&hit.p.x);
						}
					}
				glEnd();
				glPointSize(1);

				// the Boundry lines in the "hits" list needs to be offset
				for(UINT i=0;i<hits.size();i++)
					{
					Vector2f D = (v(hits[i])-v(hits[i]+1)).getNormalized();
					Vector2f normal = Vector2f(D.y, -D.x);
					Vector2f E1 = v(hits[i])+normal*dist;	// classic offset of vertex 1
					Vector2f E2 = v(hits[i]+1)+normal*dist;	// classic offset of vertex 2

					glColor3f(1,1,0);
					glBegin(GL_LINES);
					glVertex2fv(&E1.x);
					glVertex2fv(&E2.x);
					glEnd();

					// Check backward line
					InFillHit hit;
					bool hitSomething = IntersectXY(P1,P2,E1,E2,hit);
					if(hitSomething && hit.d > 0.0001)
						{
						offset_points[raw_offset_lines[backward].e] = hit.p;	// adjust backward offset line end point
						offset_points[raw_offset_lines[hits[i]].s] = hit.p;		// adjust invalid offset line start point
						fixed=true;
						}
					hitSomething = IntersectXY(P3,P4,E1,E2,hit);
					if(hitSomething && hit.d > 0.0001)
						{
						offset_points[raw_offset_lines[forward].s] = hit.p;		// adjust forward offset line start point
						offset_points[raw_offset_lines[hits[i]].e] = hit.p;		// adjust invalid offset line end point
						fixed=true;
						}
					}// for all hits
				}

			// delete invalid lines
			if(fixed)
				{
				int double_vertex = -1;
				bool deleteLine = false;
				// delete zero-length lines
				for(int i=0;i<raw_offset_lines.size();i++)
					if(offset_points[raw_offset_lines[i].s] == offset_points[raw_offset_lines[i].e])
						{
						double_vertex = raw_offset_lines[i].e;
						raw_offset_lines.erase(raw_offset_lines.begin()+i);
						}
					for(int v=0;v<offset_points.size();v++)
						if(offset_points[v] == offset_points[(v+1)%offset_points.size()])
							double_vertex = (v+1)%offset_points.size();
					// delete double vertex and update lines
					if(double_vertex != -1)
						{
						for(int l=0;l<raw_offset_lines.size();l++)
							{
							if(raw_offset_lines[l].s >= double_vertex)
								raw_offset_lines[l].s--;
							if(raw_offset_lines[l].e >= double_vertex)
								raw_offset_lines[l].e--;
							}
						offset_points.erase(offset_points.begin()+double_vertex);
						//	handleShrinkErrors(dist);
						}
					return (double_vertex != -1);
				}

			/*
			if(an invalid offset edge is consecutive)
			Case II algorithm;
			else
			Case I algorithm;
			if(update by Case I or Case II algorithm == false)
			connect a backward edge and a forward edge
			corresponding to offset lines[i];*/
			}
		}
	return false;
	}
/*
void Poly::handleShrinkErrors(float dist)
{
	// Fix
	if(shrink.size() > 2)
		for(UINT i=0;i<shrink.size();i++)
		{
			int backward=-1, forward=-1;
			if(shrink[i].valid == false)
			{
				backward=i-1;
				UINT forward=i+1;
				while(forward < shrink.size() && shrink[forward].valid==false )
					forward++;
				bool fixed=false;
				if(forward-backward == 2)	// case I, there's just one invalid offset edge
				{
					// handle: remove point, adjust next point to be the intersection of backward and forward edges
					// Intersect backward and forward edge
					Vector2f P1(v(backward, true));
					Vector2f P2(v(backward+1, true));
					Vector2f P3(v(forward, true));
					Vector2f P4(v(forward+1, true));

					// extend lines
					P2 = (P2-P1).getNormalized()*6000+P1;	// End end of backwards line
					P3 = (P3-P4).getNormalized()*6000+P4;	// Start end of forwards line

//					glBegin(GL_LINES);
//					glColor3f(1,1,1);
//					glVertex2fv(&P1.x);
//					glVertex2fv(&P2.x);
//					glVertex2fv(&P3.x);
//					glVertex2fv(&P4.x);
//					glEnd();

					InFillHit hit;
					bool hitSomething = IntersectXY(P1,P2,P3,P4,hit);
					if(hitSomething)
					{
						shrink[forward%shrink.size()] = hit.p;
						shrink[(backward+1)%shrink.size()] = hit.p;
					}
					shrink.erase(shrink.begin()+i);	// delete invalid edge
					fixed=true;
				}
				else if(forward-backward > 2)		// Case II
				{
					Vector2f P1(v(backward, true));
					Vector2f P2(v(backward+1, true));
					Vector2f P3(v(forward, true));
					Vector2f P4(v(forward+1, true));

					// extend lines
					//P2 = (P2-P1).getNormalized()*6000+P1;	// End end of backwards line
					//P3 = (P3-P4).getNormalized()*6000+P4;	// Start end of forwards line

					glPointSize(10);
					glBegin(GL_POINTS);
					vector<int> hits;
					// Check if the forward or backward edge hits the Boundery edge
					for(UINT i=backward+1;i<forward;i++)
						{
						Vector2f E1 = v(i);
						Vector2f E2 = v(i+1);
						// backward edge test
						InFillHit hit;
						bool hitSomething = IntersectXY(P1,P2,E1,E2,hit);
						if(hitSomething)
							{
							hits.push_back(i);
							glVertex2fv(&hit.p.x);
							}
						// forward edge test
						hitSomething = IntersectXY(P3,P4,E1,E2,hit);
						if(hitSomething)
							{
							hits.push_back(i);
							glVertex2fv(&hit.p.x);
							}
						}
					glEnd();
					glPointSize(1);

					// Pair wise offset intersecting "original" lines and intersect with before and after lines.
					// extend lines
					//P2 = (P2-P1).getNormalized()*6000+P1;	// End end of backwards line
					//P3 = (P3-P4).getNormalized()*6000+P4;	// Start end of forwards line

					glColor3f(0,1,1);
					glBegin(GL_LINES);
					glVertex3fv(&P1.x);
					glVertex3fv(&P2.x);
					glVertex3fv(&P3.x);
					glVertex3fv(&P4.x);
					glEnd();

					for(UINT i=0;i<hits.size();i++)
						{
						Vector2f D = (v(hits[i])-v(hits[i]+1)).getNormalized();
						Vector2f normal = Vector2f(D.y, -D.x);
						Vector2f E1 = v(hits[i])+normal*dist;
						Vector2f E2 = v(hits[i]+1)+normal*dist;

						glColor3f(1,1,0);
						glBegin(GL_LINES);
						glVertex2fv(&E1.x);
						glVertex2fv(&E2.x);
						glEnd();

						// Check backward line
						InFillHit hit;
						bool hitSomething = IntersectXY(P1,P2,E1,E2,hit);
						if(hitSomething)
							{
							v(backward+1, true) = hit.p;
							fixed=true;
							}
						hitSomething = IntersectXY(P3,P4,E1,E2,hit);
						if(hitSomething)
							{
							v(backward+2, true) = hit.p;
							v(forward, true) = hit.p;
							fixed=true;
							}
						if(fixed)
							shrink.erase(shrink.begin()+forward-1);
						}// for all hits
				}	// end Case II
			i=forward;	// Skip connected invalid edges
			}
		}
}*/
/*----------------------------------------------------------------------------------------
 *	Global Variables
 */

/*
 *	A structure to represent the mouse information
 */
struct Mouse 
{
	int x;		/*	the x coordinate of the mouse cursor	*/
	int y;		/*	the y coordinate of the mouse cursor	*/
	int lmb;	/*	is the left button pressed?		*/
	int mmb;	/*	is the middle button pressed?	*/
	int rmb;	/*	is the right button pressed?	*/

	/*
	 *	These two variables are a bit odd. Basically I have added these to help replicate
	 *	the way that most user interface systems work. When a button press occurs, if no
	 *	other button is held down then the co-ordinates of where that click occured are stored.
	 *	If other buttons are pressed when another button is pressed it will not update these
	 *	values. 
	 *
	 *	This allows us to "Set the Focus" to a specific portion of the screen. For example,
	 *	in maya, clicking the Alt+LMB in a view allows you to move the mouse about and alter
	 *	just that view. Essentually that viewport takes control of the mouse, therefore it is
	 *	useful to know where the first click occured.... 
	 */
	int xpress; /*	stores the x-coord of when the first button press occurred	*/
	int ypress; /*	stores the y-coord of when the first button press occurred	*/
};

/*
 *	rename the structure from "struct Mouse" to just "Mouse"
 */
typedef struct Mouse Mouse;

/*
 *	Create a global mouse structure to hold the mouse information.
 */
Mouse TheMouse = {0,0,0,0,0};
UINT editNr = -1;

/*
 *	Variables to hold the current size of the window.
 */
int winw = 1280;
int winh = 480;

Poly poly;


/*----------------------------------------------------------------------------------------
 *	This is the main display callback function. It sets up the drawing for 
 *	The 3D scene first then calls the Draw3D() function. After that it switches to 
 *	an orthographic projection and calls Draw2D().
 */
void Draw(void)
{
	/*
	 *	Clear the background
	 */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/*
	*	Allow drawing in full region of the screen
	*/
	glViewport(0,0,winw,winh);

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winw, 0, winh);

	
	vector<point> backup = poly.vert;

	int x=1;
	while(x--)
	{
	poly.ShrinkGPC(SHRINKSIZE);
	glLineWidth(1);
//	poly.draw(Vector2f(0,0));
	glLineWidth(SHRINKSIZE*2-5);
	int count=0;
	while(poly.handleShrinkErrors(SHRINKSIZE))
		{
/*		if( count == 1)
			{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			poly.draw(Vector2f(0,400));
			}*/
		count++;
		}
	poly.draw(Vector2f(0,0));
	}

	poly.vert = backup;

	glPopMatrix();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	/*
	 *	Bring the back buffer to the front and vice-versa.
	 */
	glutSwapBuffers();
}

/*----------------------------------------------------------------------------------------
 *	This function is called when the window is resized. All this does is simply 
 *	store the new width and height of the window which are then referenced by
 *	the draw function to set the correct viewing transforms 
 */
void Resize(int w, int h)
{
	winw = w;
	winh = h;

	/*
	 *	Allow drawing in full region of the screen
	 */
	glViewport(0,0,w,h);
}


/*----------------------------------------------------------------------------------------
 *	\brief	This function is called whenever a mouse button is pressed or released
 *	\param	button	-	GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, or GLUT_MIDDLE_BUTTON
 *	\param	state	-	GLUT_UP or GLUT_DOWN depending on whether the mouse was released
 *						or pressed respectivly. 
 *	\param	x		-	the x-coord of the mouse cursor.
 *	\param	y		-	the y-coord of the mouse cursor.
 */
void MouseButton(int button,int state,int x, int y)
{
	/*
	 *	update the mouse position
	 */
	TheMouse.x = x;
	TheMouse.y = y;

	/*
	 *	has the button been pressed or released?
	 */
	if (state == GLUT_DOWN) 
	{
		/*
		 *	This holds the location of the first mouse click
		 */
		if ( !(TheMouse.lmb || TheMouse.mmb || TheMouse.rmb) )
			{
			TheMouse.xpress = x;
			TheMouse.ypress = y;

			// check if we are editing a existing vertex
			UINT closest = -1;
			float dist = 9999999;
			Vector2f p=Vector2f(x,winh-y);
			for(UINT i=0;i < poly.vert.size();i++)
			{
			if((poly.vert[i]-p).length() < dist)
				{
				dist = (poly.vert[i]-p).length();
				closest = i;
				}
			}

			if(dist < 6)
			{
				editNr = closest;
			}
			else
				{
				poly.Add(Vector2f(x,winh-y));
				editNr=(UINT)poly.vert.size()-1;
//				poly.Shrink(SHRINKSIZE);
				}
			}

		/*
		 *	Which button was pressed?
		 */
		switch(button) 
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 1;
			break;
		case GLUT_MIDDLE_BUTTON:
			poly.vert.clear();
			TheMouse.mmb = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 1;
			break;
		}
	}
	else 
	{
		/*
		 *	Which button was released?
		 */
		switch(button) 
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 0;
			break;
		case GLUT_MIDDLE_BUTTON:
			TheMouse.mmb = 0;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 0;
			break;
		}
	}

	/*
	 *	Force a redraw of the screen. If we later want interactions with the mouse
	 *	and the 3D scene, we will need to redraw the changes.
	 */
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
 *	\brief	This function is called whenever the mouse cursor is moved AND A BUTTON IS HELD.
 *	\param	x	-	the new x-coord of the mouse cursor.
 *	\param	y	-	the new y-coord of the mouse cursor.
 */
void MouseMotion(int x, int y)
{
	/*
	 *	Calculate how much the mouse actually moved
	 */
	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	/*
	 *	update the mouse position
	 */
	TheMouse.x = x;
	TheMouse.y = y;

	if(TheMouse.lmb == 1)
	{
			poly.vert[editNr] = Vector2f(x,winh-y);
	}

	/*
	 *	Force a redraw of the screen
	 */
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
 *	\brief	This function is called whenever the mouse cursor is moved AND NO BUTTONS ARE HELD.
 *	\param	x	-	the new x-coord of the mouse cursor.
 *	\param	y	-	the new y-coord of the mouse cursor.
 */
void MousePassiveMotion(int x, int y)
{
	/*
	 *	Calculate how much the mouse actually moved
	 */
	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	/*
	 *	update the mouse position
	 */
	TheMouse.x = x;
	TheMouse.y = y;

	/*
	 *	Note that I'm not using a glutPostRedisplay() call here. The passive motion function 
	 *	is called at a very high frequency. We really don't want much processing to occur here.
	 *	Redrawing the screen every time the mouse moves is a bit excessive. Later on we 
	 *	will look at a way to solve this problem and force a redraw only when needed. 
	 */
}

/*----------------------------------------------------------------------------------------
 *
 */
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(winw,winh);
	glutInitWindowPosition(200,100);
	glutCreateWindow("03 - Mouse Motion");

	poly.Add(Vector2f(508,352));
	poly.Add(Vector2f(165,405));
	poly.Add(Vector2f(150,162));
	poly.Add(Vector2f(475,191));
	poly.Add(Vector2f(481,121));
	poly.Add(Vector2f(566,284));
/*
	poly.Add(Vector2f(50*size,10*size));
	poly.Add(Vector2f(50*size,130*size));
	poly.Add(Vector2f(10*size,130*size));
	poly.Add(Vector2f(10*size,90*size));
	poly.Add(Vector2f(40*size,70*size));
	poly.Add(Vector2f(10*size,50*size));
	poly.Add(Vector2f(10*size,10*size));
*/
	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glEnable(GL_POINT_SMOOTH);

	glutMainLoop();
}









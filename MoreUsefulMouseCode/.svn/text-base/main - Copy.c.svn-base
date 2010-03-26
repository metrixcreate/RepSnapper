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


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <sstream>

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
	point(float x, float y, int parent=-1, bool isValid=true, bool disable=false) : Vector2f(x,y){p=parent;valid=isValid, disabled=disable;}
	point(Vector2f p, int parent=-1, bool isValid=true, bool disable=false) : Vector2f(p) {p=parent;valid=isValid, disabled=disable;}
	int p;	// parent vertexNr
	bool valid;
	bool disabled;
};

class Poly{
public:
	Poly(){};
	void Shrink(float dist);
	void Add(Vector2f p){vert.push_back(p);}
	float angleAtVertex(int i);
	Vector2f &v(int i, bool shrinked=false);
	Vector2f e(int i, bool shrinked=false);
	Vector2f biplane(int i);
	void calcValid();
	bool isconvex(int i, bool shrinked=false);
	void draw(Vector2f offset);
	void handleShrinkErrors();

	vector<point> vert;			// points, indices into ..... a CuttingPlane or a GCode object
	vector<point> shrink;			// points, indices into ..... a CuttingPlane or a GCode object
};

void Poly::calcValid()
{
	for(UINT i=0;i<shrink.size();i++)
		shrink[i].valid = (e(i).getNormalized() - e(i, true).getNormalized()).length() < 1;
}


void Poly::draw(Vector2f offset)
{
/*	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	for(UINT i=0;i<vert.size();i++)
		glVertex2fv(&vert[i].x);
	glEnd();
*/

	glBegin(GL_LINES);
	glColor3f(1,1,1);
	for(UINT i=0;i<vert.size();i++)
	{
		glVertex2f(v(i).x+offset.x, v(i).y+offset.y);
		glVertex2f(v(i-1).x+offset.x, v(i-1).y+offset.y);
	}
	glEnd();

	glBegin(GL_LINES);
	for(UINT i=0;i<vert.size();i++)
	{
		stringstream oss;
		oss << i << "test:" << shrink[i].valid << "\n";
		cout << oss.str();

		if(shrink[i].disabled)
			continue;
		if(shrink[i].valid == true)
			glColor3f(0,1,0);
		else
			glColor3f(1,0,0);
		glVertex2f(v(i,true).x+offset.x, v(i,true).y+offset.y);
		glVertex2f(v(i+1,true).x+offset.x, v(i+1,true).y+offset.y);
	}
	glEnd();

	for(UINT i=0;i<shrink.size();i++)
	{
		stringstream oss;
		oss << i ;
		cout << oss.str();
		renderBitmapString(Vector3f(shrink[i].x+offset.x, shrink[i].y+offset.y, 0), GLUT_BITMAP_8_BY_13, oss.str());
	}
}

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

Vector2f &Poly::v(int i, bool shrinked)
{
	if(shrinked)
	{
		if(i < 0)
			i+= (int)shrink.size();
		return shrink[i%shrink.size()];
	}
	if(i < 0)
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

void Poly::Shrink(float dist)
{
	shrink.clear();
	// biplane
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
		shrink.push_back(bp);
	}
/*
	for(UINT i=0;i<vert.size();i++)
		angleAtVertex(i);

	glColor3f(0,1,0);
	glBegin(GL_LINES);
	// biplane
	for(UINT i=0;i<vert.size();i++)
		{
		Vector2f p=v(i);
		Vector2f bp=biplane(i)*20+p;
		glVertex2f(p.x, p.y);
		glVertex2f(bp.x, bp.y);
		}
	glEnd();*/

	calcValid();
}

void Poly::handleShrinkErrors()
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

				if(forward-backward == 2)	// case I
				{
					// handle: remove point, adjust next point to be the intersection of backward and forward edges
					shrink[i].disabled = true;
					// Intersect backward and forward edge
					Vector2f P1(v(backward, true));
					Vector2f P2(v(backward+1, true));
					Vector2f P3(v(forward, true));
					Vector2f P4(v(forward+1, true));

					// extend lines
					P2 = (P2-P1).getNormalized()*6000+P1;	// End end of backwards line
					P3 = (P3-P4).getNormalized()*6000+P4;	// Start end of forwards line

					glBegin(GL_LINES);
					glColor3f(1,1,1);
					glVertex2fv(&P1.x);
					glVertex2fv(&P2.x);
					glVertex2fv(&P3.x);
					glVertex2fv(&P4.x);
					glEnd();

					InFillHit hit;
					bool hitSomething = IntersectXY(P1,P2,P3,P4,hit);
					if(hitSomething)
					{
						shrink[forward%shrink.size()] = hit.p;
						shrink[(backward+1)%shrink.size()] = hit.p;
					}


				}

			}
		}
}
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

	poly.Shrink(40);
	glLineWidth(1);
	poly.draw(Vector2f(0,0));
	glLineWidth(3);
	poly.handleShrinkErrors();
	poly.draw(Vector2f(640,0));

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

			poly.Add(Vector2f(x,winh-y));
			poly.Shrink(20);
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
			poly.shrink.clear();
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

	int size=3;
	poly.Add(Vector2f(50*size,10*size));
	poly.Add(Vector2f(50*size,130*size));
	poly.Add(Vector2f(10*size,130*size));
	poly.Add(Vector2f(10*size,90*size));
	poly.Add(Vector2f(40*size,70*size));
	poly.Add(Vector2f(10*size,50*size));
	poly.Add(Vector2f(10*size,10*size));

	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);

	glutMainLoop();
}









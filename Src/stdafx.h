/* -------------------------------------------------------- *
*
* StdAfx.h
*
* Copyright 2009+ Michael Holm - www.kulitorum.com
*
* This file is part of RepSnapper and is made available under
* the terms of the GNU General Public License, version 2, or at your
* option, any later version, incorporated herein by reference.
*
* ------------------------------------------------------------------------- */
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#pragma warning( disable : 4311 4312 4244 4267 4800)

#define DEBUG_ECHO (1<<0)
#define DEBUG_INFO (1<<1)
#define DEBUG_ERRORS (1<<2)
#ifdef WIN32
	#include <windows.h>											// Header File For Windows
	#include <tchar.h>
typedef unsigned int        uint;
#endif
typedef unsigned int        UINT;
#include <stdio.h>
#include <FL/Fl.H>
#include <vmmlib/vmmlib.h>
#include <GL/gl.h>												// Header File For The OpenGL32 Library
#include <GL/glu.h>												// Header File For The GLu32 Library
//#include <gl\glaux.h>											// Header File For The GLaux Library
#include "math.h"                                               // Needed for sqrtf
#include "ArcBall.h"
#include "gcode.h"
#include "ModelViewController.h"
#include "Printer.h"
#include "ProcessController.h"
#include "search.h"
#include "stl.h"
#include "UI.h"
#include "xml/XML.H"

typedef unsigned int uint;

void MakeAcceleratedGCodeLine(Vector3f start, Vector3f end, float DistanceToReachFullSpeed, float extrusionFactor, GCode &code, float z, float minSpeedXY, float maxSpeedXY, float minSpeedZ, float maxSpeedZ, bool UseIncrementalEcode, bool Use3DGcode, float &E, bool EnableAcceleration);
bool IntersectXY(const Vector2f &p1, const Vector2f &p2, const Vector2f &p3, const Vector2f &p4, InFillHit &hit);	// Utilityfunction for CalcInFill
bool InFillHitCompareFunc(const InFillHit& d1, const InFillHit& d2);

extern void HSVtoRGB 	(const float &h, const float &s, const float &v, float &r,float &g,float &b);			
extern void RGBtoHSV 	(const float &r, const float &g, const float &b, float &h, float &s, float &v);
extern void RGBTOHSL	(float red, float green, float blue, float &hue, float &sat, float &lightness);
extern void	RGBTOYUV	(float r, float g, float b, float &y, float &u, float &v);
extern void YUVTORGB	(float y, float u, float v, float &r, float &g, float &b);


#include "ModelViewController.h"

#include "AsyncSerial.h"
#ifdef WIN32
extern "C"
{
#include <lua.h>
}

#include <luabind/luabind.hpp>

using namespace luabind;
#endif

extern ModelViewController *MVC;

// TODO: reference additional headers your program requires here

// ivconv
#include "ivcon.h"

/* -------------------------------------------------------- *
*
* RepSnapper.cpp
*
* Copyright 2009+ Michael Holm - www.kulitorum.com
*
* This file is part of RepSnapper and is made available under
* the terms of the GNU General Public License, version 2, or at your
* option, any later version, incorporated herein by reference.
*
* ------------------------------------------------------------------------- */
#include "stdafx.h"

//#include <windows.h>													// Header File For The Windows Library
#include <GL/gl.h>														// Header File For The OpenGL32 Library
#include <GL/glu.h>														// Header File For The GLu32 Library

#include "ModelViewController.h"

#include "gcode.h"
#include "UI.h"

GUI *gui;


#include <boost/thread.hpp>

using namespace std;

int main()
{
	gui = new GUI();
	MVC = gui->MVC;

	Fl::visual(FL_DOUBLE|FL_INDEX);

	char WindowTitle[100] = "GCodeView";
	char* W = &WindowTitle[0];
	MVC->gui = gui;
	MVC->serial.setGUI(gui);
	MVC->ProcessControl.gui = gui;
	gui->show(1,&W);
	return Fl::run();
}


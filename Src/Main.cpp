#include "stdafx.h"

// Program Entry (WinMain)

//#include <windows.h>													// Header File For The Windows Library
#include <GL/gl.h>														// Header File For The OpenGL32 Library
#include <GL/glu.h>														// Header File For The GLu32 Library

#include "gcode.h"
#include "UI.h"

CubeViewUI *cvui;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	cvui=new CubeViewUI;

	Fl::visual(FL_DOUBLE|FL_INDEX);

	char WindowTitle[100] = "GCodeView";
	char* W = &WindowTitle[0];
	cvui->show(1,&W);
//	cvui->code->Read("c:/ViewMe.gcode");

	return Fl::run();
}
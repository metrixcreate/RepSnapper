/* -------------------------------------------------------- *
*
* ModelViewController.h
*
* Copyright 2009+ Michael Holm - www.kulitorum.com
*
* This file is part of RepSnapper and is made available under
* the terms of the GNU General Public License, version 2, or at your
* option, any later version, incorporated herein by reference.
*
* ------------------------------------------------------------------------- */#pragma once

// View related
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include "UI.h"
#include <math.h>
#include "ArcBall.h"

// Model related
#include "gcode.h"
#include "stl.h"
#include "ProcessController.h"
#include "glutils.h"
#include "RepRapSerial.h"

enum SHRINK_QUALITY {SHRINK_FAST, SHRINK_NICE};

#pragma warning( disable : 4244 4267)

// Construct a model and a view, and link them together.

class ModelViewController : public Fl_Gl_Window
{
public:
	ModelViewController(int x,int y,int w,int h,const char *l);
	~ModelViewController();

	// RFO Functions
	void ReadRFO(string filename);

	// STL Functions
	void ReadStl(string filename);
	void OptimizeRotation() { ProcessControl.OptimizeRotation();}
	void RotateObject(float x, float y, float z, float a) {ProcessControl.RotateObject(Vector3f(x,y,z),a);}

	void SetShrinkQuality(string quality);

	void setObjectname(string name);
	void setFileMaterial(string material);
	void setFileType(string type);
	void setFileLocation(string location);

	// GCode Functions
	void ReadGCode(string filename) {ProcessControl.gcode.Read(filename);}
	void ConvertToGCode();
	void init();
	void SetUseIncrementalEcode(bool val) {ProcessControl.UseIncrementalEcode = val;}
	void SetUse3DGcode(bool val) {ProcessControl.Use3DGcode = val;}

	// My own view functions
	void draw();
	void DrawGridAndAxis();
	void WriteGCode(string filename) {/*ProcessControl.WriteGCode(filename);*/}
	void CopySettingsToGUI();

	void CenterView();
	int  handle(int);
	void Translate(string axis, float distance);
	void Scale(string axis, float distance);
	void Rotate(string axis, float distance);

	// Callback functions
	void resize (int x,int y, int width, int height);		// Reshape The Window When It's Moved Or Resized

	// LUA
	void RunLua(char* buffer);

	void SetDisplayGCode(bool val){ProcessControl.DisplayGCode = val;}
	void SetLuminanceShowsSpeed(bool val){ProcessControl.LuminanceShowsSpeed = val;}
	void CalcBoundingBoxAndZoom(){ProcessControl.CalcBoundingBoxAndZoom();}

	// GCode GUI Values
	void SetGCodeDrawStart(float val){ProcessControl.GCodeDrawStart = val; redraw();}
	void SetGCodeDrawEnd(float val){ProcessControl.GCodeDrawEnd = val; redraw();}
	void SetMinPrintSpeedXY(float val) {ProcessControl.MinPrintSpeedXY = val;}
	void SetMaxPrintSpeedXY(float val) {ProcessControl.MaxPrintSpeedXY = val;}
	void SetMinPrintSpeedZ(float val) {ProcessControl.MinPrintSpeedZ = val;}
	void SetMaxPrintSpeedZ(float val) {ProcessControl.MaxPrintSpeedZ = val;}
	void SetDistanceToReachFullSpeed(float val) {ProcessControl.DistanceToReachFullSpeed = val;}
	void SetExtrusionFactor(float val) {ProcessControl.extrusionFactor = val;}

	// STL GUI Values
	void SetLayerThickness(float val){ProcessControl.LayerThickness = val; redraw();}
	void SetCuttingPlaneValue(float val){ProcessControl.CuttingPlaneValue = val; redraw();}

	void SetDisplayEndpoints(bool val){ProcessControl.DisplayEndpoints = val; redraw();}
	void SetDisplayNormals(bool val){ProcessControl.DisplayNormals = val; redraw();}
	void SetDisplayBBox(bool val){ProcessControl.DisplayBBox = val; redraw();}
	void SetDisplayWireframe(bool val){ProcessControl.DisplayWireframe = val; redraw();}
	void SetDisplayWireframeShaded(bool val){ProcessControl.DisplayWireframeShaded = val; redraw();}

	void SetDisplayPolygons(bool val){ProcessControl.DisplayPolygons = val; redraw();}
	void SetDisplayAllLayers(bool val){ProcessControl.DisplayAllLayers = val; redraw();}
	void SetDisplayinFill(bool val){ProcessControl.DisplayinFill = val; redraw();}
	void SetPolygonOpasity(float val){ProcessControl.PolygonOpasity = val; redraw();}

	// CuttingPlane GUI values
	void SetInfillDistance(float val){ProcessControl.InfillDistance = val; redraw();}
	void SetInfillRotation(float val){ProcessControl.InfillRotation = val; redraw();}
	void SetInfillRotationPrLayer(float val){ProcessControl.InfillRotationPrLayer = val; redraw();}
	void SetOptimization(float val){ProcessControl.Optimization = val; redraw();}
	void SetExamine(float val){ProcessControl.Examine = val; redraw();}
	void SetExtrudedMaterialWidth(float val){ProcessControl.ExtrudedMaterialWidth = val; redraw();}

	void SetDisplayDebuginFill(bool val){ProcessControl.DisplayDebuginFill = val; redraw();}
	void SetDisplayDebug(bool val){ProcessControl.DisplayDebug = val; redraw();}
	void SetDisplayCuttingPlane(bool val){ProcessControl.DisplayCuttingPlane = val; redraw();}
	void SetDrawVertexNumbers(bool val){ProcessControl.DrawVertexNumbers = val; redraw();}
	void SetDrawLineNumbers(bool val){ProcessControl.DrawLineNumbers = val; redraw();}

	void SetShellOnly(bool val) {ProcessControl.ShellOnly = val; redraw();}
	void SetShellCount(uint val) {ProcessControl.ShellCount = val; redraw();}

	void SetEnableAcceleration(bool val) {ProcessControl.EnableAcceleration = val; redraw();}
	
	// Raft GUI values
	void SetRaftSize(float val){ProcessControl.RaftSize=val; redraw();}
	void SetRaftBaseLayerCount(int val){ProcessControl.RaftBaseLayerCount=val;}
	void SetRaftMaterialPrDistanceRatio(float val){ProcessControl.RaftMaterialPrDistanceRatio=val;}
	void SetRaftRotation(float val){ProcessControl.RaftRotation=val;}
	void SetRaftBaseDistance(float val){ProcessControl.RaftBaseDistance=val;}
	void SetRaftBaseThickness(float val){ProcessControl.RaftBaseThickness=val;}
	void SetRaftBaseTemperature(float val){ProcessControl.RaftBaseTemperature=val;}
	void SeRaftInterfaceLayerCount(int val){ProcessControl.RaftInterfaceLayerCount=val;}
	void SetRaftInterfaceMaterialPrDistanceRatio(float val){ProcessControl.RaftInterfaceMaterialPrDistanceRatio=val;}
	void SetRaftRotationPrLayer(float val){ProcessControl.RaftRotationPrLayer=val;}
	void SetRaftInterfaceDistance(float val){ProcessControl.RaftInterfaceDistance=val;}
	void SetRaftInterfaceThickness(float val){ProcessControl.RaftInterfaceThickness=val;}
	void SetRaftInterfaceTemperature(float val){ProcessControl.RaftInterfaceTemperature=val;}

	// Apron
	void SetApronEnable(bool val){ProcessControl.ApronEnable = val;}
	void SetApronPreview(bool val){ProcessControl.ApronPreview = val;}
	void SetApronSize(float val){ProcessControl.ApronSize = val;}
	void SetApronHeight(float val){ProcessControl.ApronHeight = val;}
	void SetApronCoverageX(float val){ProcessControl.ApronCoverageX = val;}
	void SetApronCoverageY(float val){ProcessControl.ApronCoverageY = val;}
	void SetApronDistanceToObject(float val){ProcessControl.ApronDistanceToObject = val;}
	void SetApronInfillDistance(float val){ProcessControl.ApronInfillDistance = val;}
	void SetRaftEnable(bool val){ProcessControl.RaftEnable = val;}


	// Rendering
	void SetPolygonVal(float val) {ProcessControl.PolygonVal=val;}
	void SetPolygonSat(float val) {ProcessControl.PolygonSat=val;}
	void SetPolygonHue(float val) {ProcessControl.PolygonHue=val;}
	void SetWireframeVal(float val) {ProcessControl.WireframeVal=val;}
	void SetWireframeSat(float val) {ProcessControl.WireframeSat=val;}
	void SetWireframeHue(float val) {ProcessControl.WireframeHue=val;}
	void SetNormalsSat(float val) {ProcessControl.NormalsSat=val;}
	void SetNormalsVal(float val) {ProcessControl.NormalsVal=val;}
	void SetNormalsHue(float val) {ProcessControl.NormalsHue=val;}
	void SetEndpointsSat(float val) {ProcessControl.EndpointsSat=val;}
	void SetEndpointsVal(float val) {ProcessControl.EndpointsVal=val;}
	void SetEndpointsHue(float val) {ProcessControl.EndpointsHue=val;}
	void SetGCodeExtrudeHue(float val) {ProcessControl.GCodeExtrudeHue=val;}
	void SetGCodeExtrudeSat(float val) {ProcessControl.GCodeExtrudeSat=val;}
	void SetGCodeExtrudeVal(float val) {ProcessControl.GCodeExtrudeVal=val;}
	void SetGCodeMoveHue(float val) {ProcessControl.GCodeMoveHue=val;}
	void SetGCodeMoveSat(float val) {ProcessControl.GCodeMoveSat=val;}
	void SetGCodeMoveVal(float val) {ProcessControl.GCodeMoveVal=val;}
	void SetHighlight(float val) {ProcessControl.Highlight = val;}
	void SetNormalsLength(float val){ProcessControl.NormalsLength = val;}
	void SetEndPointSize(float val){ProcessControl.EndPointSize = val;}

	void SetPrintMargin(string Axis, float value);

	// LUA
	ProcessController &getProcessController();

	// Communication
	void ConnectToPrinter(char on){
		if(on)
			{
			serial.Connect(ProcessControl.m_sPortName);
			}
		else
			{
			serial.DisConnect();
			}

	}
	void Print();
	void Continue();
	void SwitchHeat(bool on, float temp);
	void SetTargetTemp(float temp);
	void RunExtruder();
	void SetExtruderSpeed(int speed);
	void SetExtruderLength(int length);
	void SetExtruderDirection(bool reverse);
	void SendNow(string str);
	void setPort(string s){ProcessControl.m_sPortName = s;}

	void Home(string axis);
	void Move(string axis, float distance);
	void Goto(string axis, float position);
	void STOP();

	Matrix4f &SelectedNodeMatrix(uint objectNr = 1);
	void SelectedNodeMatrices(vector<Matrix4f *> &result );
	RFO_Object* SelectedParent();
	void GetSelectedRFO(RFO_Object **selectedObject, RFO_File **selectedFile);
	void newObject();

	RepRapSerial serial;
	bool m_bExtruderDirection; // True = forwards
	int  m_iExtruderSpeed;
	int m_iExtruderLength;
	float m_fTargetTemp;

	/*--------------ArcBall-------------------*/

	GLUquadricObj *quadratic;											// Used For Our Quadric

	Matrix4fT   Transform;
	Matrix3fT   LastRot;
	Matrix3fT   ThisRot;
	ArcBallT    *ArcBall;								                // NEW: ArcBall Instance
	Vector2fT    MousePt;												// NEW: Current Mouse Point
	Vector2f	downPoint;
	/*--------------View-------------------*/

	float zoom;
	void SetEnableLight(int lightNr, bool on){ if(on) lights[lightNr].TurnOn(); else lights[lightNr].TurnOff(); redraw(); }
	CGL_Light3D lights[4];
	
	/*--------------User interface (View)-------------------*/
	GUI *gui;
	ProcessController ProcessControl;
};

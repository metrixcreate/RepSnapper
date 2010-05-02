#pragma once

//Physical Pin Mappings for Direct Drive

/*
ATMega644P

INT0 (D 0) PB0  1|        |40  PA0 (AI 0 / D31)
INT1 (D 1) PB1  2|        |39  PA1 (AI 1 / D30)
INT2 (D 2) PB2  3|        |38  PA2 (AI 2 / D29)
 PWM (D 3) PB3  4|        |37  PA3 (AI 3 / D28)
 PWM (D 4) PB4  5|        |36  PA4 (AI 4 / D27)
MOSI (D 5) PB5  6|        |35  PA5 (AI 5 / D26)
MISO (D 6) PB6  7|        |34  PA6 (AI 6 / D25)
 SCK (D 7) PB7  8|        |33  PA7 (AI 7 / D24)
           RST  9|        |32  AREF
           VCC 10|        |31  GND 
           GND 11|        |30  AVCC
         XTAL2 12|        |29  PC7 (D 23)
         XTAL1 13|        |28  PC6 (D 22)
RX0 (D 8)  PD0 14|        |27  PC5 (D 21) TDI
TX0 (D 9)  PD1 15|        |26  PC4 (D 20) TDO
RX1 (D 10) PD2 16|        |25  PC3 (D 19) TMS
TX1 (D 11) PD3 17|        |24  PC2 (D 18) TCK
PWM (D 12) PD4 18|        |23  PC1 (D 17) SDA
PWM (D 13) PD5 19|        |22  PC0 (D 16) SCL
PWM (D 14) PD6 20|        |21  PD7 (D 15) PWM

*/

/****************************************************************************************
* Sanguino/RepRap Motherboard with direct-drive extruders
*
****************************************************************************************
#elif MOTHERBOARD == 1

#define DEBUG_PIN        0

//Physical Pins (1-40)

#define X_STEP_PIN (byte)15  //Physical Pin - 21
#define X_DIR_PIN (byte)18  //Physical Pin - 24
#define X_MIN_PIN (byte)20  //Physical Pin - 26
#define X_MAX_PIN (byte)21  //Physical Pin - 27
#define X_ENABLE_PIN (byte)19  //Physical Pin - 25

#define Y_STEP_PIN (byte)23  //Physical Pin - 29
#define Y_DIR_PIN (byte)22  //Physical Pin - 28
#define Y_MIN_PIN (byte)25  //Physical Pin - 34
#define Y_MAX_PIN (byte)26  //Physical Pin - 35
#define Y_ENABLE_PIN (byte)19  //Physical Pin - 25

#define Z_STEP_PIN (byte)29  //Physical Pin - 38
#define Z_DIR_PIN (byte)30  //Physical Pin - 39
#define Z_MIN_PIN (byte)2  //Physical Pin - 3
#define Z_MAX_PIN (byte)1  //Physical Pin - 2
#define Z_ENABLE_PIN (byte)31  //Physical Pin - 40


#define EXTRUDER_0_MOTOR_SPEED_PIN   (byte)12  //Physical Pin - 18
#define EXTRUDER_0_MOTOR_DIR_PIN     (byte)16  //Physical Pin - 22
#define EXTRUDER_0_HEATER_PIN        (byte)14  //Physical Pin - 20
#define EXTRUDER_0_FAN_PIN           (byte)3  //Physical Pin - 4
#define EXTRUDER_0_TEMPERATURE_PIN  (byte)4  //Physical Pin - 36        // Analogue input
#define EXTRUDER_0_VALVE_DIR_PIN     (byte)17  //Physical Pin - 23
#define EXTRUDER_0_VALVE_ENABLE_PIN  (byte)13  //Physical Pin - 19    // Valve needs to be redesigned not to need this
#define EXTRUDER_0_STEP_ENABLE_PIN  (byte)3  //Physical Pin - 4      // 3 - Conflicts with the fan; set -ve if no stepper

#define EXTRUDER_1_MOTOR_SPEED_PIN   (byte)4  //Physical Pin - 5
#define EXTRUDER_1_MOTOR_DIR_PIN    (byte)0  //Physical Pin - 1
#define EXTRUDER_1_HEATER_PIN        (byte)24  //Physical Pin - 33
#define EXTRUDER_1_FAN_PIN           (byte)7  //Physical Pin - 8
#define EXTRUDER_1_TEMPERATURE_PIN  (byte)3  //Physical Pin - 37       // Analogue input
#define EXTRUDER_1_VALVE_DIR_PIN    (byte) 6  //Physical Pin - 7  
#define EXTRUDER_1_VALVE_ENABLE_PIN (byte)5  //Physical Pin - 6       // Valve needs to be redesigned not to need this
#define EXTRUDER_1_STEP_ENABLE_PIN  (byte)-1  //Physical Pin - NONE      // 7 - Conflicts with the fan; set -ve if no stepper
*/
#undef WIN32

#ifdef WIN32
#include "Serial/SerialEx.h"
#endif

#include "UI.h"
#include "AsyncSerial.h"

class RepRapSerial : public BufferedAsyncSerial
{
public:
	RepRapSerial(){m_bPrinting = false; m_iLineNr = 0; gui=0;m_bConnected=false; debugMask =  DEBUG_ECHO | DEBUG_INFO | DEBUG_ERRORS;logFile=0;}
	void open(const std::string& devname, unsigned int baud_rate)
	{
		try{
			BufferedAsyncSerial::open(devname, baud_rate);
		} catch (std::exception& e) {
			stringstream oss;
			oss<<"Exception: " << e.what() << ":" << devname << endl;
			debugPrint(oss.str(), true);
		}
	}
	// Event handler
//	virtual void OnEvent (EEvent eEvent, EError eError);

	void OnEvent(char* data, size_t size);

	void AddToBuffer(string s){buffer.push_back(s);}
	void SendNow(string s);
	void Clear() { m_bPrinting = false; m_iLineNr = 0; SetLineNr(-1); buffer.clear();}
	uint Length() { return buffer.size();}
	void StartPrint();
	void SetLineNr(int nr);
	void SetDebugMask(int mask, bool on);
	void SetDebugMask();
	void setGUI(GUI* g){ gui=g;}
	void SendNextLine();
	void SendData(string s, const int lineNr);
	void Connect(string port);
	void DisConnect();
	bool isPrinting(){return m_bPrinting;}
	bool m_bPrinting;

private:
	void debugPrint(string s, bool selectLine = false);
	void echo(string s);
	vector<string> buffer;
	bool m_bConnected;
	uint m_iLineNr;
	string InBuffer;
	short debugMask;

	GUI* gui;
	FILE* logFile;
	
/*
	// Very private :P
	FT_HANDLE fthandle;
	FT_STATUS res;
	LONG COMPORT;

	char COMx[5];
	int n;

	DCB dcb;
	HANDLE hCommPort;
	BOOL fSuccess;	*/


};

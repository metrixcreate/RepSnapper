#include "stdafx.h"
#include "RepRapSerial.h"
#include "Convert.h"

void RepRapSerial::debugPrint(string s, bool selectLine)
{
	uint a=0;
	while(a<s.length())
	{
		if(s[a] == '\r' || s[a] == '\n') s[a] = ' ';
		a++;
	}
	time_t rawtime;
	tm * ptm;
	time ( &rawtime );
	ptm = localtime ( &rawtime );
	std::stringstream oss;
	oss << setfill('0') << setw(2) << ptm->tm_hour << ":" << setfill('0') << setw(2) << ptm->tm_min << ":" << setfill('0') << setw(2) << ptm->tm_sec << " Send >>" << s.c_str() << "\n";
	s=oss.str();

	if(gui)
		{
		gui->CommunationLog->add(s.c_str());
		if(gui->AutoscrollButton->value())
			gui->CommunationLog->bottomline(gui->CommunationLog->size());
		if(selectLine)
			{
			gui->CommunationLog->select(gui->CommunationLog->size());
			gui->ErrorLog->add(s.c_str());
			if(gui->AutoscrollButton->value())
				gui->ErrorLog->bottomline(gui->ErrorLog->size());
			}

		while(gui->CommunationLog->size() > MVC->ProcessControl.KeepLines)
			gui->CommunationLog->remove(1);
		while(gui->ErrorLog->size() > MVC->ProcessControl.KeepLines)
			gui->ErrorLog->remove(1);
		while(gui->Echo->size() > MVC->ProcessControl.KeepLines)

			gui->Echo->remove(1);
		}
	else
		printf("%s", s.c_str());

	if(MVC->ProcessControl.FileLogginEnabled)
	{
	// is the files open?
	if(logFile == 0)
		{
		// Append or new?
		if(MVC->ProcessControl.ClearLogfilesWhenPrintStarts)
			logFile = fopen("./RepSnapper.log", "w");
		else
			{
			logFile = fopen("./RepSnapper.log", "a");
			fseek ( logFile , 0 , SEEK_END );	// goto end of file
			}
		}
	fputs ( s.c_str(), logFile );
	}

};
void RepRapSerial::echo(string s)
{

	uint a=0;
	while(a<s.length())
	{
		if(s[a] == '\r' || s[a] == '\n') s[a] = ' ';
		a++;
	}
	time_t rawtime;
	tm * ptm;
	time ( &rawtime );
	ptm = localtime ( &rawtime );
	std::stringstream oss;
	oss << setfill('0') << setw(2) << ptm->tm_hour << ":" << setfill('0') << setw(2) << ptm->tm_min << ":" << setfill('0') << setw(2) << ptm->tm_sec << " Echo >>" << s.c_str() << "\n";
	s=oss.str();

	if(gui)
	{
		Fl::lock();
		gui->Echo->add(s.c_str());
		if(gui->AutoscrollButton->value())
		{
			gui->Echo->bottomline(gui->Echo->size());
			gui->Echo->redraw();
		}
		Fl::unlock();
	}
	else
		printf("%s", s.c_str());

	if(MVC->ProcessControl.FileLogginEnabled)
	{
	// is the files open?
	if(logFile == 0)
		{
		// Append or new?
		if(MVC->ProcessControl.ClearLogfilesWhenPrintStarts)
			logFile = fopen("./RepSnapper.log", "w");
		else
			{
			logFile = fopen("./RepSnapper.log", "a");
			fseek ( logFile , 0 , SEEK_END );	// goto end of file
			}
		}
	fputs ( s.c_str(), logFile );
	}

};

void RepRapSerial::StartPrint()
{
	m_iLineNr = 0;
	m_bPrinting = true;
	SendNextLine();
	SendNextLine();
	SendNextLine();
	SendNextLine();


}

void RepRapSerial::SendNextLine()
{

	if(m_bPrinting == false)
		return;
	if(m_iLineNr < buffer.size())
		{
		string a = buffer[m_iLineNr];
		SendData(a.c_str(), m_iLineNr);
		m_iLineNr++;
		}
	else	// we are done
		{
		m_bPrinting = false;
		buffer.clear();
		gui->ProgressBar->label("Print done");
		MVC->PrintDone();
		return;
		}
	if(gui)
		gui->ProgressBar->value((float)m_iLineNr);

}

void RepRapSerial::SendNow(string s)
{

	s+= "\n";
	debugPrint( string("Sending:") + s);
	write(s);

}
void RepRapSerial::SendData(string s, const int lineNr)
{

	// Apply Downstream Multiplier

	float DSMultiplier = 1.0f;
	if(gui)
		DSMultiplier = gui->DownstreamMultiplierSlider->value();

	if(DSMultiplier != 1.0f)
	{
		size_t pos = s.find( "F", 0);
		if( pos != string::npos )	//string::npos means not defined
		{
			size_t end = s.find( " ", pos);
			if(end == string::npos)
				end = s.length()-1;
			string number = s.substr(pos+1,end);
			string start = s.substr(0,pos+1);
			string after = s.substr(end+1,s.length()-1);
			float old_speed = ToFloat(number);
			s.clear();
			std::stringstream oss;
			oss << start << old_speed*DSMultiplier << " " <<after;
			s=oss.str();
		}
	}


	string buffer;
	std::stringstream oss;
	oss << " N" << lineNr << " ";//*";
	buffer += oss.str();
	// strip comments
	
	string tmp=s;
	size_t found;
	found=tmp.find_first_of(";");
	if(found!=string::npos)
		tmp=tmp.substr(0,found);
	found=tmp.find_last_not_of(" ");
	if(found!=string::npos)
		tmp=tmp.substr(0,found+1);

	for(uint i=0;i<tmp.length();i++)
		if((tmp[i] < '*' || tmp[i] > 'z') && tmp[i] != ' ')	// *-z (ascii 42-122)
			tmp.erase(tmp.begin()+i--);

	buffer += tmp;
	buffer += " *";
	oss.str( "" );
	// Calc checksum.
	short checksum = 0;
	unsigned char count=0;
	while(buffer[count] != '*')
		checksum = checksum^buffer[count++];

	oss << checksum;//std::setfill('0') << std::setw(2) << buffer.length()+2;
	buffer += oss.str();
	debugPrint( string("SendData:") + buffer);
	buffer += "\r\n";
	write(buffer);
}


extern void TempReadTimer(void *);

void RepRapSerial::Connect(string port)
{
	open(port.c_str(), 19200);
	Fl::add_timeout(1.0f, &TempReadTimer);
}


void RepRapSerial::DisConnect()
{
	close();
	m_bConnected = false;

}

void RepRapSerial::SetLineNr(int nr)
{

	SendData("M110", nr);	// restart lineNr count

}

void RepRapSerial::SetDebugMask(int mask, bool on)
{
	if(on)
		debugMask |= mask;
	else
		debugMask &=~mask;

	SetDebugMask();

}
void RepRapSerial::SetDebugMask()
{
	std::stringstream oss;
	string buffer="M111 S";
	oss << debugMask;
	buffer += oss.str();
	SendNow(buffer);
}

void RepRapSerial::OnEvent(char* data, size_t dwBytesRead)
{
	int a=0;
	// Read data, until there is nothing left
	data[dwBytesRead] = '\0';
	InBuffer += data;		// Buffer data for later analysis

	// Endchars = \r\n

	//		debugPrint( string("Received:\"") + szBuffer +"\" (" + stringify(dwBytesRead));
	{
		// Check inbuffer for good stuff

		// remove leading \n and \r
		while(InBuffer.length() > 0 && (InBuffer.substr(0,1) == "\n" ||  InBuffer.substr(0,1) == "\r"))
			InBuffer = InBuffer.substr(1, InBuffer.length()-1);

		if(InBuffer[0] == 1)	// Ctrl
		{
			InBuffer = InBuffer.substr(2, InBuffer.length()-2);
			debugPrint("Recieved a Ctrl character", true);
		}
		if(InBuffer.size() == 0)
			return;
		size_t found;
		found=InBuffer.find_first_of("\r");

		while (found!=string::npos && found != 0)
		{
			string command = InBuffer.substr(0,found);
			if(0)
			{
				stringstream oss;
				oss << "Command:" << command;
				debugPrint(oss.str(), true);
			}
			if (command == "ok")	// most common, first
			{
				//					debugPrint("Recieved: Ok");
				if(m_bPrinting)
				{
					SendNextLine();
				}
			}
			else if(command.substr(0,5) == "Echo:") // search, there's a parameter int (temperature)
			{
				string parameter = command.substr(5,command.length()-5);
				echo( string("Echo:") + parameter);
				// Check parameter
			}
			else if(command.substr(0,2) == "T:") // search, there's a parameter int (temperature)
			{
				string parameter = command.substr(2,command.length()-2);
				debugPrint( string("Received:") + command+ " with parameter " + parameter);

				gui->CurrentTempText->value(parameter.c_str());
				// Check parameter

			}
			else if(command == "start")
			{
				debugPrint( string("Received: start"));
				// Tell GUI we are ready to go.
				int a=0;
			}
			else if(command.substr(0,3) == "E: ") // search, there's a parameter int (temperature_error, wait_till_hot)
			{
				string parameter = command.substr(3,command.length()-3);
				debugPrint( string("Received:") + command+ " with parameter " + parameter);
				// Check parameter

			}
			else if(command.substr(0,3) == "ok ") // search, there's a parameter string (debugstring)
			{
				string parameter = command.substr(3,command.length()-3);
				debugPrint( string("Received:") + command+ " with parameter " + parameter + "**************************************", true);
			}
			else if(command.substr(0,5) == "huh? ") // search, there's a parameter string (unknown command)
			{
				string parameter = command.substr(6,command.length()-5);
				debugPrint( string("Received:") + command+ " with parameter " + parameter, true);

				if(m_bPrinting)
				{
					SendNextLine();
				}
			}
			else if(command.substr(0,7) == "Resend:") // search, there's a parameter string (unknown command)
			{
				string parameter = command.substr(7,command.length()-7);
				debugPrint( string("Received:") + command+ " with parameter " + parameter, true);

				std::stringstream iss(parameter);
				iss >> m_iLineNr;	// Rewind to requested line

				if(m_bPrinting)
				{
					SendNextLine();
				}

			}
			else if(command.substr(0,45) == "[FIRMWARE WARNING] invalid M-Code received: M") // search, there's a parameter string (unknown Mcode)
			{
				string parameter = command.substr(45,command.length()-45);
				debugPrint( string("Received:") + command+ " with parameter " + parameter, true);
			}
			else	// Unknown response
			{
				debugPrint( string("Received:") + command+"\n", true);
			}
			InBuffer = InBuffer.substr(found);	// 2 end-line characters, \n\r
			// Empty eol crap
			while(InBuffer.length() > 0 && (InBuffer.substr(0,1) == "\n" ||  InBuffer.substr(0,1) == "\r"))
				InBuffer = InBuffer.substr(1, InBuffer.length()-1);
			found=InBuffer.find_first_of("\r");
		}
	}
}

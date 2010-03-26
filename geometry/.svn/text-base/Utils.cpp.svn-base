// utils.cpp : implementation file
//
#include "stdafx.h"
//#include "SHELLAPI.H"
#include "utils.h"


BOOL PeekAndPump()
{
	static MSG msg;

	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) {
		if (!AfxGetApp()->PumpMessage()) {
			::PostQuitMessage(0);
			return FALSE;
		}	
	}

	return TRUE;
}

BOOL FileOpen(FILE **fp, LPCTSTR Name, char *mode, BOOL bIssueWarning /* = TRUE */)
{
	*fp = fopen(Name,mode);
	if (!(*fp)) {
		if (bIssueWarning) {
			CString str;
			str.Format("Unable to open %s.",Name);
			AfxMessageBox(str);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL SetBarText(LPCTSTR fmt, ...)
{
	va_list args;
	char buffer[512];

	CFrameWnd *pFrame = (CFrameWnd*)AfxGetMainWnd();

	/* pFrame->SetMessageText() */
	CWnd *bar = pFrame->GetMessageBar();

	if (bar != NULL) {
		va_start(args, fmt);
		vsprintf(buffer, fmt, args);
		va_end(args);
		bar->SetWindowText(buffer);
	}
	return (bar != NULL);
}

void Message(LPCTSTR fmt, ...)
{
	va_list args;
	char buffer[1024];
	CString str;
	str.Empty();

	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);
	str += buffer;
	AfxMessageBox(str);
}

BOOL Error(LPCTSTR fmt, ...)
{
	va_list args;
	char buffer[1024];
	CString str = "Error occurred: "; 

	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);
	str += buffer;
	AfxMessageBox(str);

	return FALSE;
}

BOOL Error(FILE* fp, LPCTSTR fmt, ...)
{
	va_list args;
	char buffer[1024];
	CString str = "Error occurred: "; 

	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);
	str += buffer;
	AfxMessageBox(str);

	if (fp) fclose(fp);
	return FALSE;
}

CString GetFieldFromString(CString& ref, int nIndex, TCHAR ch)
{
	CString strReturn;
	LPCTSTR pstrStart = ref.LockBuffer();
	LPCTSTR pstrBuffer = pstrStart;
	int nCurrent = 0;
	int nStart = 0;
	int nEnd = 0;
	int nOldStart = 0;

	while (nCurrent <= nIndex && *pstrBuffer != _T('\0') && *pstrBuffer != _T('\n'))
	{
		if (*pstrBuffer == ch)
		{
			nOldStart = nStart;
			nStart = nEnd+1;
			nCurrent++;
		}
		nEnd++;
		pstrBuffer++;
	}

	ref.UnlockBuffer();

	if (nCurrent < nIndex) 
//	if (*pstrBuffer == _T('\0'))
	{
		TRACE("Warning: GetStringField - Couldn't find field %d.\n", nIndex);
		return strReturn;
	}
	return ref.Mid(nOldStart, nEnd-nOldStart-1);
}

BOOL EnumSerialPorts(CStringArray& PortNames)
{
	HKEY hKey;
	DWORD PortCount;

	PortNames.RemoveAll();

	if ( ERROR_SUCCESS != RegOpenKey(HKEY_LOCAL_MACHINE,
									_T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 
									&hKey ))
	{
		TRACE("Registry Key is missing.");
		return FALSE;
	}

    RegQueryInfoKey (hKey, NULL, NULL, NULL, NULL, NULL, NULL, &PortCount, 
					 NULL, NULL, NULL, NULL);

	if (PortCount == 0)
    {
		RegCloseKey(hKey);
		TRACE("There are no serial ports.");
		return FALSE;
	}

	TCHAR vname[50];
	DWORD vnsize = 50;
	char pname[50];
	DWORD pnsize = 50;

	for (DWORD nPort = 0; nPort < PortCount; nPort++ )
	{
		RegEnumValue(hKey, nPort, &vname[0], &vnsize, NULL,
					 NULL, (unsigned char*)&pname[0], &pnsize );
		PortNames.Add(pname);
	}
	return TRUE;
}
/*
#include "winsock2.h"
// Link in with ws2_32.lib
BOOL GetIPaddress(CString& strIPaddress, CString& strIPnumbers)
{
	CString strIPaddress;
	char buffer[1024];
	hostent *hostinfo = NULL;
		
	if (gethostname(buffer, 1024) == SOCKET_ERROR)
		return FALSE;  
	
	if ((hostinfo = gethostbyname(buffer)) == NULL)
		return FALSE;  
	
	strIPaddress = inet_ntoa (*(struct in_addr *) *hostinfo->h_addr_list);

    strIPnumbers.Format("%u.%u.%u.%u", (BYTE) phe->h_addr_list[0] [0],
									   (BYTE) phe->h_addr_list[0] [1],
									   (BYTE) phe->h_addr_list[0] [2],
									   (BYTE) phe->h_addr_list[0] [3]);
	
	return TRUE;
 }
*/

/*
LONG CMyView::TwipsToPixels(long lTwips, short nDirection)
{
	const int nTwipsPerInch = 1440;
	int nPixelsPerInch;
	CClientDC dc(this);
	if (nDirection == 0)     // Horizontal
		nPixelsPerInch = dc.GetDeviceCaps(LOGPIXELSX);
	else                    // Vertical
		nPixelsPerInch = dc.GetDeviceCaps(LOGPIXELSY);
	return (LONG) (lTwips*nPixelsPerInch)/nTwipsPerInch;
}

LONG CMyView::PixelsToTwips(long lPixels, short nDirection)
{
	const int nTwipsPerInch = 1440;
	int nPixelsPerInch;
	CClientDC dc(this);
	if (nDirection == 0)     // Horizontal
		nPixelsPerInch = dc.GetDeviceCaps(LOGPIXELSX);
	else                    // Vertical
		nPixelsPerInch = dc.GetDeviceCaps(LOGPIXELSY);
	return (LONG) (lPixels*nTwipsPerInch)/nPixelsPerInch;
}
*/

/*
#include "shlobj.h"

    char szTitle[] = "Select Directory for Whatever Reason";
	char szPath[MAX_PATH];

	BROWSEINFO bi;
    bi.hwndOwner = GetSafeHwnd();
    bi.pidlRoot = NULL;
    bi.pszDisplayName = NULL;
    bi.lpszTitle = szTitle;
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
    bi.lpfn = NULL;
    bi.lParam = NULL;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != NULL)
    {
		SHGetPathFromIDList(pidl, szPath);

		LPMALLOC pMalloc;    
		SHGetMalloc(&pMalloc);
		pMalloc->Free(pidl);
	}
*/
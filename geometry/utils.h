// Utils.h : interface file
//

#ifndef _INCLUDE_UTILS_H_
#define _INCLUDE_UTILS_H_

BOOL FileOpen(FILE **fp, LPCTSTR Name, char *mode, BOOL bIssueWarning = TRUE);
BOOL PeekAndPump();
BOOL SetBarText(LPCTSTR fmt, ...);

void Message(LPCTSTR fmt, ...);
BOOL Error(LPCTSTR fmt, ...);
BOOL Error(FILE* fp, LPCTSTR fmt, ...);

CString GetFieldFromString(CString& ref, int nIndex, TCHAR ch = TCHAR(','));

#endif
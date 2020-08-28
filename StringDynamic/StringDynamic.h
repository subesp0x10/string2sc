
// StringDynamic.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CStringDynamicApp:
// See StringDynamic.cpp for the implementation of this class
//

class CStringDynamicApp : public CWinApp
{
public:
	CStringDynamicApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CStringDynamicApp theApp;

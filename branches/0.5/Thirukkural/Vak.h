// Vak.h : main header file for the VAK application
//

#if !defined(AFX_VAK_H__E6C784C8_0350_11D5_8A27_0050FC0C3667__INCLUDED_)
#define AFX_VAK_H__E6C784C8_0350_11D5_8A27_0050FC0C3667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVakApp:
// See Vak.cpp for the implementation of this class
//

class CVakApp : public CWinApp
{
public:
	CVakApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVakApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVakApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VAK_H__E6C784C8_0350_11D5_8A27_0050FC0C3667__INCLUDED_)

// Vaachaka.h : main header file for the VAACHAKA application
//

#if !defined(AFX_VAACHAKA_H__E7D08260_87E4_4221_93EE_3D7D27076D9C__INCLUDED_)
#define AFX_VAACHAKA_H__E7D08260_87E4_4221_93EE_3D7D27076D9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVaachakaApp:
// See Vaachaka.cpp for the implementation of this class
//

class CVaachakaApp : public CWinApp
{
public:
	CVaachakaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVaachakaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVaachakaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VAACHAKA_H__E7D08260_87E4_4221_93EE_3D7D27076D9C__INCLUDED_)

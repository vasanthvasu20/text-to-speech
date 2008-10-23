// DlgProxy.h : header file
//
/**********************************************************************
 * File:                DlgProxy.h  
 * Description:         
 * Author:              
 *
 * (C) Copyright 2008, MILE Lab, IISc.
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 ** http://www.apache.org/licenses/LICENSE-2.0
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 *
 **********************************************************************/

#if !defined(AFX_DLGPROXY_H__E6C784CC_0350_11D5_8A27_0050FC0C3667__INCLUDED_)
#define AFX_DLGPROXY_H__E6C784CC_0350_11D5_8A27_0050FC0C3667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVakDlg;

/////////////////////////////////////////////////////////////////////////////
// CVakDlgAutoProxy command target

class CVakDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CVakDlgAutoProxy)

	CVakDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CVakDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVakDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVakDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CVakDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CVakDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CVakDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__E6C784CC_0350_11D5_8A27_0050FC0C3667__INCLUDED_)

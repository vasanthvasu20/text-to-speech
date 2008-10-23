// DlgProxy.cpp : implementation file
//

/**********************************************************************
 * File:                DlgProxy.cpp  
 * Description:         Wizard generated file
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

#include "stdafx.h"
#include "Vak.h"
#include "DlgProxy.h"
#include "VakDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVakDlgAutoProxy

IMPLEMENT_DYNCREATE(CVakDlgAutoProxy, CCmdTarget)

CVakDlgAutoProxy::CVakDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CVakDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CVakDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CVakDlgAutoProxy::~CVakDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CVakDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CVakDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CVakDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVakDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CVakDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IVak to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {E6C784C5-0350-11D5-8A27-0050FC0C3667}
static const IID IID_IVak =
{ 0xe6c784c5, 0x350, 0x11d5, { 0x8a, 0x27, 0x0, 0x50, 0xfc, 0xc, 0x36, 0x67 } };

BEGIN_INTERFACE_MAP(CVakDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CVakDlgAutoProxy, IID_IVak, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {E6C784C3-0350-11D5-8A27-0050FC0C3667}
IMPLEMENT_OLECREATE2(CVakDlgAutoProxy, "Vak.Application", 0xe6c784c3, 0x350, 0x11d5, 0x8a, 0x27, 0x0, 0x50, 0xfc, 0xc, 0x36, 0x67)

/////////////////////////////////////////////////////////////////////////////
// CVakDlgAutoProxy message handlers

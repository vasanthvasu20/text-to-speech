// DlgProxy.h : header file
//

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

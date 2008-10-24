// VaachakaDlg.h : header file
//

#if !defined(AFX_VAACHAKADLG_H__7A8630B8_C260_40D7_B041_8A485C1768D8__INCLUDED_)
#define AFX_VAACHAKADLG_H__7A8630B8_C260_40D7_B041_8A485C1768D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVaachakaDlg dialog

class CVaachakaDlg : public CDialog
{
// Construction
public:
	CVaachakaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVaachakaDlg)
	enum { IDD = IDD_VAACHAKA_DIALOG };
	CString	m_strKannada;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVaachakaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVaachakaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSpeak();
	afx_msg void OnRepeat();
	afx_msg void OnFileSpeak();
	afx_msg void OnFileRepeat();
	afx_msg void OnFileExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// FUnction Declarations
	CString ConvertToPhonetic();
	CString ApplyKannadaRules(CString);
	CString ConvertToNumbers();
	char *Convert(char m_strTemp[]);
	// Variable Declarations
	CString m_strPhoneticData;
	CString m_strActualPath;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VAACHAKADLG_H__7A8630B8_C260_40D7_B041_8A485C1768D8__INCLUDED_)

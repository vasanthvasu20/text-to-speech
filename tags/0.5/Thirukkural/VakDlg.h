// VakDlg.h : header file
//

#if !defined(AFX_VAKDLG_H__E6C784CA_0350_11D5_8A27_0050FC0C3667__INCLUDED_)
#define AFX_VAKDLG_H__E6C784CA_0350_11D5_8A27_0050FC0C3667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVakDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CVakDlg dialog

class CVakDlg : public CDialog
{
	DECLARE_DYNAMIC(CVakDlg);
	friend class CVakDlgAutoProxy;
	
// Construction
public:
	CVakDlg(CWnd* pParent = NULL);	// Standard constructor
	virtual ~CVakDlg();
	int FileOpenFlag;
	int FlagSpace;
	char *m_strText;
	int Flagnumber;
	CString m_strActualPath;
	CString Convert(CString m_strTemp);
	CString ConvertNumbers();
public:
// Dialog Data
	//{{AFX_DATA(CVakDlg)
	enum { IDD = IDD_VAK_DIALOG };
	CButton	m_nSpeak;
	CButton	m_strOptions;
	CString	m_strData;
	CString m_strEnglish;
	CString	m_strUpdateData;
	CString m_strPhoneticData;
	CString m_strConvEnglish;
	int FLAG;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVakDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CVakDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CVakDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnSpeak();
	afx_msg void OnOptions();
	afx_msg void OnPlayAgain();
	afx_msg void OnUpdateData();
	afx_msg CString OnConvertData(CString);
	afx_msg CString ConvertToPhonetic(CString);
	afx_msg CString ApplyTamilRules(CString);
	afx_msg void OnSpeakfile();
	afx_msg void OnFileSpeak();
	afx_msg void OnFileSpeakfile();
	afx_msg void OnFileWavewrite();
	afx_msg void OnFileRepeat();
	afx_msg void OnFileSavefile();
	afx_msg void OnFileExit();
	afx_msg void OnFileSavetext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VAKDLG_H__E6C784CA_0350_11D5_8A27_0050FC0C3667__INCLUDED_)

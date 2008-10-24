// VaachakaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vaachaka.h"
#include "VaachakaDlg.h"
#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVaachakaDlg dialog

CVaachakaDlg::CVaachakaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVaachakaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVaachakaDlg)
	m_strKannada = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CFile JunkFile;
	JunkFile.Open("Junk",CFile::modeCreate,NULL);
	m_strActualPath=JunkFile.GetFilePath();
	int i=m_strActualPath.GetLength()-1;
	m_strActualPath.SetAt(i-3,'$');
}

void CVaachakaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVaachakaDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strKannada);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVaachakaDlg, CDialog)
	//{{AFX_MSG_MAP(CVaachakaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SPEAK, OnSpeak)
	ON_BN_CLICKED(IDC_REPEAT, OnRepeat)
	ON_COMMAND(ID_FILE_SPEAK, OnFileSpeak)
	ON_COMMAND(ID_FILE_REPEAT, OnFileRepeat)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVaachakaDlg message handlers

BOOL CVaachakaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVaachakaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVaachakaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVaachakaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVaachakaDlg::OnSpeak() 
{
	BeginWaitCursor();
	UpdateData(TRUE);
	//TRACE("\n m_strKannada = %s",m_strKannada);
	m_strPhoneticData = ConvertToPhonetic();
	m_strPhoneticData = ConvertToNumbers();
	TRACE("\n In Applying Rules ");
	m_strPhoneticData = ApplyKannadaRules(m_strPhoneticData);
	if(m_strPhoneticData.IsEmpty())
		AfxMessageBox("Field is blank");
	else
	{
		CDoc doc;
		doc.SizeOfSentance=0;
		doc.Path=m_strActualPath;
		doc.m_strKannadaData=m_strPhoneticData;
		TRACE("\n In Speak '%s'",doc.m_strKannadaData); 
		doc.KannadaSynthesize();
	}
	EndWaitCursor();
	
}

void CVaachakaDlg::OnRepeat() 
{
	BeginWaitCursor();
	CDoc doc;
	doc.Path=m_strActualPath;
	doc.PlaySou();
	EndWaitCursor();
}

CString CVaachakaDlg::ConvertToPhonetic()
{
	//m_strPhoneticData=m_strKannada;
	CString test;
	test.GetBufferSetLength(100000);
	int kan_length=m_strKannada.GetLength();
	int k=0;
	char temparr[100];
	int j;
	int t=0;
	char temp1,temp2;
	/*for(int i=0;i<m_strKannada.GetLength();i++)
		TRACE("\n m_strKannada = %d",(unsigned char)m_strKannada.GetAt(i));*/
	for(int i=0;i<m_strKannada.GetLength();i++)
	{
		switch(m_strKannada[i])
		{
			case _TCHAR(67): test.SetAt(k,'a');
							 k++;
							break;
			case _TCHAR(68): test.SetAt(k,'a');
							 k++;
							 test.SetAt(k,'a');
							 k++;
							break;
			case _TCHAR(69): test.SetAt(k,'i');
								k++;
							break;
			case _TCHAR(70): test.SetAt(k,'i');
							 k++;
							 test.SetAt(k,'i');
							 k++;
							break;
			case _TCHAR(71): test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(72): test.SetAt(k,'u');
							 k++;
							 test.SetAt(k,'u');
							 k++;
							break;
			case _TCHAR(73): test.SetAt(k,'r');//Handle x2
							 k++;
							 if((i+1 < m_strKannada.GetLength()) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196))
							 {
								 test.SetAt(k,'u');
								 k++;
								 i++;
								 
							 }
							 else if((i+1 < m_strKannada.GetLength()) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198))
							 {
								 test.SetAt(k,'u');
								 k++;
								 i++;
								 
							 }
							 break;
			case _TCHAR(74): test.SetAt(k,'e');
							 k++;
							break;
			case _TCHAR(75): test.SetAt(k,'e');
							 k++;
							 test.SetAt(k,'e');
							 k++;
							break;
			case _TCHAR(76): test.SetAt(k,'a');
							 k++;
							 test.SetAt(k,'i');
							 k++;
							break;
			case _TCHAR(77): test.SetAt(k,'o');
							 k++;
							break;
			case _TCHAR(78): test.SetAt(k,'o');
							 k++;
							 test.SetAt(k,'o');
							 k++;
							break;
			case _TCHAR(79): test.SetAt(k,'a');
							 k++;
							 test.SetAt(k,'u');
							 k++;
							break;
			case _TCHAR(80):test.SetAt(k,'k');
							k++;
							break;
			case _TCHAR(81):test.SetAt(k,'k');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(82):test.SetAt(k,'k');
							k++;
							test.SetAt(k,'1');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							break;
			case _TCHAR(83):test.SetAt(k,'k');
							k++;
							test.SetAt(k,'1');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239) ))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							break;
			case _TCHAR(84):test.SetAt(k,'k');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(85):test.SetAt(k,'g');
							k++;
							break;
			case _TCHAR(86):test.SetAt(k,'g');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(87):test.SetAt(k,'g');
							k++;
							test.SetAt(k,'1');
							k++;
							break;
			case _TCHAR(88):test.SetAt(k,'g');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(89):test.SetAt(k,'x');
							k++;
							break;
			case _TCHAR(90):test.SetAt(k,'c');
							k++;
							test.SetAt(k,'h');
							k++;
							break;
			case _TCHAR(97):test.SetAt(k,'c');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(98):test.SetAt(k,'c');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'1');
							k++;
							break;
			case _TCHAR(99):test.SetAt(k,'c');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(100):test.SetAt(k,'j');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							break;
			case _TCHAR(101):test.SetAt(k,'j');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							break;
			case _TCHAR(102):test.SetAt(k,'j');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(103):if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(192) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(104) && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(105))
							 {
								test.SetAt(k,'j');
								 k++;
								 test.SetAt(k,'1');
								 k++;
								 i=i+3;
							 }
							else if(i+3 < kan_length && (_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(192) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(104) && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(196))) 
							 {
								 test.SetAt(k,'j');
								 k++;
								 test.SetAt(k,'1');
								 k++;
								 i=i+3;
								 if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196))
								 {
									 test.SetAt(k,'u');
									 k++;
									 i++;
								 }
								 else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198))
								 {
									 test.SetAt(k,'u');
									 k++;
									 test.SetAt(k,'u');
									 k++;
									 i++;
								 }
								 else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200))
								 {
									 test.SetAt(k,'r');//handle x2
									 k++;
									 test.SetAt(k,'u');
									 k++;
									 i++;
								 }
								 else
								 {
									if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
									{
									}
									else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
									{
									} 
									else
									{
										test.SetAt(k,'a');
										k++;
									}
								 }
								 
							 }
							else if(i+3 < kan_length && (_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(104) && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(196))) 
							{
								test.SetAt(k,'j');
								 k++;
								 test.SetAt(k,'1');
								 k++;
								 i=i+3;
								 if(i+1 >= kan_length)
								 {
									test.SetAt(k,'e');
									k++;
								}
								else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{	
									test.SetAt(k,'e');
									k++;
									test.SetAt(k,'e');
									k++;
									i++;
								}
								else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(202))
								{
									test.SetAt(k,'a');
									k++;
									test.SetAt(k,'i');
									k++;
									i++;
								}
								
								else
								{
									if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(202))
									{
									}
									else if(i+5 < kan_length && _TCHAR(m_strKannada.GetAt(i+5)) == _TCHAR(202))
									{
									}
									else
									{
										test.SetAt(k,'e');
										k++;
									}
								}
								 
							}
							else if(i+3 < kan_length && (_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(104) && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(198))) 
							{
								test.SetAt(k,'j');
								 k++;
								 test.SetAt(k,'1');
								 k++;
								 i=i+3;
								 if(i+1 >= kan_length)
								 {

									test.SetAt(k,'o');
									k++;
								 }
								 else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								 {
									 test.SetAt(k,'o');
									 k++;
									 test.SetAt(k,'o');
									 k++;
									 i++;
								 }
								 else
								 {
									test.SetAt(k,'o');
									k++;
								 }

							}
							else //if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(192))// && !(_TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(104)))
							{
								test.SetAt(k,'r');
								k++;
								
							}
								break;
			case _TCHAR(106):if(i+2 < kan_length && (_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(104) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(196)))
							 {
								 test.SetAt(k,'j');
								 k++;
								 test.SetAt(k,'1');
								 k++;
								 test.SetAt(k,'i');
								 k++;
								 i=i+2;
								 if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								 {
									 test.SetAt(k,'i');
									 k++;
									 i++;
								 }
							 }
							else if(i < kan_length)// && (_TCHAR(m_strKannada.GetAt(i+1)) != _TCHAR(104)) )
							{
								test.SetAt(k,'r');
								k++;
								test.SetAt(k,'i');
								k++;
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'i');
									k++;
									i++;
								}
							}
							break;
			case _TCHAR(107):test.SetAt(k,'r');//Handle x2
							 k++;
							 test.SetAt(k,'u');
							 k++;
							 break;
			case _TCHAR(108):test.SetAt(k,'t');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							break;
			case _TCHAR(109):test.SetAt(k,'t');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248)|| _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							break;
			case _TCHAR(110):test.SetAt(k,'t');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(111):test.SetAt(k,'t');
							k++;
							test.SetAt(k,'1');
							k++;

							break;
			case _TCHAR(112):test.SetAt(k,'t');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(113):test.SetAt(k,'d');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(115))
							{
								test.SetAt(k,'1');
								k++;
								i++;
							}

							break;
			case _TCHAR(114):test.SetAt(k,'d');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(252))
							{
								test.SetAt(k,'1');
								k++;
								i++;
							}
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			
			case _TCHAR(116):test.SetAt(k,'n');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(194))
							{
								test.SetAt(k,'i');
								k++;
								i++;
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'i');
									k++;
									i++;
								}
							}
							
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							else if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							break;
			case _TCHAR(117):test.SetAt(k,'n');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							break;
			case _TCHAR(118):test.SetAt(k,'t');
							k++;
							test.SetAt(k,'h');
							k++;
							break;

			case _TCHAR(119):test.SetAt(k,'t');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(120):test.SetAt(k,'t');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'1');
							k++;
							break;

			case _TCHAR(121):test.SetAt(k,'t');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(122):test.SetAt(k,'d');
							k++;
							test.SetAt(k,'h');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(115))
							{
								test.SetAt(k,'1');
								k++;
								i++;
							}
							break;

			case _TCHAR(162):test.SetAt(k,'d');
							k++;
							test.SetAt(k,'h');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(252))
							{
								test.SetAt(k,'1');
								k++;
								i++;
							}
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(163):test.SetAt(k,'n');
							k++;
							test.SetAt(k,'1');
							k++;
							break;

			case _TCHAR(164):test.SetAt(k,'n');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(165):test.SetAt(k,'p');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(115))
							{
								test.SetAt(k,'1');
								k++;
								i++;
							}
							break;
			case _TCHAR(166):test.SetAt(k,'p');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(252))
							{
								test.SetAt(k,'1');
								k++;
								i++;
							}
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(167):test.SetAt(k,'b');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
							}
							
							break;
			case _TCHAR(168):if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(115))
							 {
								test.SetAt(k,'b');
								k++;
								test.SetAt(k,'1');
								k++;
								i++;
							 }
							else
							{
								test.SetAt(k,'b');
								k++;
								if(i+1 >= kan_length)
								{
									test.SetAt(k,'a');
									k++;
								}
								else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
								{
									if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
									{
									}
									else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
									{
									} 
									else
									{
										test.SetAt(k,'a');
										k++;
									}
								}
							}
							
							break;
			case _TCHAR(169):test.SetAt(k,'b');
							k++;
							if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(252))
							{
								test.SetAt(k,'1');
								k++;
								i++;
							}
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(170):if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(192) && (_TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(105)))
							{
								test.SetAt(k,'m');
								k++;
								i=i+2;
								if(i+1 >= kan_length)
								{
									test.SetAt(k,'a');
									k++;
								 }
								else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
								{
									if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
									{
									}
									else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
									{
									} 
									else
									{
										test.SetAt(k,'a');
										k++;
									}
								}
								else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203))
								{
									test.SetAt(k,'a');
									k++;
									test.SetAt(k,'u');
									k++;
									i++;
								}
							}
							else if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(196))
							{
								test.SetAt(k,'m');
								k++;
								i=i+2;
								if(i+1 >= kan_length)
								{
									test.SetAt(k,'e');
									k++;
								}
								else if(k+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'e');
									k++;
									test.SetAt(k,'e');
									k++;
									i++;
								}
								else if(k+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(202))
								{
									test.SetAt(k,'a');
									k++;
									test.SetAt(k,'i');
									k++;
									i++;
								}
								else
								{
									if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(202))
									{
									}
									else if(i+5 < kan_length && _TCHAR(m_strKannada.GetAt(i+5)) == _TCHAR(202))
									{
									}
									else
									{
										test.SetAt(k,'e');
										k++;
									}
								}

							}
							else if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(198))
							{
								test.SetAt(k,'m');
								k++;
								i=i+2;
								if(i+1 >= kan_length)
								{
									test.SetAt(k,'o');
									k++;
								}
								else if(k+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'o');
									k++;
									test.SetAt(k,'o');
									k++;
									i++;
								}
								else
								{
									test.SetAt(k,'o');
									k++;
								}
							}
							else if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(199) )
							{
								test.SetAt(k,'v');
									k++;
								i=i+2;
								if(i+1 >= kan_length)
								{
									test.SetAt(k,'o');
									k++;
								}
								else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'o');
									k++;
									test.SetAt(k,'o');
									k++;
									i++;
								}
								else
								{
									test.SetAt(k,'o');
									k++;
								}
							}
							else 
							 {
							
								 test.SetAt(k,'v');
									k++;
							 }
							break;
			case _TCHAR(171):if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196))
							 {
								 test.SetAt(k,'m');
								 k++;
								 test.SetAt(k,'i');
								 k++;
								 i++;
								 if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								 {
									 test.SetAt(k,'i');
									 k++;
									 i++;
								 }
							 }
							else
							{
								test.SetAt(k,'v');
								k++;
								test.SetAt(k,'i');
								k++;
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								 {
									 test.SetAt(k,'i');
								
									 k++;
									 i++;
								 }

							}
							break;
			case _TCHAR(65):if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(105) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(192) && (_TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(105)))
							{
								test.SetAt(k,'y');
								k++;
								i=i+3;
								if(i+1 >= kan_length)
								{
									 test.SetAt(k,'a');
									 k++;
								}
								else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
								{
									if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
									{
									}
									else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
									{
									} 
									else
									{
										test.SetAt(k,'a');
										k++;
									}
								}
							}
							else if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(105) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(198))
							{
								test.SetAt(k,'y');
								k++;
								i=i+3;
								if(i+1 >= kan_length)
								{
									 test.SetAt(k,'o');
									 k++;
								}
								else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'o');
									 k++;
									 test.SetAt(k,'o');
									 k++;
									 i++;
								}
								else
								{
									test.SetAt(k,'o');
									 k++;
								}
							}
							else if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(105) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(196))
							{
								test.SetAt(k,'y');
								k++;
								i=i+3;
								if(i+1 >= kan_length)
								{
									 test.SetAt(k,'e');
									 k++;
								}
								else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'e');
									 k++;
									 test.SetAt(k,'e');
									 k++;
									 i++;
								}
								else
								{
									if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(202))
									{
									}
									else if(i+5 < kan_length && _TCHAR(m_strKannada.GetAt(i+5)) == _TCHAR(202))
									{
									}
									else
									{
										test.SetAt(k,'e');
										k++;
									}
								}
							}
							else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(105) && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(201) && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(196) && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(202))
							{
								test.SetAt(k,'y');
								k++;
								test.SetAt(k,'a');
								k++;
								test.SetAt(k,'i');
								k++;
								i=i+4;

							}
							else
							{
								test.SetAt(k,'z');//For anuswara
								k++;
							}
							break;
			case _TCHAR(172):if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196))
							 {
								 test.SetAt(k,'y');
								 k++;
								 test.SetAt(k,'i');
								 k++;
								 i++;
								 if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								 {
									 test.SetAt(k,'i');
								
									 k++;
									 i++;
								 }

							 }
								break;
			case _TCHAR(174):test.SetAt(k,'l');
							k++;
							if(i+1 >= kan_length)
							{
								test.SetAt(k,'a');
								k++;
							}
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(248) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
									else
									{
										test.SetAt(k,'a');
										k++;
									}
							}
							break;
			case _TCHAR(175):test.SetAt(k,'l');
							k++;
							break;
			case _TCHAR(176):test.SetAt(k,'l');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(177):test.SetAt(k,'s');
							k++;
							test.SetAt(k,'h');
							k++;
							break;

			case _TCHAR(178):test.SetAt(k,'s');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(181):test.SetAt(k,'s');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'1');
							k++;
							break;

			case _TCHAR(182):test.SetAt(k,'s');
							k++;
							test.SetAt(k,'h');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(184):test.SetAt(k,'s');
							k++;
							break;

			case _TCHAR(185):test.SetAt(k,'s');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(186):test.SetAt(k,'h');
							k++;
							break;

			case _TCHAR(187):test.SetAt(k,'h');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(188):test.SetAt(k,'l');
							k++;
							test.SetAt(k,'1');
							k++;
							break;

			case _TCHAR(189):test.SetAt(k,'l');
							k++;
							test.SetAt(k,'1');
							k++;
							test.SetAt(k,'i');
							k++;
							if((i+1 < kan_length) && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'i');
								k++;
								i++;
							}
							break;
			case _TCHAR(192):if(i+1 >= kan_length)
							 {
								 test.SetAt(k,'a');
								 k++;
							 }
							else if(i+1 < kan_length && !(_TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(196) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(197) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(199) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(200) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(193) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(201) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(203) || _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(239)))
							{
								
								if(i+2 < kan_length && _TCHAR(m_strKannada.GetAt(i+2)) == _TCHAR(248))
								{
								}
								else if(i+4 < kan_length && _TCHAR(m_strKannada.GetAt(i+4)) == _TCHAR(248))
								{
								} 
								else
								{
									test.SetAt(k,'a');
									k++;
								}
								
								
							}
							break;
			case _TCHAR(193):test.SetAt(k,'a');
							k++;
							test.SetAt(k,'a');
							k++;
							break;
			case _TCHAR(196):test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(197):test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(198):test.SetAt(k,'u');
							k++;
							test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(199):test.SetAt(k,'u');
							k++;
							test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(200):test.SetAt(k,'r');//Handle x2
							k++;
							test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(201):if(i+1 >= kan_length)
							 {
								 test.SetAt(k,'e');
								 k++;
							 }
							else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
							{
								test.SetAt(k,'e');
								k++;
								test.SetAt(k,'e');
								k++;
								i++;
							}
							else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(202))
							{
								test.SetAt(k,'a');
								k++;
								test.SetAt(k,'i');
								k++;
								i++;
							}
							else if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(198))
							{
								test.SetAt(k,'o');
								k++;
								i++;
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,'o');
									k++;
									i++;
								}
							}
							else// 
							{
								if(i+3 < kan_length && _TCHAR(m_strKannada.GetAt(i+3)) == _TCHAR(202))
								{
								}
								else if(i+5 < kan_length && _TCHAR(m_strKannada.GetAt(i+5)) == _TCHAR(202))
								{
								}
								else
								{
									test.SetAt(k,'e');
									k++;
								}
								
							}
							break;
			case _TCHAR(202):test.SetAt(k,'a');
							k++;
							test.SetAt(k,'i');
							k++;
							break;
			case _TCHAR(203):test.SetAt(k,'a');
							k++;
							test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(204):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'k');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'k');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'k');
								k++;
							}
							break;
			case _TCHAR(205):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'k');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'k');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'k');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(206):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'g');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'g');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'g');
								k++;
							}
							break;
			case _TCHAR(207):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'g');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'g');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'g');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(208):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'x');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'x');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'x');
								k++;
							}
							break;
			case _TCHAR(209):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'c');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'c');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'c');
								k++;
								test.SetAt(k,'h');
								k++;
							}
							break;
			case _TCHAR(210):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'c');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'c');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'c');
								k++;
								test.SetAt(k,'h');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(211):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'j');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'j');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'j');
								k++;
							}
							break;
			case _TCHAR(212):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'j');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'j');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'j');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(213):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'x');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'x');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'x');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(214):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'t');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'t');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'t');
								k++;
							}
							break;
			case _TCHAR(215):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'t');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'t');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'t');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(216):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'d');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'d');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'d');
								k++;
							}
							break;
			case _TCHAR(217):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'d');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'d');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'d');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(218):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'n');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'n');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'n');
								k++;
							}
							break;
			case _TCHAR(219):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'t');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'t');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'t');
								k++;
								test.SetAt(k,'h');
								k++;
							}
							break;
			case _TCHAR(220):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'t');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'t');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'t');
								k++;
								test.SetAt(k,'h');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(221):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'d');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'d');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'d');
								k++;
								test.SetAt(k,'h');
								k++;
							}
							break;
			case _TCHAR(222):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'d');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'d');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'d');
								k++;
								test.SetAt(k,'h');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(223):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'n');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'n');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'n');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(224):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'p');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'p');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'p');
								k++;
							}
							break;
			case _TCHAR(225):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'p');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'p');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'p');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(226):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'b');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'b');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'b');
								k++;
							}
							break;
			case _TCHAR(227):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'b');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'b');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'b');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(228):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'m');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'m');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'m');
								k++;
							}
							break;
			case _TCHAR(229):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'y');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'y');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'y');
								k++;
							}
							break;
			case _TCHAR(230):
			case _TCHAR(231):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'r');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'r');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'r');
								k++;
							}
							break;
			case _TCHAR(232):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'l');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'l');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'l');
								k++;
							}
							break;
			case _TCHAR(233):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'v');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'v');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'v');
								k++;
							}
							break;
			case _TCHAR(234):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'s');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'s');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'s');
								k++;
								test.SetAt(k,'h');
								k++;
							}
							break;
			case _TCHAR(235):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'s');
									 test.SetAt(k-1,'h');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'s');
									 test.SetAt(k,'h');
									 k++;
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'s');
								k++;
								test.SetAt(k,'h');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(236):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'s');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'s');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'s');
								k++;
							}
							break;
			case _TCHAR(237):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'h');
									 test.SetAt(k-1,temp2);
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'h');
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'h');
								k++;
							}
							break;
			case _TCHAR(238):if(k-1 >=0 && (test.GetAt(k-1) == 'a'  || test.GetAt(k-1) == 'i' || test.GetAt(k-1) == 'u' || test.GetAt(k-1) == 'e' || test.GetAt(k-1) == 'o'))
							 {
								 temp1=test.GetAt(k-1);
								 //TRACE("\n temp1 = %c",temp1);
								 if(k-2 >=0 && (test.GetAt(k-2) == 'a'  || test.GetAt(k-2) == 'i' || test.GetAt(k-2) == 'u'  || test.GetAt(k-2) == 'e' || test.GetAt(k-2) == 'o'))
								 {
									 temp2=test.GetAt(k-2);
									 //TRACE("\n temp2 = %c",temp2);
									 test.SetAt(k-2,'l');
									 test.SetAt(k-1,'1');
									 test.SetAt(k,temp2);
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								 else
								 {
									 test.SetAt(k-1,'l');
									 test.SetAt(k,'1');
									 k++;
									 test.SetAt(k,temp1);
									 k++;
								 }
								if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(195))
								{
									test.SetAt(k,temp1);
									k++;
									i++;
								}
								
							 }
							else
							{
								test.SetAt(k,'l');
								k++;
								test.SetAt(k,'1');
								k++;
							}
							break;
			case _TCHAR(239):break;
			case _TCHAR(240):j=k-1;
							t=0;
							while(j >= 0)//
							{
								if(test.GetAt(j) == 'a' || test.GetAt(j) == 'i' || test.GetAt(j) == 'u' || test.GetAt(j) == 'e' || test.GetAt(j) == 'o' )
								{
									temparr[t]=test.GetAt(j);
									t++;
								}
								else
									break;
								j--;
								
							}
							while(j >= 0)//
							{
								if(!(test.GetAt(j) == 'a' || test.GetAt(j) == 'i' || test.GetAt(j) == 'u' || test.GetAt(j) == 'e' || test.GetAt(j) == 'o' ))
								{
									temparr[t]=test.GetAt(j);
									t++;
								}
								else
									break;
								j--;
								
							}
							temparr[t]='\0';
							j++;
							test.SetAt(j,'r');
							j++;
							for(t=strlen(temparr)-1;t>=0;t--)
							{
								test.SetAt(j,temparr[t]);
								j++;
							}
							k=j;
							break;
							
			case _TCHAR(248):test.SetAt(k,'r');//handle x2
							k++;
							test.SetAt(k,'u');
							k++;
							break;
			case _TCHAR(66):test.SetAt(k,'h');
							k++;
							test.SetAt(k,'a');
							k++;
			case ' ': test.SetAt(k,' ');
					   k++;
					   break;
			case _TCHAR(246):if(i+1 < kan_length && _TCHAR(m_strKannada.GetAt(i+1)) == _TCHAR(202))
							 {
							 }
							break;			
			case _TCHAR(241):
			case _TCHAR(242):
			case _TCHAR(243):
			case _TCHAR(244):
			case _TCHAR(245):
			case _TCHAR(249):
			case _TCHAR(251):
			case _TCHAR(252):break;
			case '.':test.SetAt(k,'.');
				k++;
				test.SetAt(k,' ');
				k++;
				break;
			case '?':test.SetAt(k,'?');
				k++;
				test.SetAt(k,' ');
				k++;
				break;
			case ',':test.SetAt(k,',');
				k++;
				test.SetAt(k,' ');
				k++;
				break;
			case '!':test.SetAt(k,'!');
				k++;
				test.SetAt(k,' ');
				k++;
				break;
			case '\n':test.SetAt(k,' ');
				k++;
				break;
			default: test.SetAt(k,m_strKannada.GetAt(i));
					k++;
						break;
		}
	}
	test.SetAt(k,'\0');
	//TRACE("\n test = %s",test);
	test.ReleaseBuffer();
	return test;
}

CString CVaachakaDlg::ApplyKannadaRules(CString m_strTempData)
{
	int len;
	int k=0;
	
	len=m_strPhoneticData.GetLength();
	m_strTempData.GetBufferSetLength(len+100);
	for(int i=0;i<len;i++)
	{
		if(m_strPhoneticData.GetAt(i) == 'z')
		{
			if(i+1 < len && (m_strPhoneticData.GetAt(i+1) == 'k' || m_strPhoneticData.GetAt(i+1) == 'c' || m_strPhoneticData.GetAt(i+1) == 't' || m_strPhoneticData.GetAt(i+1) == 'g' || m_strPhoneticData.GetAt(i+1) == 'j' || m_strPhoneticData.GetAt(i+1) == 'd' ))
			{
				m_strTempData.SetAt(k,'n');
				k++;
				m_strTempData.SetAt(k,'1');
				k++;
			}
			else
			{
				m_strTempData.SetAt(k,'m');
				k++;
			}
		}
		else
		{
			m_strTempData.SetAt(k,m_strPhoneticData.GetAt(i));
			k++;
		}
	}
	m_strTempData.SetAt(k,'\0');
	//TRACE("\n m_strTempData = %s",m_strTempData);

	return m_strTempData;
}

void CVaachakaDlg::OnFileSpeak() 
{
	BeginWaitCursor();
	UpdateData(TRUE);
	//TRACE("\n m_strKannada = %s",m_strKannada);
	m_strPhoneticData = ConvertToPhonetic();
	TRACE("\n In Applying Rules ");
	m_strPhoneticData = ApplyKannadaRules(m_strPhoneticData);
	if(m_strPhoneticData.IsEmpty())
		AfxMessageBox("Field is blank");
	else
	{
		CDoc doc;
		doc.SizeOfSentance=0;
		doc.Path=m_strActualPath;
		doc.m_strKannadaData=m_strPhoneticData;
		TRACE("\n In Speak "); 
		doc.KannadaSynthesize();
	}
	EndWaitCursor();
	
}

void CVaachakaDlg::OnFileRepeat() 
{
	BeginWaitCursor();
	CDoc doc;
	doc.Path=m_strActualPath;
	doc.PlaySou();
	EndWaitCursor();	
}

void CVaachakaDlg::OnFileExit() 
{
	exit(1);
	
}

CString CVaachakaDlg::ConvertToNumbers()
{
	int length = m_strPhoneticData.GetLength();
//	TRACE("\n phonetic length = %d, Phonetic in Convert = %s",length,m_strPhoneticData);
	char *m_strInput,*m_strOutput,m_strTemp[20];
	char *m_strInter;
	m_strInput = new char [length];
	m_strOutput = new char [length+1000];
	m_strInter = new char [500];
	strcpy(m_strInput,m_strPhoneticData);

	int i=0,k=0,j=0;
	while(i<length)
	{
		while(!(m_strInput[i] == '0' || m_strInput[i] == '1' || m_strInput[i] == '2' || m_strInput[i] == '3' || m_strInput[i] == '4' || m_strInput[i] == '5' || m_strInput[i] == '6' || m_strInput[i] == '7' || m_strInput[i] == '8' || m_strInput[i] == '9' ))
		{
			if((m_strInput[i] == 'k'  || m_strInput[i] == 'g' || m_strInput[i] == 'h' || m_strInput[i] == 'j' || m_strInput[i] == 'x' || m_strInput[i] == 't' || m_strInput[i] == 'd' || m_strInput[i] == 'n' || m_strInput[i] == 'p' || m_strInput[i] == 'b' || m_strInput[i] == 'l'))
			{
				
					m_strOutput[k] = m_strInput[i];
					k++;
					i++;
					if(i>=length)
						break;
					if(i < length && m_strInput[i] == '1')// || m_strInput[i+1] == '1' || m_strInput[i+1] == '2' || m_strInput[i+1] == '3' || m_strInput[i+1] == '4' || m_strInput[i+1] == '5' || m_strInput[i+1] == '6' || m_strInput[i+1] == '7' || m_strInput[i+1] == '8' || m_strInput[i] == '9+1' ))
					{
						m_strOutput[k]=m_strInput[i];
						k++;
						i++;
						
						if(i>=length)
							break;
					}
			}
			else
			{
				m_strOutput[k] = m_strInput[i];
				i++;
				if(i>=length)
				break;
				k++;
			}
			
		}

		if(m_strInput[i] == '0' || m_strInput[i] == '1' || m_strInput[i] == '2' || m_strInput[i] == '3' || m_strInput[i] == '4' || m_strInput[i] == '5' || m_strInput[i] == '6' || m_strInput[i] == '7' || m_strInput[i] == '8' || m_strInput[i] == '9' )
		{
			j=0;
			/*if(i > 0 && (m_strInput[i-1] == 'k'  || m_strInput[i-1] == 'g' || m_strInput[i-1] == 'h' || m_strInput[i-1] == 'j' || m_strInput[i-1] == 'x' || m_strInput[i-1] == 't' || m_strInput[i-1] == 'd' || m_strInput[i-1] == 'n' || m_strInput[i-1] == 'p' || m_strInput[i-1] == 'b' || m_strInput[i-1] == 'l'))
			{
				break;
			}*/
			while(m_strInput[i] == '0' || m_strInput[i] == '1' || m_strInput[i] == '2' || m_strInput[i] == '3' || m_strInput[i] == '4' || m_strInput[i] == '5' || m_strInput[i] == '6' || m_strInput[i] == '7' || m_strInput[i] == '8' || m_strInput[i] == '9' )
			{
				m_strTemp[j]=m_strInput[i];
				j++;
				i++;
				if(i>=length)
				break;

			}
			m_strTemp[j]='\0';
			m_strInter=Convert(&m_strTemp[0]);
			m_strOutput[k]='\0';
			strcat(m_strOutput,m_strInter);
			k=strlen(m_strOutput);
		}


	}
	m_strOutput[++k]='\0';
	//TRACE("\n m_strOutput = %s",m_strOutput);
	return m_strOutput;
}

char* CVaachakaDlg::Convert(char m_strTemp[20])
{
	//AfxMessageBox("In convert");
	char *m_strConvert;
	m_strConvert= new char [200];
	int FlagR=0,FlagThousand=0,FlagOne=0,FlagLakh=0,FlagTwo=0;
	int FlagThree=0,FlagCrore=0,FlagFour=0,FlagFive=0,FlagHunCrore=0,FlagThousCrore=0,FlagThou=0,FlagFR=0;
	m_strConvert[0]='\0';
	int l = strlen(m_strTemp);
	//TRACE("\n m_strTemp = %s",m_strTemp);
	//cout<<"\n l = "<<l;
	int count=l;
	while(count > 0)
	{

		if(count == 1 || FlagOne == 1 || FlagTwo == 1 || FlagThree == 1 || FlagFive == 1)
		{
			char c=m_strTemp[l-count];
			switch(c)
			{
				case '0' : strcat(m_strConvert,"son1n1e ");
					break;
				case '1' :strcat(m_strConvert,"on1dhu ");
						break;
				case '2' :strcat(m_strConvert,"eradu ");
						break;
				case '3' : strcat(m_strConvert,"muuru ");
						break;
				case '4' : strcat(m_strConvert,"n1aalakku ");
						break;
				case '5' : strcat(m_strConvert,"aidhu ");
						break;
				case '6' : strcat(m_strConvert,"aaru ");
						break;
				case '7' : strcat(m_strConvert,"eel1u ");
						break;
				case '8' : strcat(m_strConvert,"entu ");
						break;
				case '9' : strcat(m_strConvert,"ombaththu ");
						break;
				default : break;
			}
			count--;
			if(FlagOne == 1)
			{
					if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0')
					{
						strcat(m_strConvert,"saavira ");
						count=count-3;
					}
					else
						strcat(m_strConvert,"saaviradha ");
					FlagThousand = 0;
					FlagOne=0;
			}
			else if(FlagTwo == 1)
			 {
				if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0')
				{
				       strcat(m_strConvert,"laksha ");
					count=count-5;
				}
				else
					strcat(m_strConvert,"lakshadha ");
				FlagLakh = 0;
				FlagTwo=0;
			}
			else if(FlagThree == 1)
			 {
				if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0')
				{
				       strcat(m_strConvert,"kooti ");
					count=count-7;
				}
				else
					strcat(m_strConvert,"kootiya ");
				FlagThree = 0;
				FlagCrore=0;
			}
			else if(FlagFive == 1)
			 {
				if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0')
				{
				       strcat(m_strConvert,"kooti ");
					count=count-8;
				}
				else
					strcat(m_strConvert,"kootiya ");
				FlagFive = 0;
				FlagThousCrore=0;
			}

		}
		else if(count == 2 || FlagThousand == 1 || FlagLakh == 1 || FlagCrore == 1 || FlagFour == 1)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else if(m_strTemp[l-count]  == '1')
			{
				switch(m_strTemp[l-count+1])
				{
					case '0':strcat(m_strConvert,"haththu ");
						break;
					case '1': strcat(m_strConvert,"han1n1on1dhu ");
						break;
					case '2': strcat(m_strConvert,"han1n1eradu ");
						break;
					case '3': strcat(m_strConvert,"hadhimuuru ");
						break;
					case '4': strcat(m_strConvert,"hadhin1aalakku ");
						break;
					case '5': strcat(m_strConvert,"hadhin1aidhu ");
						break;
					case '6': strcat(m_strConvert,"hadhin1aaru ");
						break;
					case '7': strcat(m_strConvert,"hadhin1eel1u ");
						break;
					case '8': strcat(m_strConvert,"hadhin1en1tu ");
						break;
					case '9': strcat(m_strConvert,"hathombaththu ");
						break;
					default: break;
				}
				count=count-2;
			}
			else if(m_strTemp[l-count] == '2' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"ipaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '2' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"ipaththa ");
				if(FlagThousand == 1)
				      FlagOne=1;
				else if(FlagLakh == 1)
					FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;

			}
			else if(m_strTemp[l-count] == '3' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"muuvaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '3' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"muuvaththa ");
				if(FlagThousand == 1)
					FlagOne=1;
				else if(FlagLakh == 1)
				      FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;
			}
			else if(m_strTemp[l-count] == '4' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"n1alavaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '4' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"n1alavaththa ");
				if(FlagThousand == 1)
					FlagOne=1;
				else if(FlagLakh == 1)
				      FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;
			}
			else if(m_strTemp[l-count] == '5' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"aivaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '5' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"aivaththa ");
				if(FlagThousand == 1)
					FlagOne=1;
				else if(FlagLakh == 1)
				      FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;
			}
			else if(m_strTemp[l-count] == '6' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"aravaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '6' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"aravaththa ");
				if(FlagThousand == 1)
					FlagOne=1;
				else if(FlagLakh == 1)
				      FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;
			}
			else if(m_strTemp[l-count] == '7' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"eppaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '7' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"eppaththa ");
				if(FlagThousand == 1)
					FlagOne=1;
				else if(FlagLakh == 1)
				      FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;
			}
			else if(m_strTemp[l-count] == '8' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"embaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '8' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"embaththa ");
				if(FlagThousand == 1)
				FlagOne=1;
				else if(FlagLakh == 1)
				      FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;
			}
			else if(m_strTemp[l-count] == '9' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"thombaththu ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '9' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"thombaththa ");
				if(FlagThousand == 1)
					FlagOne=1;
				else if(FlagLakh == 1)
				      FlagTwo=1;
				else if(FlagCrore == 1)
					FlagThree = 1;
				else if(FlagFour == 1)
					FlagFive = 1;
				count=count-1;
			}
			if(FlagThousand == 1)
			{
					if(!(FlagOne == 1))
					{
						if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0')
						{
							strcat(m_strConvert,"saavira ");
							count=count-3;
						}
						else
							strcat(m_strConvert,"saaviradha ");
					}
				FlagThousand=0;
			 }
			 if(FlagLakh == 1)
			{
					if(!(FlagTwo == 1))
					{
						if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0')
						{
							strcat(m_strConvert,"laksha ");
							count=count-5;
						}
						else
							strcat(m_strConvert,"lakshadha ");
					}
					FlagLakh=0;
			 }
			 if(FlagCrore == 1)
			{
					if(!(FlagThree == 1))
					{
						if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0')
						{
							strcat(m_strConvert,"kooti ");
							count=count-7;
						}
						else
							strcat(m_strConvert,"kootiya ");
					}
					FlagCrore=0;
			 }
			 if(FlagFour == 1)
			{
				if(FlagFR == 1)
					FlagFR=0;
				else
				{
					if(!(FlagFive == 1))
					{
						if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0')
						{
							strcat(m_strConvert,"kooti ");
							count=count-7;
						}
						else
							strcat(m_strConvert,"kootiya ");
					}
				}
					FlagFour=0;
			 }

		}
		else if(count == 3 || FlagHunCrore == 1 || FlagThou == 1)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0')
			{
				/*if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");*/
				strcat(m_strConvert,"n1uuru ");
				if(FlagHunCrore == 1)
				{
					if(m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0' && m_strTemp[l-count+8] == '0' && m_strTemp[l-count+9] == '0' && m_strTemp[l-count+4] == '0')
					{
						strcat(m_strConvert,"kooti ");
						count=count-10;
					}
					else
						strcat(m_strConvert,"kootiya ");
					FlagHunCrore=0;
				}
				if(FlagThou == 1)
				{
					if(m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0' && m_strTemp[l-count+8] == '0' && m_strTemp[l-count+9] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0')
					{
						strcat(m_strConvert,"kooti ");
						count=count-11;
					}
					else
						strcat(m_strConvert,"kootiya ");
					FlagThou=0;
				}

				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && !(m_strTemp[l-count+2] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"n1uura ");
				if(FlagHunCrore == 1)
				 {
					strcat(m_strConvert,"kootiya ");
					FlagHunCrore=0;
				 }
				 if(FlagThou == 1)
				 {
					strcat(m_strConvert,"kootiya ");
					FlagThou=0;
				 }
				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && !(m_strTemp[l-count+1] == '0'))
			{
				/*if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");*/
				strcat(m_strConvert,"n1uura ");
				if(FlagHunCrore)
				{
					FlagFour=1;
					FlagHunCrore=0;
				}
				if(FlagThou)
				{
					FlagFour=1;
					FlagFR=1;
					FlagThou=0;
				}

				count=count-1;
				FlagR=0;
			}
			else if(m_strTemp[l-count] == '2')
			{
				strcat(m_strConvert,"in1");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"mun1");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,"n1aa");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"ai");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"aar ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"eel1u ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"entu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"ombaththu ");
				FlagR=1;
			}

		}
		else if(count == 4 || FlagThousCrore == 1)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0')
			{
			/*	if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");*/
				strcat(m_strConvert,"saavira ");
				if(FlagThousCrore == 1)
				{
					if(m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0' && m_strTemp[l-count+8] == '0' && m_strTemp[l-count+9] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0')
					{
						strcat(m_strConvert,"kooti ");
						count=count-11;
					}
					else
						strcat(m_strConvert,"kootiya ");
					FlagThousCrore=0;
				}
				count=count-4;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && !(m_strTemp[l-count+2] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"saaviradha ");
				if(FlagThousCrore == 1)
				 {
					strcat(m_strConvert,"kootiya ");
					FlagThousCrore=0;
				 }

				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0')
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"saaviradha ");
				if(FlagThousCrore == 1)
				 {
					strcat(m_strConvert,"kootiya ");
					FlagThousCrore=0;
				 }

				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && !(m_strTemp[l-count+1] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"saaviradha ");
				if(FlagThousCrore)
				{
					FlagThou=1;
					FlagThousCrore=0;
				}
				count=count-1;
				FlagR=0;
			}
			else if(m_strTemp[l-count] == '2')
			{
				strcat(m_strConvert,"eradu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"muuru ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,"n1aalakku ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"aidhu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"aaru ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"eel1u ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"entu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"ombaththu ");
				FlagR=1;
			}
		}
		else if(count == 5)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else
				FlagThousand = 1;
		}
		else if(count == 6)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0')
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"laksha ");
				count=count-6;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && m_strTemp[l-count+2] == '0' && (m_strTemp[l-count+3] == '0') && m_strTemp[l-count+4] == '0' && !(m_strTemp[l-count+5] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"lakshadha ");
				count=count-5;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && !(m_strTemp[l-count+4] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"lakshadha ");
				count=count-4;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && !(m_strTemp[l-count+3] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"lakshadha ");
				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && !(m_strTemp[l-count+2] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"lakshadha ");
				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && !(m_strTemp[l-count+1] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"lakshadha ");
				count=count-1;
				FlagR=0;
			}
			else if(m_strTemp[l-count] == '2')
			{
				strcat(m_strConvert,"eradu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"muuru ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,"n1aalakku ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"aidhu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"aaru ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"eel1u ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"entu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"ombaththu ");
				FlagR=1;
			}
		}
		else if(count == 7)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else
				FlagLakh = 1;
		}
		else if(count == 8)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0'  && m_strTemp[l-count+7] == '0' )
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"kooti ");
				count=count-8;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && m_strTemp[l-count+2] == '0' && (m_strTemp[l-count+3] == '0') && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0'  && m_strTemp[l-count+6] == '0' && !(m_strTemp[l-count+7] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"kootiya ");
				count=count-7;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && !(m_strTemp[l-count+6] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"kootiya ");
				count=count-6;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && !(m_strTemp[l-count+5] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"kootiya ");
				count=count-5;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && !(m_strTemp[l-count+4] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu");
				strcat(m_strConvert,"kootiya");
				count=count-4;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && !(m_strTemp[l-count+3] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"kootiya ");
				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0'  && !(m_strTemp[l-count+2] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"kootiya ");
				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1)   && !(m_strTemp[l-count+1] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"on1dhu ");
				strcat(m_strConvert,"kootiya ");
				count=count-1;
				FlagR=0;
			}

			else if(m_strTemp[l-count] == '2')
			{
				strcat(m_strConvert,"eradu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"muuru ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,"n1aalakku ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"aidhu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"aaru ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"eel1u ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"entu ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"ombaththu ");
				FlagR=1;
			}

		}
		else if(count == 9)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else
				FlagCrore = 1;
		}
		else if(count == 10)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else
				FlagHunCrore=1;
		}
		else if(count == 11)
		{
			if(m_strTemp[l-count] == '0')
				count--;
			else
				FlagThousCrore=1;
		}
		else if(count > 11)
		{

			m_strConvert='\0';
			count=count-l;
		}

		else
		{
			count=count-l;
			break;
		}

	}

	//TRACE("\nConvert = ",m_strConvert);
	return m_strConvert;
}
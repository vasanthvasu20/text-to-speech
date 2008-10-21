// VakDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vak.h"
#include "VakDlg.h"
#include "DlgProxy.h"

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
// CVakDlg dialog

IMPLEMENT_DYNAMIC(CVakDlg, CDialog);

CVakDlg::CVakDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVakDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVakDlg)
	m_strData = _T("");
	m_strUpdateData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	CFile JunkFile;
	JunkFile.Open("Junk",CFile::modeCreate,NULL);
	m_strActualPath=JunkFile.GetFilePath();

	int i=m_strActualPath.GetLength()-1;
	m_strActualPath.SetAt(i-3,'$');

}

CVakDlg::~CVakDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CVakDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVakDlg)
	DDX_Control(pDX, IDC_SPEAK, m_nSpeak);
	DDX_Control(pDX, IDC_OPTIONS, m_strOptions);
	DDX_Text(pDX, IDC_DATA, m_strData);
	DDV_MaxChars(pDX, m_strData, 100000);
	DDX_Text(pDX, IDC_UPDATEDATA, m_strUpdateData);
	DDV_MaxChars(pDX, m_strUpdateData, 100000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVakDlg, CDialog)
	//{{AFX_MSG_MAP(CVakDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SPEAK, OnSpeak)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_BN_CLICKED(IDC_OPTIONS2, OnPlayAgain)
	ON_EN_UPDATE(IDC_DATA, OnUpdateData)
	ON_BN_CLICKED(IDC_SPEAKFILE, OnSpeakfile)
	ON_COMMAND(ID_FILE_SPEAK, OnFileSpeak)
	ON_COMMAND(ID_FILE_SPEAKFILE, OnFileSpeakfile)
	ON_COMMAND(ID_FILE_REPEAT, OnFileRepeat)
	ON_COMMAND(ID_FILE_SAVEFILE, OnFileSavefile)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_SAVETEXT, OnFileSavetext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVakDlg message handlers

BOOL CVakDlg::OnInitDialog()
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
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, "About Thirukkural");//strAboutMenu);
			pSysMenu->DeleteMenu(2,MF_BYPOSITION);
			pSysMenu->DeleteMenu(3,MF_BYPOSITION);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVakDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVakDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVakDlg::OnPaint() 
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
HCURSOR CVakDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CVakDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}


BOOL CVakDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CVakDlg::OnSpeak() 
{
	BeginWaitCursor();
	UpdateData(TRUE);
	Flagnumber=0;
	TRACE("\n In Convert to Phonetic ");
	m_strConvEnglish.GetBufferSetLength(m_strEnglish.GetLength()+10000);
	m_strConvEnglish=ConvertNumbers();
	m_strConvEnglish+='\0';	
	TRACE("\n m_strConvEnglish after numbers= %s",m_strConvEnglish);
	m_strConvEnglish.ReleaseBuffer();
	TRACE(" m_strEnglish = %s",m_strConvEnglish);
	m_strPhoneticData = ConvertToPhonetic(m_strConvEnglish);
	TRACE("\n In Applying Rules ");
	m_strPhoneticData = ApplyTamilRules(m_strPhoneticData);
	if(m_strPhoneticData.IsEmpty())
		AfxMessageBox("Field is blank");
	else
	{
		CDoc doc;
		doc.SizeOfSentance=0;
		doc.Path=m_strActualPath;
		doc.m_strKannadaData=m_strPhoneticData;
		TRACE("\n In Speak ");
		doc.Flagnumber=Flagnumber;
		doc.KannadaSynthesize();
	}
	EndWaitCursor();
}

void CVakDlg::OnOptions() 
{
	exit(1);
}


void CVakDlg::OnPlayAgain() 
{
	BeginWaitCursor();
	CDoc doc;
	doc.Path=m_strActualPath;
	doc.PlaySou();
	EndWaitCursor();
}

void CVakDlg::OnUpdateData() 
{
	UpdateData(TRUE);
	m_strUpdateData=OnConvertData(m_strData);
	UpdateData(FALSE);
}

CString CVakDlg::OnConvertData(CString m_strOnConvertData)
{
	int l=strlen(m_strOnConvertData);
	m_strEnglish.GetBufferSetLength(l+500);

	int i,j=0;

	for(i=0;i<l;i++,j++)
	{

		//checking for CV where V=a 
	if(m_strOnConvertData.GetAt(i) == 'a')
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			j--;
			
		}
		else

		{
			m_strEnglish.SetAt(j,_TCHAR(220));
			
		}
	}
	//checking for CC where C=b
	else if(m_strOnConvertData.GetAt(i) == 'b')
	{
		 if(i>0 &&  ((m_strOnConvertData[i-1]) == 'b' ) )
		{
			 if(i>1 && (m_strOnConvertData[i-2] == 'b') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(233));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'b' && m_strOnConvertData[i-2] == 'b'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(233));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(233));
			 }

		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(233));
		}
		

	}
	// Checking for CV where V=c
	else if(m_strOnConvertData.GetAt(i) == 'c' && (i == 0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			_TCHAR Replace;
			if(m_strOnConvertData[i-1] == 'h')Replace=232;
			else if(m_strOnConvertData[i-1] == 'b')Replace=233;
			else if(m_strOnConvertData[i-1] == 'k')Replace=241;
			else if(m_strOnConvertData[i-1] == '[')Replace=234;
			else if(m_strOnConvertData[i-1] == ']')Replace=235;
			else if(m_strOnConvertData[i-1] == 'o')Replace=236;
			else if(m_strOnConvertData[i-1] == 'p')Replace=237;
			else if(m_strOnConvertData[i-1] == 'l')Replace=238;
			else if(m_strOnConvertData[i-1] == ';')Replace=239;
			else if(m_strOnConvertData[i-1] == 'j')Replace=240;
			else if(m_strOnConvertData[i-1] == 'k')Replace=241;
			else if(m_strOnConvertData[i-1] == '\'')Replace=242;
			else if(m_strOnConvertData[i-1] == 'm')Replace=243;
			else if(m_strOnConvertData[i-1] == 'n')Replace=244;
			else if(m_strOnConvertData[i-1] == 'v')Replace=245;
			else if(m_strOnConvertData[i-1] == '/')Replace=246;
			else if(m_strOnConvertData[i-1] == 'y')Replace=247;
			else if(m_strOnConvertData[i-1] == 'u')Replace=248;
			else if(m_strOnConvertData[i-1] == 'i')Replace=249;
			else if(m_strOnConvertData[i-1] == 'Q')Replace=250;
			else if(m_strOnConvertData[i-1] == 'W')Replace=251;
			else if(m_strOnConvertData[i-1] == 'E')Replace=252;
			else if(m_strOnConvertData[i-1] == 'R')Replace=253;
			else if(m_strOnConvertData[i-1] == 'Y')Replace=254;
			m_strEnglish.SetAt(j,Replace);
			m_strEnglish.SetAt(j-1,_TCHAR(170));
			j++;
			m_strEnglish.SetAt(j,_TCHAR(163));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(229));
		}
	}
	// Checking for CV where V=d
	else if(m_strOnConvertData.GetAt(i) == 'd' && (i == 0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		if(i>0 && ((m_strOnConvertData[i-1]) == 'h'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(176));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'b'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(177));
			j--;
		}
		else if(i>0  && ((m_strOnConvertData[i-1]) == '['))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(178));
			j--;
		}
		else if(i>0  && ((m_strOnConvertData[i-1]) == ']'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(179));
			j--;
		}
		else if(i>0  && ((m_strOnConvertData[i-1]) == 'o'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(180));
			j--;
		}
		else if(i>0  && ((m_strOnConvertData[i-1]) == 'p'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(181));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'l'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(182));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == ';'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(184));
			j--;
		}
		else if(i>0  && ((m_strOnConvertData[i-1]) == 'j'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(185));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'k'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(186));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == '\''))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(187));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'm'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(188));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'n'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(189));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'v'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(190));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == '/'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(191));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'y'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(192));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'u'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(193));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'i'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(194));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			m_strEnglish.SetAt(j,_TCHAR(167));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(224));
		}
	}

	// Checking for CV where V=q
	else if(m_strOnConvertData.GetAt(i) == 'q' && (i== 0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			m_strEnglish.SetAt(j,_TCHAR(163));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(221));
		}
	}
	//Checking for CV where V=e
	else if(m_strOnConvertData.GetAt(i) == 'e' && (i==0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		if(i>0 && ((m_strOnConvertData[i-1]) == 'h'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(195));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'b'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(196));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == '['))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(197));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == ']'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(198));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'o'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(199));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'p'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(200));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'l'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(201));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == ';'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(203));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'j'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(204));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'k'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(205));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == '\''))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(206));
			j--;
		}
		else if(i>0  && ((m_strOnConvertData[i-1]) == 'm'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(207));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'n'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(214));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'v'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(215));
			j--;
		}
		else if(i>0  && ((m_strOnConvertData[i-1]) == '/'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(216));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'y'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(217));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'u'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(218));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'i'))
		{
			m_strEnglish.SetAt(j-1,_TCHAR(219));
			j--;
		}
		else if(i>0 && ((m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			m_strEnglish.SetAt(j,_TCHAR(168));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(225));
		}
	}

	else if(m_strOnConvertData.GetAt(i) == 'f')
	{
		if(i>0 && (m_strOnConvertData[i-1] == 'a' || m_strOnConvertData[i-1] == 'q' || m_strOnConvertData[i-1] == 's' || m_strOnConvertData[i-1] == 'w' || m_strOnConvertData[i-1] == 'd' || m_strOnConvertData[i-1] == 'e' || m_strOnConvertData[i-1] == 'g' || m_strOnConvertData[i-1] == 't' || m_strOnConvertData[i-1] == 'r' || m_strOnConvertData[i-1] == 'c' || m_strOnConvertData[i-1] == 'x' || m_strOnConvertData[i-1] == 'z'))
		{
			j--;
		}
		
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(162));
		}
	}
	// Checking for CV where V=g
	else if((m_strOnConvertData.GetAt(i) == 'g') && (i== 0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			_TCHAR Replace;
			if(m_strOnConvertData[i-1] == 'h')Replace=232;
			else if(m_strOnConvertData[i-1] == 'b')Replace=233;
			else if(m_strOnConvertData[i-1] == 'k')Replace=241;
			else if(m_strOnConvertData[i-1] == '[')Replace=234;
			else if(m_strOnConvertData[i-1] == ']')Replace=235;
			else if(m_strOnConvertData[i-1] == 'o')Replace=236;
			else if(m_strOnConvertData[i-1] == 'p')Replace=237;
			else if(m_strOnConvertData[i-1] == 'l')Replace=238;
			else if(m_strOnConvertData[i-1] == ';')Replace=239;
			else if(m_strOnConvertData[i-1] == 'j')Replace=240;
			else if(m_strOnConvertData[i-1] == '\'')Replace=242;
			else if(m_strOnConvertData[i-1] == 'm')Replace=243;
			else if(m_strOnConvertData[i-1] == 'n')Replace=244;
			else if(m_strOnConvertData[i-1] == 'v')Replace=245;
			else if(m_strOnConvertData[i-1] == '/')Replace=246;
			else if(m_strOnConvertData[i-1] == 'y')Replace=247;
			else if(m_strOnConvertData[i-1] == 'u')Replace=248;
			else if(m_strOnConvertData[i-1] == 'i')Replace=249;
			else if(m_strOnConvertData[i-1] == 'Q')Replace=250;
			else if(m_strOnConvertData[i-1] == 'W')Replace=251;
			else if(m_strOnConvertData[i-1] == 'E')Replace=252;
			else if(m_strOnConvertData[i-1] == 'R')Replace=253;
			else if(m_strOnConvertData[i-1] == 'Y')Replace=254;
		m_strEnglish.SetAt(j,Replace);
		m_strEnglish.SetAt(j-1,_TCHAR(170));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(226));
		}
	}
	// Checking for CC where C=h
	else if(m_strOnConvertData.GetAt(i) == 'h')
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h'  || m_strOnConvertData[i-1] == 'b'))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'h' || m_strOnConvertData[i-2] == 'b') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(232));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'h' && m_strOnConvertData[i-2] == 'h'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(232));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(232));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(232));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'i')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(249));
		}*/
		if(i>0 &&  (m_strOnConvertData[i-1] == 'i' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'i') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(249));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'i' && m_strOnConvertData[i-2] == 'i'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(249));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(249));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(249));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'j')
	{
		if(i>0  && (m_strOnConvertData[i-1] == 'j'  || m_strOnConvertData[i-1] == 'k'))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'j' || m_strOnConvertData[i-2] == 'k') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(240));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'j' && m_strOnConvertData[i-2] == 'j'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(240));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(240));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(240));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'k')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(241));
		}*/
		if(i>0 &&  (m_strOnConvertData[i-1] == 'k' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'k') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(241));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'k' && m_strOnConvertData[i-2] == 'k'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(241));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(241));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(241));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'l')
	{
		if(i>0 && (m_strOnConvertData[i-1] == 'l' || m_strOnConvertData[i-1] == ';'))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'l' || m_strOnConvertData[i-2] == ';') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(238));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'l' && m_strOnConvertData[i-2] == 'l'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(238));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(238));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(238));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'm')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(243));
		}*/
		if(i>0 && (m_strOnConvertData[i-1]) == 'm'  )
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'm') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(243));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'm' && m_strOnConvertData[i-2] == 'm'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(243));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(243));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(243));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'n')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(244));
		}*/
		if(i>0 && (m_strOnConvertData[i-1] == 'n' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'n') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(244));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'n' && m_strOnConvertData[i-2] == 'n'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(244));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(244));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(244));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'o')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(236));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == 'o' || m_strOnConvertData[i-1] == 'p'))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'o' || m_strOnConvertData[i-2] == 'p') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(236));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'o' && m_strOnConvertData[i-2] == 'o'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(236));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(236));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(236));
		}

	
	}
	else if(m_strOnConvertData.GetAt(i) == 'p')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(237));
		}*/
		if(i>0 && (m_strOnConvertData[i-1] == 'p' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'p') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(237));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'p' && m_strOnConvertData[i-2] == 'p'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(237));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(237));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(237));
		}
	
	}
	else if(m_strOnConvertData.GetAt(i) == 'r' && (i == 0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			_TCHAR Replace;
			if(m_strOnConvertData[i-1] == 'h')Replace=232;
			else if(m_strOnConvertData[i-1] == 'b')Replace=233;
			else if(m_strOnConvertData[i-1] == 'j')Replace=240;
			else if(m_strOnConvertData[i-1] == '[')Replace=234;
			else if(m_strOnConvertData[i-1] == ']')Replace=235;
			else if(m_strOnConvertData[i-1] == 'o')Replace=236;
			else if(m_strOnConvertData[i-1] == 'p')Replace=237;
			else if(m_strOnConvertData[i-1] == 'l')Replace=238;
			else if(m_strOnConvertData[i-1] == ';')Replace=239;
			else if(m_strOnConvertData[i-1] == 'k')Replace=241;
			else if(m_strOnConvertData[i-1] == 'j')Replace=240;
			else if(m_strOnConvertData[i-1] == '\'')Replace=242;
			else if(m_strOnConvertData[i-1] == 'm')Replace=243;
			else if(m_strOnConvertData[i-1] == 'n')Replace=244;
			else if(m_strOnConvertData[i-1] == 'v')Replace=245;
			else if(m_strOnConvertData[i-1] == '/')Replace=246;
			else if(m_strOnConvertData[i-1] == 'y')Replace=247;
			else if(m_strOnConvertData[i-1] == 'u')Replace=248;
			else if(m_strOnConvertData[i-1] == 'i')Replace=249;
			else if(m_strOnConvertData[i-1] == 'Q')Replace=250;
			else if(m_strOnConvertData[i-1] == 'W')Replace=251;
			else if(m_strOnConvertData[i-1] == 'E')Replace=252;
			else if(m_strOnConvertData[i-1] == 'R')Replace=253;
			else if(m_strOnConvertData[i-1] == 'Y')Replace=254;
			m_strEnglish.SetAt(j,Replace);
			m_strEnglish.SetAt(j-1,_TCHAR(172));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(228));
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 's' && (i == 0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' ||  (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			m_strEnglish.SetAt(j,_TCHAR(164));
		}
		else if(i>0 && m_strOnConvertData[i-1] == 'o')
		{
			j--;
			m_strEnglish.SetAt(j,_TCHAR(174));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(222));
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 't' && (i == 0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			_TCHAR Replace;
			if(m_strOnConvertData[i-1] == 'h')Replace=232;
			else if(m_strOnConvertData[i-1] == 'b')Replace=233;
			else if(m_strOnConvertData[i-1] == '[')Replace=234;
			else if(m_strOnConvertData[i-1] == ']')Replace=235;
			else if(m_strOnConvertData[i-1] == 'o')Replace=236;
			else if(m_strOnConvertData[i-1] == 'p')Replace=237;
			else if(m_strOnConvertData[i-1] == 'l')Replace=238;
			else if(m_strOnConvertData[i-1] == ';')Replace=239;
			else if(m_strOnConvertData[i-1] == 'k')Replace=241;
			else if(m_strOnConvertData[i-1] == 'j')Replace=240;
			else if(m_strOnConvertData[i-1] == '\'')Replace=242;
			else if(m_strOnConvertData[i-1] == 'm')Replace=243;
			else if(m_strOnConvertData[i-1] == 'n')Replace=244;
			else if(m_strOnConvertData[i-1] == 'v')Replace=245;
			else if(m_strOnConvertData[i-1] == '/')Replace=246;
			else if(m_strOnConvertData[i-1] == 'y')Replace=247;
			else if(m_strOnConvertData[i-1] == 'u')Replace=248;
			else if(m_strOnConvertData[i-1] == 'i')Replace=249;
			else if(m_strOnConvertData[i-1] == 'Q')Replace=250;
			else if(m_strOnConvertData[i-1] == 'W')Replace=251;
			else if(m_strOnConvertData[i-1] == 'E')Replace=252;
			else if(m_strOnConvertData[i-1] == 'R')Replace=253;
			else if(m_strOnConvertData[i-1] == 'Y')Replace=254;
		m_strEnglish.SetAt(j,Replace);
		m_strEnglish.SetAt(j-1,_TCHAR(171));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(227));
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'u')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(248));
		}*/
		if(i>0  &&  ((m_strOnConvertData[i-1] == 'u' ) || m_strOnConvertData[i-1] == 'i'))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'u' || m_strOnConvertData[i-2] == 'i') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(248));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'u' && m_strOnConvertData[i-2] == 'u'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(248));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(248));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(248));
		}
		
	
	}
	else if(m_strOnConvertData.GetAt(i) == 'v')
	{
		/*if(i>1 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(245));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == 'v' ))
		{	
			if(i>1 && (m_strOnConvertData[i-2] == 'v') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(245));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'v' && m_strOnConvertData[i-2] == 'v'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(245));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(245));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(245));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'w' && (i==0 || (i>0 && m_strOnConvertData.GetAt(i-1) != '^')))
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			m_strEnglish.SetAt(j,_TCHAR(166));
		}
		else if(i>0 && m_strOnConvertData[i-1] == 'o')
		{
			j--;
			m_strEnglish.SetAt(j,_TCHAR(175));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(223));
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'x')// && (i>0 && m_strOnConvertData.GetAt(i-1) != '^'))
	{
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			_TCHAR Replace;
			if(m_strOnConvertData[i-1] == 'h')Replace=232;
			else if(m_strOnConvertData[i-1] == 'b')Replace=233;
			else if(m_strOnConvertData[i-1] == '[')Replace=234;
			else if(m_strOnConvertData[i-1] == ']')Replace=235;
			else if(m_strOnConvertData[i-1] == 'o')Replace=236;
			else if(m_strOnConvertData[i-1] == 'p')Replace=237;
			else if(m_strOnConvertData[i-1] == 'l')Replace=238;
			else if(m_strOnConvertData[i-1] == ';')Replace=239;
			else if(m_strOnConvertData[i-1] == 'j')Replace=240;
			else if(m_strOnConvertData[i-1] == 'k')Replace=241;
			else if(m_strOnConvertData[i-1] == '\'')Replace=242;
			else if(m_strOnConvertData[i-1] == 'm')Replace=243;
			else if(m_strOnConvertData[i-1] == 'n')Replace=244;
			else if(m_strOnConvertData[i-1] == 'v')Replace=245;
			else if(m_strOnConvertData[i-1] == '/')Replace=246;
			else if(m_strOnConvertData[i-1] == 'y')Replace=247;
			else if(m_strOnConvertData[i-1] == 'u')Replace=248;
			else if(m_strOnConvertData[i-1] == 'i')Replace=249;
			else if(m_strOnConvertData[i-1] == 'Q')Replace=250;
			else if(m_strOnConvertData[i-1] == 'W')Replace=251;
			else if(m_strOnConvertData[i-1] == 'E')Replace=252;
			else if(m_strOnConvertData[i-1] == 'R')Replace=253;
			else if(m_strOnConvertData[i-1] == 'Y')Replace=254;
			m_strEnglish.SetAt(j,Replace);
			m_strEnglish.SetAt(j-1,_TCHAR(171));
			j++;
			m_strEnglish.SetAt(j,_TCHAR(163));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(230));
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'y')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(247));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == 'y' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'y') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(247));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'y' && m_strOnConvertData[i-2] == 'y'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(247));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(247));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(247));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'z')// && (i>0 && m_strOnConvertData.GetAt(i-1) != '^'))
	{
		
		if(i>0 &&  (m_strOnConvertData[i-1] == 'h' || (m_strOnConvertData[i-1]) == 'b' || (m_strOnConvertData[i-1]) == '[' || (m_strOnConvertData[i-1]) == ']' || (m_strOnConvertData[i-1]) == 'o' || (m_strOnConvertData[i-1]) == 'p' || (m_strOnConvertData[i-1]) == 'l' || (m_strOnConvertData[i-1]) == ';' || (m_strOnConvertData[i-1]) == 'j' || (m_strOnConvertData[i-1]) == 'k' || (m_strOnConvertData[i-1]) == '\'' || (m_strOnConvertData[i-1]) == 'm' || (m_strOnConvertData[i-1]) == 'n' || (m_strOnConvertData[i-1]) == 'v' || (m_strOnConvertData[i-1]) == '/' || (m_strOnConvertData[i-1]) == 'y' || (m_strOnConvertData[i-1]) == 'u' || (m_strOnConvertData[i-1]) == 'i' || (m_strOnConvertData[i-1]) == 'Q' || (m_strOnConvertData[i-1]) == 'W' || (m_strOnConvertData[i-1]) == 'E' || (m_strOnConvertData[i-1]) == 'R' || (m_strOnConvertData[i-1]) == 'T'))
		{
			_TCHAR Replace;
			if(m_strOnConvertData[i-1] == 'h')Replace=232;
			else if(m_strOnConvertData[i-1] == 'b')Replace=233;
			else if(m_strOnConvertData[i-1] == '[')Replace=234;
			else if(m_strOnConvertData[i-1] == ']')Replace=235;
			else if(m_strOnConvertData[i-1] == 'o')Replace=236;
			else if(m_strOnConvertData[i-1] == 'p')Replace=237;
			else if(m_strOnConvertData[i-1] == 'l')Replace=238;
			else if(m_strOnConvertData[i-1] == ';')Replace=239;
			else if(m_strOnConvertData[i-1] == 'j')Replace=240;
			else if(m_strOnConvertData[i-1] == 'k')Replace=241;
			else if(m_strOnConvertData[i-1] == '\'')Replace=242;
			else if(m_strOnConvertData[i-1] == 'm')Replace=243;
			else if(m_strOnConvertData[i-1] == 'n')Replace=244;
			else if(m_strOnConvertData[i-1] == 'v')Replace=245;
			else if(m_strOnConvertData[i-1] == '/')Replace=246;
			else if(m_strOnConvertData[i-1] == 'y')Replace=247;
			else if(m_strOnConvertData[i-1] == 'u')Replace=248;
			else if(m_strOnConvertData[i-1] == 'i')Replace=249;
			else if(m_strOnConvertData[i-1] == 'Q')Replace=250;
			else if(m_strOnConvertData[i-1] == 'W')Replace=251;
			else if(m_strOnConvertData[i-1] == 'E')Replace=252;
			else if(m_strOnConvertData[i-1] == 'R')Replace=253;
			else if(m_strOnConvertData[i-1] == 'Y')Replace=254;
			m_strEnglish.SetAt(j,Replace);
			m_strEnglish.SetAt(j-1,_TCHAR(170));
			j++;
			m_strEnglish.SetAt(j,_TCHAR(247));
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(229));
			j++;
			m_strEnglish.SetAt(j,_TCHAR(247));
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'A')
	{
		j--;	
	}
	else if(m_strOnConvertData.GetAt(i) == 'B')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'C')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'D')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'E')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(252));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == 'E' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'E') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(252));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'E' && m_strOnConvertData[i-2] == 'E'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(252));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(252));
			 }
		}
		else {
			m_strEnglish.SetAt(j,_TCHAR(252));
		}
	
	}
	else if(m_strOnConvertData.GetAt(i) == 'F')
	{
		m_strEnglish.SetAt(j,_TCHAR(231));
	}
	else if(m_strOnConvertData.GetAt(i) == 'G')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'H')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'I')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'J')
		j--;

	else if(m_strOnConvertData.GetAt(i) == 'K')
	{
		m_strEnglish.SetAt(j,_TCHAR(34));
	}
	else if(m_strOnConvertData.GetAt(i) == 'L')
	{
		m_strEnglish.SetAt(j,_TCHAR(58));
	}
	else if(m_strOnConvertData.GetAt(i) == 'M')
	{
		m_strEnglish.SetAt(j,_TCHAR(47));
	}
	else if(m_strOnConvertData.GetAt(i) == 'N')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'O')
	{
		m_strEnglish.SetAt(j,_TCHAR(91));
	}
	else if(m_strOnConvertData.GetAt(i) == 'P')
	{
		m_strEnglish.SetAt(j,_TCHAR(93));
	}
	else if(m_strOnConvertData.GetAt(i) == 'Q')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(250));
		}*/
		 if(i>0  && (m_strOnConvertData[i-1] == 'Q' ))
		{
			 if(i>1 && (m_strOnConvertData[i-2] == 'Q') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(250));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'Q' && m_strOnConvertData[i-2] == 'Q'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(250));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(250));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(250));
		}
	
	}
	else if(m_strOnConvertData.GetAt(i) == 'R')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(253));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == 'R' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'R') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(253));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'R' && m_strOnConvertData[i-2] == 'R'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(253));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(253));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(253));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'S')
	j--;
	else if(m_strOnConvertData.GetAt(i) == 'T')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(254));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == 'T' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'T') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(254));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'T' && m_strOnConvertData[i-2] == 'T'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(254));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(254));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(254));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'U')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'V')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'W')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(251));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == 'W' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == 'W') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(251));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == 'W' && m_strOnConvertData[i-2] == 'W'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(251));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(251));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(251));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == 'X')
		j--;
	else if(m_strOnConvertData.GetAt(i) == 'Y')
	{
		m_strEnglish.SetAt(j,_TCHAR(255));
	}
	else if(m_strOnConvertData.GetAt(i) == 'Z')
		j--;
	else if(m_strOnConvertData.GetAt(i) == '[')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(234));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == '[' || (m_strOnConvertData[i-1]) == ']' ))
		{	
			if(i>1 && (m_strOnConvertData[i-2] == '[' || m_strOnConvertData[i-2] == ']') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(234));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == '[' && m_strOnConvertData[i-2] == '['))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(234));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(234));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(234));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == ']')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(235));
		}*/
	 if(i>0  && (m_strOnConvertData[i-1] == ']' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == ']') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(235));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == ']' && m_strOnConvertData[i-2] == ']'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(235));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(235));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(235));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == ';')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(239));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == ';' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == ';') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(239));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == ';' && m_strOnConvertData[i-2] == ';'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(239));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(239));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(239));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == ':')
	{
		m_strEnglish.SetAt(j,_TCHAR(59));
	}
	else if(m_strOnConvertData.GetAt(i) == '\'')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(242));
		}*/
		if(i>0 &&  (m_strOnConvertData[i-1] == '\'' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == '\'') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(242));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == '\'' && m_strOnConvertData[i-2] == '\''))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(242));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(242));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(242));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == '"')
	{
		m_strEnglish.SetAt(j,_TCHAR(44));
	}
	else if(m_strOnConvertData.GetAt(i) == '/')
	{
		/*if(i>0 && _TCHAR(m_strEnglish[i-1]) == _TCHAR(162))
		{
			m_strEnglish.SetAt(j,_TCHAR(246));
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == '/' ))
		{
			if(i>1 && (m_strOnConvertData[i-2] == '/') && _TCHAR(m_strEnglish[j-2]) == _TCHAR(162))// && (i > 2 && m_strOnConvertData[i-3] != 'b'))
			 {
				 	 m_strEnglish.SetAt(j,_TCHAR(246));
			}
			 else if(i > 2 && (m_strOnConvertData[i-3] == '/' && m_strOnConvertData[i-2] == '/'))
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(246));
			 }
			 else 
			 {
				 m_strEnglish.SetAt(j,_TCHAR(162));
				j++;
				m_strEnglish.SetAt(j,_TCHAR(246));
			 }
		}
		else
		{
			m_strEnglish.SetAt(j,_TCHAR(246));
		}
		
	}
	else if(m_strOnConvertData.GetAt(i) == '.')
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j-1,_TCHAR(165));
			j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'c' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(169));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'q' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(163));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 's' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(164));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'w' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(166));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'd' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(167));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'e' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(168));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'g' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(170));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 't' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(171));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == 'r' && (i>0 && m_strOnConvertData.GetAt(i-1) == '^'))
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(172));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}

	else if(m_strOnConvertData.GetAt(i) == '^')
	{
		/*if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
			//	j--;
		}
		else {
			j--;
			//m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}*/
		if(i>0  && (m_strOnConvertData[i-1] == '^' ))
		{	
			if(i > 4 && (m_strOnConvertData[i-5] == '^' && m_strOnConvertData[i-4] == '^' && m_strOnConvertData[i-3] == '^' && m_strOnConvertData[i-2] == '^'))
			 {
				 m_strEnglish.SetAt(j,m_strOnConvertData[i]);
			}
			else if(i > 3 && (m_strOnConvertData[i-4] == '^' && m_strOnConvertData[i-3] == '^' && m_strOnConvertData[i-2] == '^'))
			 {
				 j--;
			}
			else if(i > 2 && (m_strOnConvertData[i-3] == '^' && m_strOnConvertData[i-2] == '^'))
			 {
				 m_strEnglish.SetAt(j,m_strOnConvertData[i]);
			 }
			 else if(i>1 && (m_strOnConvertData[i-2] == '^'))// && (i>2 && m_strOnConvertData[i-3] == '^')) 
			 {
				 	 j--;
			}
			 else 
			 {
				 m_strEnglish.SetAt(j,m_strOnConvertData[i]);
			 }
		}
		else
		{
			j--;
		}
	}
	else if(m_strOnConvertData.GetAt(i) == '7')
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(39));
				//j--;
		}
		else {
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == '8')
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(39));
				//j--;
		}
		else 
		{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == '9')
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(34));
			//j--;
		}
		else 
		{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else if(m_strOnConvertData.GetAt(i) == '0')
	{
		if(i>0 && m_strOnConvertData[i-1] == '^')
		{
			m_strEnglish.SetAt(j,_TCHAR(34));
			//j--;
		}
		else{
			m_strEnglish.SetAt(j,m_strOnConvertData[i]);
		}
	}
	else 
		m_strEnglish.SetAt(j,m_strOnConvertData[i]);

	}
	
	m_strEnglish.SetAt(j,'\0');
	return m_strEnglish;
	
}

CString CVakDlg::ConvertToPhonetic(CString m_strConvertingData)
{

	if(m_strConvertingData.IsEmpty())
	{
		AfxMessageBox("Field is empty");
		return m_strConvertingData;
	}
	int flag=0;
	BOOL m_bFlagBefore = 0;
	int i = 0;
	while(m_strConvertingData.GetAt(i) == ' ')
	{
		m_strConvertingData.Delete(i,1);
		//i++;
	}
	i=0;
	
	//while(m_strConvertingData.GetAt(i) != '\0')
	//	i++;
	
	int length = m_strConvertingData.GetLength();
	CString temp;
	//m_strConvertingData.GetLength();
	m_strConvertingData.GetBufferSetLength(length+5000);
//	temp.GetBufferSetLength(length+20);
	i=0;
	while(i<length)
	{	
		if(_TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(232) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(233) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(234) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(235) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(236) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(237) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(238) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(239) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(240) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(241)
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(242) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(243)
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(244) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(245) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(246) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(247) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(248) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(249) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(250) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(251) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(252) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(253) 
			|| _TCHAR(m_strConvertingData.GetAt(i)) == _TCHAR(254))
		{
			if(_TCHAR(m_strConvertingData.GetAt(i+1)) == _TCHAR(162) || _TCHAR(m_strConvertingData.GetAt(i+1)) == _TCHAR(163) || _TCHAR(m_strConvertingData.GetAt(i+1)) == _TCHAR(164) || _TCHAR(m_strConvertingData.GetAt(i+1)) == _TCHAR(166) ||  _TCHAR(m_strConvertingData.GetAt(i+1)) == _TCHAR(167) || _TCHAR(m_strConvertingData.GetAt(i+1)) == _TCHAR(168))
			{
				temp+=m_strConvertingData.GetAt(i);
				i++;
			}
			else
			{
				flag=0;
				if(i-1 >= 0)
				{
					if(_TCHAR(m_strConvertingData.GetAt(i-1)) == _TCHAR(170) || 
						_TCHAR(m_strConvertingData.GetAt(i-1)) == _TCHAR(171) ||
						_TCHAR(m_strConvertingData.GetAt(i-1)) == _TCHAR(172))
					{
						temp+=m_strConvertingData.GetAt(i);
						i++;
						flag=1;
					}
					else
						flag=0;
				}
				if(flag == 0)
				{
						temp+=m_strConvertingData.GetAt(i);
						temp+=_TCHAR(220);
						i++;
				}
			}
		}
		else
		{
			temp+=m_strConvertingData.GetAt(i);
			i++;
		}
	}

	m_strConvertingData = temp;

	length = m_strConvertingData.GetLength();
	TRACE("\nLength = %d ' ",length);
	CString m_strConvertedData;
	m_strConvertedData.GetBufferSetLength(length+10000);
	m_strConvertingData.GetBufferSetLength(length+10000);
	i=0;
	int j=0;
	
	while(i<length)
	{
		//TRACE("   %d %c ",i,m_strConvertingData.GetAt(i));
		switch(m_strConvertingData.GetAt(i))
		{
			case char(162) :
				i++;
				continue;
			case char(163) :
				m_strConvertedData.SetAt(j,'a');
				j++;
				m_strConvertedData.SetAt(j,'a');
				j++;
				i++;
				continue;
			case char(164) :
				m_strConvertedData.SetAt(j,'i');
				j++;
				i++;
				continue;
			case char(166) :
				m_strConvertedData.SetAt(j,'i');
				j++;
				m_strConvertedData.SetAt(j,'i');
				j++;
				i++;
				continue;
			case char(167) :
				m_strConvertedData.SetAt(j,'u');
				j++;
				i++;
				continue;
			case char(168) :
				m_strConvertedData.SetAt(j,'u');
				j++;
				m_strConvertedData.SetAt(j,'u');
				j++;
				i++;
				continue;
			case char(170) :
				if((char(m_strConvertingData.GetAt(i+2)) == char(247)))
				{
					if((char(m_strConvertingData.GetAt(i+3)) == char(163)) || 
					   (char(m_strConvertingData.GetAt(i+3)) == char(164)) || 
					   (char(m_strConvertingData.GetAt(i+3)) == char(166)) || 
					   (char(m_strConvertingData.GetAt(i+3)) == char(167)) || 
					   (char(m_strConvertingData.GetAt(i+3)) == char(168)) || 
					   (char(m_strConvertingData.GetAt(i+3)) == char(169))) 
					{
						m_strConvertedData.SetAt(j+1,'e');
					}
					else
					{
						m_strConvertedData.SetAt(j+1,'a');
						m_strConvertedData.SetAt(j+2,'u');
					}
				}
				else if(char(m_strConvertingData.GetAt(i+1)) == char(163))
				{	
					m_strConvertedData.SetAt(j+1,'o');
				}
				else
				{
					m_strConvertedData.SetAt(j+1,'e');
				}
				m_bFlagBefore = 1;
				i++;
				continue;
			case char(171) :
				if(char(m_strConvertingData.GetAt(i+2)) == char(163))
				{	
					m_strConvertedData.SetAt(j+1,'o');
					m_strConvertedData.SetAt(j+2,'o');
				}
				else
				{
					m_strConvertedData.SetAt(j+1,'e');
					m_strConvertedData.SetAt(j+2,'e');
				}
				m_bFlagBefore = 1;
				i++;
				continue;
			case char(172) :
				m_strConvertedData.SetAt(j+1,'a');
				m_strConvertedData.SetAt(j+2,'i');
				m_bFlagBefore = 1;
				i++;
				continue;
			case char(174) :
				m_strConvertedData.SetAt(j++,'t');
				m_strConvertedData.SetAt(j++,'i');
				i++;
				continue;
			case char(175) :
				m_strConvertedData.SetAt(j++,'t');
				m_strConvertedData.SetAt(j++,'i');
				m_strConvertedData.SetAt(j++,'i');
				i++;
				continue;
			case char(176) :
				m_strConvertedData.SetAt(j++,'k');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(177) :
				m_strConvertedData.SetAt(j++,'x');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;

			case char(178) :
				m_strConvertedData.SetAt(j++,'c');
				m_strConvertedData.SetAt(j++,'h');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(179) :
				m_strConvertedData.SetAt(j++,'x');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(180) :
				m_strConvertedData.SetAt(j++,'t');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(181) :
				m_strConvertedData.SetAt(j++,'n');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(182) :
				m_strConvertedData.SetAt(j++,'t');
				m_strConvertedData.SetAt(j++,'h');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(184) :
				m_strConvertedData.SetAt(j++,'n');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(185) :
				m_strConvertedData.SetAt(j++,'p');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(186) :
				m_strConvertedData.SetAt(j++,'m');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(187) :
				m_strConvertedData.SetAt(j++,'y');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(188) :
				m_strConvertedData.SetAt(j++,'r');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(189) :
				m_strConvertedData.SetAt(j++,'l');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(190) :
				m_strConvertedData.SetAt(j++,'v');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(191) :
				m_strConvertedData.SetAt(j++,'z');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(192) :
				m_strConvertedData.SetAt(j++,'l');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(193) :
				m_strConvertedData.SetAt(j++,'r');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(194) :
				m_strConvertedData.SetAt(j++,'n');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(195) :
				m_strConvertedData.SetAt(j++,'k');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(196) :
				m_strConvertedData.SetAt(j++,'x');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(197) :
				m_strConvertedData.SetAt(j++,'c');
				m_strConvertedData.SetAt(j++,'h');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(198) :
				m_strConvertedData.SetAt(j++,'x');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(199) :
				m_strConvertedData.SetAt(j++,'t');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(200) :
				m_strConvertedData.SetAt(j++,'n');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(201) :
				m_strConvertedData.SetAt(j++,'t');
				m_strConvertedData.SetAt(j++,'h');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(203) :
				m_strConvertedData.SetAt(j++,'n');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(204) :
				m_strConvertedData.SetAt(j++,'p');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(205) :
				m_strConvertedData.SetAt(j++,'m');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(206) :
				m_strConvertedData.SetAt(j++,'y');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(207) :
				m_strConvertedData.SetAt(j++,'r');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(214) :
				m_strConvertedData.SetAt(j++,'l');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(215) :
				m_strConvertedData.SetAt(j++,'v');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(216) :
				m_strConvertedData.SetAt(j++,'z');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(217) :
				m_strConvertedData.SetAt(j++,'l');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(218) :
				m_strConvertedData.SetAt(j++,'r');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(219) :
				m_strConvertedData.SetAt(j++,'n');
				m_strConvertedData.SetAt(j++,'1');
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(220) :
				m_strConvertedData.SetAt(j++,'a');
				i++;
				continue;
			case char(221) :
				m_strConvertedData.SetAt(j++,'a');
				m_strConvertedData.SetAt(j++,'a');
				i++;
				continue;
			case char(222) :
				m_strConvertedData.SetAt(j++,'i');
				i++;
				continue;
			case char(223) :
				m_strConvertedData.SetAt(j++,'i');
				m_strConvertedData.SetAt(j++,'i');
				i++;
				continue;
			case char(224) :
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(225) :
				m_strConvertedData.SetAt(j++,'u');
				m_strConvertedData.SetAt(j++,'u');
				i++;
				continue;
			case char(226) :
				m_strConvertedData.SetAt(j++,'e');
				i++;
				continue;
			case char(227) :
				m_strConvertedData.SetAt(j++,'e');
				m_strConvertedData.SetAt(j++,'e');
				i++;
				continue;
			case char(228) :
				m_strConvertedData.SetAt(j++,'a');
				m_strConvertedData.SetAt(j++,'i');
				i++;
				continue;
			case char(229) :
				if((char(m_strConvertingData.GetAt(i+1)) == char(247)))
				{
					m_strConvertedData.SetAt(j++,'a');
					m_strConvertedData.SetAt(j++,'u');
					i+=3;

				}
				else
				{
					m_strConvertedData.SetAt(j++,'o');
					i++;
				}
				continue;
			case char(230) :
				m_strConvertedData.SetAt(j++,'o');
				m_strConvertedData.SetAt(j++,'o');
				i++;
				continue;
			case char(231) :
				m_strConvertedData.SetAt(j++,'g');
				i++;
				continue;
			case char(232) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'k');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   (m_strConvertedData.GetAt(j+2) == 'u' || 
						    m_strConvertedData.GetAt(j+2) == 'i')))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'k');
					i++;
				}
				continue;
			case char(233) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'x');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'x');
					i++;
				}
				continue;
			case char(234) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'c');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'h');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'h');
						j++;

					}
					m_bFlagBefore = 0;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'c');
					m_strConvertedData.SetAt(j++,'h');
					i++;
				}
				continue;
			case char(235) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'x');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'1');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'1');
						j++;

					}
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'x');
					m_strConvertedData.SetAt(j++,'1');
					i++;
				}
				continue;
			case char(236) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'t');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'t');
					i++;
				}
				continue;
			case char(237) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'n');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'n');
					i++;
				}
				continue;
			case char(238) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'t');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'h');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'h');
						j++;
					}
					m_bFlagBefore = 0;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'t');
					m_strConvertedData.SetAt(j++,'h');
					i++;
				}
				continue;
			case char(239) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'n');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'1');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'1');
						j++;

					}
					m_bFlagBefore = 0;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'n');
					m_strConvertedData.SetAt(j++,'1');
					i++;
				}
				continue;
			case char(240) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'p');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;
					
					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'p');
					i++;
				}
				continue;
			case char(241) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'m');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'m');
					i++;
				}
				continue;
			case char(242) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'y');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'y');
					i++;
				}
				continue;
			case char(243) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'r');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'r');
					i++;
				}
				continue;
			case char(244) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'l');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'l');
					i++;
				}
				continue;
			case char(245) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'v');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'v');
					i++;
				}
				continue;
			case char(246) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'z');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'z');
					i++;
				}
				continue;
			case char(247) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'l');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'1');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'1');
						j++;

					}
					m_bFlagBefore = 0;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'l');
					m_strConvertedData.SetAt(j++,'1');
					i++;
				}
				continue;
			case char(248) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'r');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'1');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'1');
						j++;

					}
					m_bFlagBefore = 0;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'r');
					m_strConvertedData.SetAt(j++,'1');
					i++;
				}

					continue;
			case char(249) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'n');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'1');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'1');
						j++;
					}
					m_bFlagBefore = 0;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'n');
					m_strConvertedData.SetAt(j++,'1');
					i++;
				}
				continue;
			case char(250) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'s');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'s');
					i++;
				}
				continue;
			case char(251) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'s');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'s');
					i++;
				}
				continue;
			case char(252) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'j');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;


					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'j');
					i++;
				}
				continue;
			case char(253) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'h');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
						j+=3;
					else
						j+=2;
					m_bFlagBefore = FALSE;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'h');
					i++;
				}
				continue;
			case char(254) :
				if(m_bFlagBefore == TRUE)
				{
					m_strConvertedData.SetAt(j,'k');
					if(m_strConvertedData.GetAt(j+1) == 'o' || 
					  (m_strConvertedData.GetAt(j+1) == 'a' && 
					   m_strConvertedData.GetAt(j+2) == 'u'))
					{
					   if((m_strConvertedData.GetAt(j+1) == 'a' && 
						   m_strConvertedData.GetAt(j+2) == 'u'))
							i=i+3;
					   else
						    i=i+2;
					}
					else
						i++;

					if((m_strConvertedData.GetAt(j+1) == 'a') || 
					  (m_strConvertedData.GetAt(j+1) == 'o' && 
					   m_strConvertedData.GetAt(j+2) == 'o') || 
					  (m_strConvertedData.GetAt(j+1) == 'e' && 
					   m_strConvertedData.GetAt(j+2) == 'e'))
					{
						j+=3;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,m_strConvertedData.GetAt(j-2));
						m_strConvertedData.SetAt(j-2,'s');
						j++;
					}
					else
					{
						j+=2;
						m_strConvertedData.SetAt(j,m_strConvertedData.GetAt(j-1));
						m_strConvertedData.SetAt(j-1,'s');
						j++;

					}
					m_bFlagBefore = 0;
				}
				else
				{
					m_strConvertedData.SetAt(j++,'k');
					m_strConvertedData.SetAt(j++,'s');
					i++;
				}
				continue;
			case char(255) :
				m_strConvertedData.SetAt(j++,'s');
				m_strConvertedData.SetAt(j++,'r');
				m_strConvertedData.SetAt(j++,'i');
				i++;
				continue;
			case char(' '):
				m_strConvertedData.SetAt(j++,' ');
				i++;
				continue;
			case char('.'):
				m_strConvertedData.SetAt(j++,'.');
				m_strConvertedData.SetAt(j++,' ');
				i++;
				continue;
			case char('?'):
				m_strConvertedData.SetAt(j++,'?');
				m_strConvertedData.SetAt(j++,' ');
				i++;
				continue;
			case char('!'):
				m_strConvertedData.SetAt(j++,'!');
				m_strConvertedData.SetAt(j++,' ');
				i++;
				continue;
			case char(','):
				m_strConvertedData.SetAt(j++,',');
				m_strConvertedData.SetAt(j++,' ');
				i++;
				continue;
			case char('\n'):
				m_strConvertedData.SetAt(j++,' ');
				i++;
				continue;
			case char('~'):
				m_strConvertedData.SetAt(j++,'~');
				i++;
				continue;
			
			default:
				i++;
		}
	}
	m_strConvertedData.SetAt(j,'\0');
	
//	m_strConvertedData.FreeExtra();
	//TRACE("   %s",m_strConvertedData.Left(j));
	m_strConvertingData.ReleaseBuffer();
	m_strConvertedData.ReleaseBuffer();
	//AfxMessageBox(m_strConvertedData);
	//return(m_strConvertedData.Left(j));
	return(m_strConvertedData);
}

CString CVakDlg::ApplyTamilRules(CString m_strTempData)
{
	int length = m_strTempData.GetLength();
	BOOL NOCHANGE = 0;
	m_strTempData.GetBufferSetLength(length+10000);
	int j=0;
	int i=0;
	TRACE("\n Before Rules %s ",m_strTempData);
	while(i<length)
	{
		switch(m_strTempData.GetAt(i))
		{
			case 'k':
				if(i-1>=0)
				{
					if(m_strTempData.GetAt(i-1) == 'x' )
						m_strTempData.SetAt(i,'g');
					
					if(m_strTempData.GetAt(i-1) == '~' && !(i>2 && (m_strTempData.GetAt(i-2) == 'a' || m_strTempData.GetAt(i-2) == 'e' || m_strTempData.GetAt(i-2) == 'i' || m_strTempData.GetAt(i-2) == 'o' || m_strTempData.GetAt(i-2) == 'u') )&& !(i>2 && m_strTempData.GetAt(i-2) == 'x'))
					{
						m_strTempData.SetAt(i,'g');
					}
				}
				if(i+1<length)
					if(m_strTempData.GetAt(i+1) == 'x' || m_strTempData.GetAt(i+1) == 'n' || m_strTempData.GetAt(i+1) == 'm' || m_strTempData.GetAt(i+1) == 'y' || m_strTempData.GetAt(i+1) == 'r' || m_strTempData.GetAt(i+1) == 'l' || m_strTempData.GetAt(i+1) == 'v' || m_strTempData.GetAt(i+1) == 's')
						m_strTempData.SetAt(i,'g');
				if(i-1>=0 && i+1<length)
				{
					if(!(m_strTempData.GetAt(i-1) == '~'))
					{
						if((m_strTempData.GetAt(i-1) == 'a' || m_strTempData.GetAt(i-1) == 'e' || m_strTempData.GetAt(i-1) == 'i' || m_strTempData.GetAt(i-1) == 'o' || m_strTempData.GetAt(i-1) == 'u') 
						&& (m_strTempData.GetAt(i+1) == 'a' || m_strTempData.GetAt(i+1) == 'e' || m_strTempData.GetAt(i+1) == 'i' || m_strTempData.GetAt(i+1) == 'o' || m_strTempData.GetAt(i+1) == 'u'))
						m_strTempData.SetAt(i,'g');
					}
				}
				i++;
				continue;
			case 'c':
				if(i-2>=0)
					if(m_strTempData.GetAt(i-2) == 'x' && m_strTempData.GetAt(i-1) == '1')
					{
						m_strTempData.SetAt(i,'j');
						j=i+1;
						while(j-1 < length)
						{
							m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
							j++;
						}
					}
				if(i-1>=0)
				{
						
					if(m_strTempData.GetAt(i-1) == '~' && !(i>2 && (m_strTempData.GetAt(i-2) == 'a' || m_strTempData.GetAt(i-2) == 'e' || m_strTempData.GetAt(i-2) == 'i' || m_strTempData.GetAt(i-2) == 'o' || m_strTempData.GetAt(i-2) == 'u') ) && !(i>3 && m_strTempData.GetAt(i-3) == 'x' && m_strTempData.GetAt(i-2) == '1'))
					{
						m_strTempData.SetAt(i,'j');
						j=i+1;
						while(j-1 < length)
						{
							m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
							j++;
						}
					}
				}
				if(i == 0 && m_strTempData.GetAt(i) == 'c')
					{
							m_strTempData.SetAt(i,'s');
							j=i+1;
							while(j-1 < length)
							{
								m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
								j++;
							}
					}
				if(i-1>=0 && i+2<length )
				{
					if((m_strTempData.GetAt(i-1) == 'a' || m_strTempData.GetAt(i-1) == 'e' || m_strTempData.GetAt(i-1) == 'i' || m_strTempData.GetAt(i-1) == 'o' || m_strTempData.GetAt(i-1) == 'u') 
						&& (m_strTempData.GetAt(i+2) == 'a' || m_strTempData.GetAt(i+2) == 'e' || m_strTempData.GetAt(i+2) == 'i' || m_strTempData.GetAt(i+2) == 'o' || m_strTempData.GetAt(i+2) == 'u'))
					{
						m_strTempData.SetAt(i,'s');
						j=i+1;
						while(j-1 < length)
						{
							m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
							j++;
						}
					}
					if(m_strTempData.GetAt(i-1) == '~' && (m_strTempData.GetAt(i+2) == 'a' || m_strTempData.GetAt(i+2) == 'e' || m_strTempData.GetAt(i+2) == 'i' || m_strTempData.GetAt(i+2) == 'o' || m_strTempData.GetAt(i+2) == 'u') && !(i>3 && m_strTempData.GetAt(i-3) == 'x' && m_strTempData.GetAt(i-2) == '1'))
					{
							m_strTempData.SetAt(i,'j');
							j=i+1;
							while(j-1 < length)
							{
								m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
								j++;
							}
						
					}
					
					if(i >0 && m_strTempData.GetAt(i-1) == ' ' )
					{
						NOCHANGE=0;
						if(i-3>0)
							if(m_strTempData.GetAt(i-3) == 'c')
								NOCHANGE = 1;
						
						if(NOCHANGE == 0)
						{
							//TRACE("\n NOchange = %d",NOCHANGE);
							m_strTempData.SetAt(i,'s');
							j=i+1;
							while(j-1 < length)
							{
								m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
								j++;
							}
						}
					}
				}
				i++;
				continue;
		
			case 't':
				if(m_strTempData.GetAt(i+1) != 'h')
				{
					if(i-1>=0)
					{
						if(m_strTempData.GetAt(i-1) == 'n')
							m_strTempData.SetAt(i,'d');
						if(m_strTempData.GetAt(i-1) == '~' && !(i>2 && (m_strTempData.GetAt(i-2) == 'a' || m_strTempData.GetAt(i-2) == 'e' || m_strTempData.GetAt(i-2) == 'i' || m_strTempData.GetAt(i-2) == 'o' || m_strTempData.GetAt(i-2) == 'u') ) && !(i>2 && m_strTempData.GetAt(i-2) == 'n'))
						{
							m_strTempData.SetAt(i,'d');
						
						}
					}
					if(i-1>=0 && i+1<length && !(m_strTempData.GetAt(i-1) == '~'))
						if((m_strTempData.GetAt(i-1) == 'a' || m_strTempData.GetAt(i-1) == 'e' || m_strTempData.GetAt(i-1) == 'i' || m_strTempData.GetAt(i-1) == 'o' || m_strTempData.GetAt(i-1) == 'u') 
							&& (m_strTempData.GetAt(i+1) == 'a' || m_strTempData.GetAt(i+1) == 'e' || m_strTempData.GetAt(i+1) == 'i' || m_strTempData.GetAt(i+1) == 'o' || m_strTempData.GetAt(i+1) == 'u'))
							m_strTempData.SetAt(i,'d');
				}
				else if(m_strTempData.GetAt(i+1) == 'h')
				{
					if(i-1>=0)
					{
						if(m_strTempData.GetAt(i-1) == '~' && !(i>2 && (m_strTempData.GetAt(i-2) == 'a' || m_strTempData.GetAt(i-2) == 'e' || m_strTempData.GetAt(i-2) == 'i' || m_strTempData.GetAt(i-2) == 'o' || m_strTempData.GetAt(i-2) == 'u') ) && !(i>3 && m_strTempData.GetAt(i-2) == '1' && m_strTempData.GetAt(i-3) == 'n'))
						{
							m_strTempData.SetAt(i++,'d');
							m_strTempData.Insert(i,'h');
							length++;
							j=i+1;
							while(j-1 < length)
							{
								m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
								j++;
							}
						}
					}
					if(i-2>=0)
						if(m_strTempData.GetAt(i-2) == 'n' && m_strTempData.GetAt(i-1) == '1')
						{
							m_strTempData.SetAt(i++,'d');
							m_strTempData.Insert(i,'h');
							length++;
							j=i+1;
							while(j-1 < length)
							{
								m_strTempData.SetAt(j,m_strTempData.GetAt(j+1));
								j++;
							}
						}
					if(i-1>=0 && i+2<length  && !(m_strTempData.GetAt(i-1) == '~'))
						if((m_strTempData.GetAt(i-1) == 'a' || m_strTempData.GetAt(i-1) == 'e' || m_strTempData.GetAt(i-1) == 'i' || m_strTempData.GetAt(i-1) == 'o' || m_strTempData.GetAt(i-1) == 'u') 
							&& (m_strTempData.GetAt(i+2) == 'a' || m_strTempData.GetAt(i+2) == 'e' || m_strTempData.GetAt(i+2) == 'i' || m_strTempData.GetAt(i+2) == 'o' || m_strTempData.GetAt(i+2) == 'u'))
						{
							m_strTempData.SetAt(i,'d');
//							m_strTempData.SetAt(i,'d');
						}
				}
				i++;
				continue;
			case 'p':
				if(i-1>=0)
				{
					if(m_strTempData.GetAt(i-1) == 'm')
						m_strTempData.SetAt(i,'b');
					if(m_strTempData.GetAt(i-1) == 'n')
						m_strTempData.SetAt(i,'b');
					if((m_strTempData.GetAt(i-1) == '~') && !(i>=2 && (m_strTempData.GetAt(i-2) == 'a' || m_strTempData.GetAt(i-2) == 'e' || m_strTempData.GetAt(i-2) == 'i' || m_strTempData.GetAt(i-2) == 'o' || m_strTempData.GetAt(i-2) == 'u'))  && !(i>2 && m_strTempData.GetAt(i-2) == 'm') && !(i>2 && m_strTempData.GetAt(i-2) == 'n') && !(i>3 && m_strTempData.GetAt(i-3) == 'n' && m_strTempData.GetAt(i-2) == '1')   )
					{
						m_strTempData.SetAt(i,'b');
						
					}

				}

				if(i-2>=0 )
				{
					if(m_strTempData.GetAt(i-2) == 'n' && m_strTempData.GetAt(i-1) == '1')
						m_strTempData.SetAt(i,'b');
					
				}


				if(i-1>=0 && i+1<length && !(m_strTempData.GetAt(i-1) == '~'))
					if((m_strTempData.GetAt(i-1) == 'a' || m_strTempData.GetAt(i-1) == 'e' || m_strTempData.GetAt(i-1) == 'i' || m_strTempData.GetAt(i-1) == 'o' || m_strTempData.GetAt(i-1) == 'u') 
						&& (m_strTempData.GetAt(i+1) == 'a' || m_strTempData.GetAt(i+1) == 'e' || m_strTempData.GetAt(i+1) == 'i' || m_strTempData.GetAt(i+1) == 'o' || m_strTempData.GetAt(i+1) == 'u'))
					{
						m_strTempData.SetAt(i,'b');
					
					}
				i++;
				continue;
			case 'r':
				if(m_strTempData.GetAt(i+1)== '1')
				{
					if(m_strTempData.GetAt(i+2)== 'r')
						i+=3;
					else
					{
						m_strTempData.Delete(i+1,1);
						i++;
					}
				}
				else
					i++;
				continue;
			case 'e':
				if(m_strTempData.GetAt(i+1)== 'a')
				{
					if(m_strTempData.GetAt(i+2)== 'a')
					{
						m_strTempData.SetAt(i,'o');
						m_strTempData.Delete(i+1,2);
						i++;
					}
					else 
						i++;
				}
				else
					i++;
				continue;
			default:
				i++;
		}

	}
	m_strTempData.ReleaseBuffer();
	TRACE("\n After Rules %s ",m_strTempData);
	
	return(m_strTempData);
}


void CVakDlg::OnSpeakfile() 
{
	CFileDialog dlg(TRUE,"txt","*.txt");

	if((dlg.DoModal() == IDOK))
	{
		FileOpenFlag=1;
		CFile file;
		VERIFY(file.Open(dlg.GetPathName(),CFile::modeRead));
		const int len=file.SeekToEnd();
		int i=0;
		m_strText=new char [len+1];
		file.SeekToBegin();
		while(i<len)
		{
			file.Read(&m_strText[i],sizeof(char));
			i++;
		}
	
		m_strText[i]='\0';
		//TRACE("\n m_strtext = %s ",m_strText);
		file.Close();
		UpdateData(TRUE);
		m_strUpdateData=m_strText;
		m_strData='\0';
		int l=strlen(m_strText);
		m_strEnglish.GetBufferSetLength(l+2);
		m_strEnglish = m_strText;
		m_strEnglish+='\0';
		UpdateData(FALSE);
	}
	else
		FileOpenFlag=0;
	
	
		
	if(FileOpenFlag == 1)
	{
		FileOpenFlag=0;
	//	dlg.EndDialog(IDCANCEL);
		OnSpeak();
	}		
}

void CVakDlg::OnFileSpeak() 
{
	if(m_strData.IsEmpty())
		AfxMessageBox("Field is blank");
	else
		OnSpeak();	
}

void CVakDlg::OnFileSpeakfile() 
{
	CFileDialog dlg(TRUE,"TAB","*.TAB");

	if((dlg.DoModal() == IDOK))
	{
		FileOpenFlag=1;
		CFile file;
		VERIFY(file.Open(dlg.GetPathName(),CFile::modeRead));
		const int len=file.SeekToEnd();
		int i=0;
		m_strText=new char [len+1];
		file.SeekToBegin();
		while(i<len)
		{
			file.Read(&m_strText[i],sizeof(char));
			i++;
		}
	
		m_strText[i]='\0';
		//TRACE("\n m_strtext = %s ",m_strText);
		file.Close();
		UpdateData(TRUE);
		m_strUpdateData.GetBufferSetLength(i+1);
		m_strUpdateData=m_strText;
		m_strData='\0';
		int l=strlen(m_strText);
		m_strEnglish.GetBufferSetLength(l+2);
		m_strEnglish = m_strText;
		m_strEnglish+='\0';
		delete [] m_strText;
		UpdateData(FALSE);
	}
	else
		FileOpenFlag=0;
	
	
		
	if(FileOpenFlag == 1)
	{
		FileOpenFlag=0;
		//AfxMessageBox("Press speak Button");
	//	dlg.EndDialog(IDCANCEL);
	//	OnSpeak();
	}		
	
}


void CVakDlg::OnFileRepeat() 
{
	char *temp,*t;
	temp = new char [100];
	t = new char [20];
	char c;
	
	int i1=0;
	t="temp.wav";
	do
	{
		c = m_strActualPath.GetAt(i1);
		if(c == '$')
			break;
		temp[i1]=c;
		i1++;

	}while(c != '$');
	temp[i1] = '\0';
	strcat(temp,t);
	temp[strlen(temp)]= '\0';	
	CFile test;
	if(test.Open(temp,CFile::modeRead))
	{
		test.Close();
	
		OnPlayAgain();	
	}
	else
		AfxMessageBox("Enter the text");
	

}



void CVakDlg::OnFileSavefile() 
{
		CDoc doc;
		doc.Path=m_strActualPath;
		doc.SaveFile();
}

void CVakDlg::OnFileExit() 
{
	exit(1);
}

CString CVakDlg::ConvertNumbers()
{
	CString m_strInput,m_strOutput,m_strTemp;
	CString m_strInter;
	m_strEnglish.ReleaseBuffer(-1);
	int Flag=0;
	m_strInter.GetBufferSetLength(500);
	m_strInput.GetBufferSetLength(m_strEnglish.GetLength());
	m_strOutput.GetBufferSetLength(m_strEnglish.GetLength()+500);
	m_strTemp.GetBufferSetLength(50);
	m_strInput = m_strEnglish;


	int i=0,k=0,j=0;
	int l = m_strEnglish.GetLength();
//	TRACE(" \n m_strEnglish= %s",m_strEnglish);
	while(i<l)
	{
		while(!(m_strInput[i] == '0' || m_strInput[i] == '1' || m_strInput[i] == '2' || m_strInput[i] == '3' || m_strInput[i] == '4' || m_strInput[i] == '5' || m_strInput[i] == '6' || m_strInput[i] == '7' || m_strInput[i] == '8' || m_strInput[i] == '9' ))
		{
			m_strOutput.SetAt(k,m_strInput[i]);
			i++;
			k++;
			//Flag=0;
			if(i>=l)
				break;
			
		}
		
		if(i>=l)
				break;
		if(m_strInput[i] == '0' || m_strInput[i] == '1' || m_strInput[i] == '2' || m_strInput[i] == '3' || m_strInput[i] == '4' || m_strInput[i] == '5' || m_strInput[i] == '6' || m_strInput[i] == '7' || m_strInput[i] == '8' || m_strInput[i] == '9' )
		{
			j=0;
			/*if(i>0 && (m_strInput[i-1] == 'n' || m_strInput[i-1] == 'l') )
			{
				i++;
				continue;
			}*/
			if((i>0 && m_strInput[i-1] == ' ') || i == 0)
				FlagSpace=1;
			else
				FlagSpace=0;
			while(m_strInput[i] == '0' || m_strInput[i] == '1' || m_strInput[i] == '2' || m_strInput[i] == '3' || m_strInput[i] == '4' || m_strInput[i] == '5' || m_strInput[i] == '6' || m_strInput[i] == '7' || m_strInput[i] == '8' || m_strInput[i] == '9' )
			{
				m_strTemp.SetAt(j,m_strInput[i]);
				j++;
				i++;
			
				if(i>=l)
				break;

			}
			m_strTemp.SetAt(j,'\0');
			m_strInter=Convert(m_strTemp);
			Flagnumber=1;
			m_strInter.ReleaseBuffer(-1);
			//TRACE(" m_strInter = %s, l= %d",m_strInter,m_strInter.GetLength());
			m_strOutput.SetAt(k,'\0');
			
			for(int j=0;j<m_strInter.GetLength();j++)
			{
				m_strOutput.SetAt(k,m_strInter.GetAt(j));
				k++;
			}

					
		}

	}
	
	m_strOutput.SetAt(k,'\0');
	m_strOutput.ReleaseBuffer(-1);
	return m_strOutput;

}

CString CVakDlg::Convert(CString m_strTemp)
{
	char *m_strConvert;
	CString m_strSend;
	m_strSend.GetBufferSetLength(300);
	m_strConvert= new char [300];
	int FlagR=0,FlagThousand=0,FlagOne=0,FlagLakh=0,FlagTwo=0;
	int FlagThree=0,FlagCrore=0,FlagFour=0,FlagFive=0,FlagHunCrore=0,FlagThousCrore=0,FlagThou=0,FlagFR=0;
	int FlagThola=0;
	if(FlagSpace == 1)
	{
		m_strConvert[0]='\0';
		
	}
	else
	{
		m_strConvert[0]=' ';
		m_strConvert[1] = '\0';
	}
	int l = strlen(m_strTemp);
	int count=l;
	while(count > 0)
	{

		if(count == 1 || FlagOne == 1 || FlagTwo == 1 || FlagThree == 1 || FlagFive == 1)
		{
			char c=m_strTemp[l-count];
			switch(c)
			{
				case '0' : strcat(m_strConvert,"[d/s");
					break;
				case '1' :strcat(m_strConvert,"c;fud ");
						break;
				case '2' :strcat(m_strConvert,"smpfod ");
						break;
				case '3' : strcat(m_strConvert,"ke;fmd ");
						break;
				case '4' : strcat(m_strConvert,";q;fhd ");
						break;
				case '5' : strcat(m_strConvert,"r;fld ");
						break;
				case '6' : strcat(m_strConvert,"qmd ");
						break;
				case '7' : strcat(m_strConvert,"t/d ");
						break;
				case '8' : strcat(m_strConvert,"good ");
						break;
				case '9' : strcat(m_strConvert,"c;fjld ");
						break;
				default : break;
			}
			count--;
			if(FlagOne == 1)
			{
					if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0')
					{
						strcat(m_strConvert,"q'smkf ");
						count=count-3;
					}
					else
						strcat(m_strConvert,"q'smlls ");
					FlagThousand = 0;
					FlagOne=0;
			}
			else if(FlagTwo == 1)
			 {
				if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0')
				{
				       strcat(m_strConvert,"nof[kf ");
					count=count-5;
				}
				else
					strcat(m_strConvert,"nof[lls ");
				FlagLakh = 0;
				FlagTwo=0;
			}
			else if(FlagThree == 1)
			 {
				if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0')
				{
				       strcat(m_strConvert,"hxos ");
					count=count-7;
				}
				else
					strcat(m_strConvert,"hxos'g ");
				FlagThree = 0;
				FlagCrore=0;
			}
			else if(FlagFive == 1)
			 {
				if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0')
				{
				       strcat(m_strConvert,"hxos ");
					count=count-8;
				}
				else
					strcat(m_strConvert,"hxos'g ");
				FlagFive = 0;
				FlagThousCrore=0;
			}

		}
		else if(count == 2 || FlagThousand == 1 || FlagLakh == 1 || FlagCrore == 1 || FlagFour == 1)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;
			else if(m_strTemp[l-count]  == '1')
			{
				switch(m_strTemp[l-count+1])
				{
					case '0':if(FlagThousand == 1)
								strcat(m_strConvert,"jll");
						else
							strcat(m_strConvert,"jlld ");
						break;
					case '1': strcat(m_strConvert,"jls;c;fmd ");
						break;
					case '2': strcat(m_strConvert,"j;;smgpod ");
						break;
					case '3': strcat(m_strConvert,"jlske;fmd ");
						break;
					case '4': strcat(m_strConvert,"jls;qnd ");
						break;
					case '5': strcat(m_strConvert,"jls;r;fld ");
						break;
					case '6': strcat(m_strConvert,"jls;qmd ");
						break;
					case '7': strcat(m_strConvert,"jls;t/d ");
						break;
					case '8': strcat(m_strConvert,"jls;good ");
						break;
					case '9': strcat(m_strConvert,"jllc;fjld ");
						break;
					default: break;
				}
				count=count-2;
			}
			else if(m_strTemp[l-count] == '2' && m_strTemp[l-count+1] == '0')
			{
				strcat(m_strConvert,"smdvld ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '2' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"smdvlls ");
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
				strcat(m_strConvert,"kdjjld ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '3' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"kdjjlls ");
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
				strcat(m_strConvert,"pqmfjld ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '4' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"pqmfjlls ");
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
				strcat(m_strConvert,"rkfjld ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '5' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"rkfjlls ");
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
				strcat(m_strConvert,"amdvld ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '6' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"amdvlls ");
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
				strcat(m_strConvert,"g/dvld ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '7' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"g/dvlls ");
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
				strcat(m_strConvert,"g;fjld ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '8' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"g;fjlls ");
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
				strcat(m_strConvert,"lcppemd ");
				count=count-2;
			}
			else if(m_strTemp[l-count] == '9' && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"lcppeuus ");
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
							strcat(m_strConvert,"q'smkf ");
							count=count-3;
						}
						else
							strcat(m_strConvert,"q'smlls ");
					}
				FlagThousand=0;
			 }
			 if(FlagLakh == 1)
			{
					if(!(FlagTwo == 1))
					{
						if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0')
						{
							strcat(m_strConvert,"nof[kf ");
							count=count-5;
						}
						else
							strcat(m_strConvert,"nof[lls ");
					}
					FlagLakh=0;
			 }
			 if(FlagCrore == 1)
			{
					if(!(FlagThree == 1))
					{
						if(m_strTemp[l-count] == '0' && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0')
						{
							strcat(m_strConvert,"hxos ");
							count=count-7;
						}
						else
							strcat(m_strConvert,"hxos'g ");
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
							strcat(m_strConvert,"hxos ");
							count=count-7;
						}
						else
							strcat(m_strConvert,"hxos'g ");
					}
				}
					FlagFour=0;
			 }

		}
		else if(count == 3 || FlagHunCrore == 1 || FlagThou == 1)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0')
			{
				if(FlagThola == 1)
				{
					strcat(m_strConvert,"q'smakf");
					FlagThola=0;
				}
				else
					strcat(m_strConvert,";emd ");
				if(FlagHunCrore == 1)
				{
					if(m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0' && m_strTemp[l-count+8] == '0' && m_strTemp[l-count+9] == '0' && m_strTemp[l-count+4] == '0')
					{
						strcat(m_strConvert,"hxos ");
						count=count-10;
					}
					else
						strcat(m_strConvert,"hxos'g ");
					FlagHunCrore=0;
				}
				if(FlagThou == 1)
				{
					if(m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0' && m_strTemp[l-count+8] == '0' && m_strTemp[l-count+9] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0')
					{
						strcat(m_strConvert,"hxos ");
						count=count-11;
					}
					else
						strcat(m_strConvert,"hxos'g ");
					FlagThou=0;
				}

				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && !(m_strTemp[l-count+2] == '0'))
			{
				if(FlagThola == 1)
				{
					strcat(m_strConvert,"q'smalls ");
					FlagThola=0;
				}
				else				
					strcat(m_strConvert,";euus ");
				if(FlagHunCrore == 1)
				 {
					strcat(m_strConvert,"hxos'g ");
					FlagHunCrore=0;
				 }
				 if(FlagThou == 1)
				 {
					strcat(m_strConvert,"hxos'g ");
					FlagThou=0;
				 }
				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && !(m_strTemp[l-count+1] == '0'))
			{
				if(FlagThola == 1)
				{
					strcat(m_strConvert,"q'smalls ");
					FlagThola=0;
				}
				else
					strcat(m_strConvert,";euus ");
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
				strcat(m_strConvert,"smd");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"kd;");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,";q");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"r");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"amd");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"g/d");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"g;");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"lcy");
				FlagThola=1;
				FlagR=1;
			}

		}
		// 1000 to 9999
		else if(count == 4 || FlagThousCrore == 1)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0')
			{
				strcat(m_strConvert,"q'smkf ");
				if(FlagThousCrore == 1)
				{
					if(m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0' && m_strTemp[l-count+7] == '0' && m_strTemp[l-count+8] == '0' && m_strTemp[l-count+9] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0')
					{
						strcat(m_strConvert,"hxos ");
						count=count-11;
					}
					else
						strcat(m_strConvert,"hxos'g ");
					FlagThousCrore=0;
				}
				count=count-4;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && !(m_strTemp[l-count+2] == '0'))
			{
				strcat(m_strConvert,"q'smlls ");
				if(FlagThousCrore == 1)
				 {
					strcat(m_strConvert,"hxos'g ");
					FlagThousCrore=0;
				 }

				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0')
			{
				strcat(m_strConvert,"q'smlls ");
				if(FlagThousCrore == 1)
				 {
					strcat(m_strConvert,"hxos'g ");
					FlagThousCrore=0;
				 }

				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && !(m_strTemp[l-count+1] == '0'))
			{
				strcat(m_strConvert,"q'smlls ");
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
				strcat(m_strConvert,"smpo");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"kev");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,";qn");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"r'");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"qu");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"t/");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"goo");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"c;fjl");
				FlagR=1;
			}
		}
		else if(count == 5)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else
				FlagThousand = 1;
		}
		else if(count == 6)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0')
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				
				strcat(m_strConvert,"nof[kf ");
				count=count-6;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && m_strTemp[l-count+2] == '0' && (m_strTemp[l-count+3] == '0') && m_strTemp[l-count+4] == '0' && !(m_strTemp[l-count+5] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				
				strcat(m_strConvert,"nof[lls ");
				count=count-5;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && !(m_strTemp[l-count+4] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				
				strcat(m_strConvert,"nof[lls ");
				count=count-4;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && !(m_strTemp[l-count+3] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
								strcat(m_strConvert,"nof[lls ");
				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && !(m_strTemp[l-count+2] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				
				strcat(m_strConvert,"nof[lls ");
				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && !(m_strTemp[l-count+1] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				
				strcat(m_strConvert,"nof[lls ");
				count=count-1;
				FlagR=0;
			}
			else if(m_strTemp[l-count] == '2')
			{
				strcat(m_strConvert,"smpfod ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"ke;fmd ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,";q;fhd ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"r;fld ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"qmd ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"t/d ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"good ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"c;fjld ");
				FlagR=1;
			}
		}
		else if(count == 7)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else
				FlagLakh = 1;
		}
		else if(count == 8)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else if((m_strTemp[l-count] == '1' || FlagR ==1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && m_strTemp[l-count+6] == '0'  && m_strTemp[l-count+7] == '0' )
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos ");
				count=count-8;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && m_strTemp[l-count+2] == '0' && (m_strTemp[l-count+3] == '0') && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0'  && m_strTemp[l-count+6] == '0' && !(m_strTemp[l-count+7] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos'g ");
				count=count-7;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && m_strTemp[l-count+5] == '0' && !(m_strTemp[l-count+6] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos'g ");
				count=count-6;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && m_strTemp[l-count+4] == '0' && !(m_strTemp[l-count+5] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos'g ");
				count=count-5;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && (m_strTemp[l-count+1] == '0') && m_strTemp[l-count+2] == '0' && m_strTemp[l-count+3] == '0' && !(m_strTemp[l-count+4] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos'g ");
				count=count-4;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0' && m_strTemp[l-count+2] == '0' && !(m_strTemp[l-count+3] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos'g ");
				count=count-3;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1) && m_strTemp[l-count+1] == '0'  && !(m_strTemp[l-count+2] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos'g ");
				count=count-2;
				FlagR=0;
			}
			else if((m_strTemp[l-count] == '1' || FlagR == 1)   && !(m_strTemp[l-count+1] == '0'))
			{
				if(FlagR == 0)
					strcat(m_strConvert,"c;fud ");
				strcat(m_strConvert,"hxos'g ");
				count=count-1;
				FlagR=0;
			}

			else if(m_strTemp[l-count] == '2')
			{
				strcat(m_strConvert,"smpfod ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '3')
			{
				strcat(m_strConvert,"ke;fmd ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '4')
			{
				strcat(m_strConvert,";q;fhd ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '5')
			{
				strcat(m_strConvert,"r;fld ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '6')
			{
				strcat(m_strConvert,"qmd ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '7')
			{
				strcat(m_strConvert,"t/d ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '8')
			{
				strcat(m_strConvert,"good ");
				FlagR=1;
			}
			else if(m_strTemp[l-count] == '9')
			{
				strcat(m_strConvert,"c;fjld ");
				FlagR=1;
			}

		}
		else if(count == 9)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else
				FlagCrore = 1;
		}
		else if(count == 10)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else
				FlagHunCrore=1;
		}
		else if(count == 11)
		{
			if(m_strTemp[l-count] == '0')
				count=count-1;

			else
				FlagThousCrore=1;
		}

		else if(count > 11)
		{
			m_strConvert='\0';
			count=count-l;
		}
		else
			break;

	}

//	TRACE(" \n m_strConvert = %s",m_strConvert);
	m_strSend = OnConvertData(m_strConvert);
	m_strSend.ReleaseBuffer(-1);
	return m_strSend;
}


void CVakDlg::OnFileSavetext() 
{
	CFileDialog dlg(FALSE,"TAB","*.TAB");
	//CString s;
	//	TRACE("\n m_strEnglish = %s",m_strEnglish);
	m_strEnglish.ReleaseBuffer();
	//TRACE("\n length = %d",m_strEnglish.GetLength());
	if((dlg.DoModal() == IDOK))
	{
		//FileSaveFlag=1;
		CFile out;
		char c;
		VERIFY(out.Open(dlg.GetPathName(),CFile::modeWrite | CFile::modeCreate));
		//int i=0;
		for(int i=0;i<m_strEnglish.GetLength();i++)
		//while(c != '\0')
		{
			c=m_strEnglish.GetAt(i);
			out.Write(&c,sizeof(char));
		}
		out.Close();
	}	
}

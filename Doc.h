#if !defined(AFX_DOC_H__895BE967_9557_49ED_98CE_0CE25B67C47C__INCLUDED_)
#define AFX_DOC_H__895BE967_9557_49ED_98CE_0CE25B67C47C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Doc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoc document

class CDoc : public CDocument
{
public:
	CDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoc)
	public:
		afx_msg void KannadaParse();
		afx_msg void CheckOnce();
		afx_msg void KannadaConcatenate();
		afx_msg void WriteWaveFile();
		//afx_msg CString ConvertNumbers();
		afx_msg void KannadaSynthesize();
		afx_msg void PlaySou();
		afx_msg int ChangeFileName(int);
		afx_msg int DetectDuration();
		virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL FlagWordEnd;
	BOOL FlagWordBegin;
	unsigned int SizeOfSentance;
	int FlagSpace;
	CString Path;
	short int *ConcatenateData;
	char *m_cToConcatenate;
	short unsigned int m_nBasicUnit;
	unsigned int pmind;
	short int *PM;	
	short int *Signal;
	short int *m_sPitchMark;
	unsigned int m_nSize;
	CString m_sFileName;
	CString m_sPreviouFileName;
	CString	m_strKannadaData;
	CFile *fp;
	int CountUnit,CUnitArray[5000],index,index2,CountSpace,CSpace[5000];
	char m_cTag[100];
	char m_cTagcopy[100];
	char ToDuration[60];
	void ExtendKannadaParse(int);
	char m_prs[100][50],m_qline[100][50],m_newqline[100][50],qword[50][50];

	struct IIScHeader
	{
		char FileID[4];
		int junk;
		int Ctype;
		unsigned char LanguageID;
		unsigned char BasicUnit;
		short int DataLength;
		short int AvgPitch;
		short int LSegment;
		short int RSegment;
		short int LengthofPitchMarks;
	};

	struct WAVEheader
	{	
		char ckID[4];              /* chunk id 'RIFF'            */
		unsigned int ckSize;           /* chunk size                 */
		char wave_ckID[4];         /* wave chunk id 'WAVE'       */
		char fmt_ckID[4];          /* format chunk id 'fmt '     */
		unsigned int fmt_ckSize;       /* format chunk size          */
		unsigned short int  formatTag;            /* format tag currently pcm   */
		unsigned short int  nChannels;            /* number of channels         */
		unsigned int nSamplesPerSec;   /* sample rate in hz          */
		unsigned int nAvgBytesPerSec;  /* average bytes per second   */
		unsigned short int  nBlockAlign;          /* number of bytes per sample */
		unsigned short int  nBitsPerSample;       /* number of bits in a sample */
		char data_ckID[4];         /* data chunk id 'data'       */
		unsigned int data_ckSize;      /* length of data chunk       */
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOC_H__895BE967_9557_49ED_98CE_0CE25B67C47C__INCLUDED_)

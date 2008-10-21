#if !defined(AFX_DOCUMENT_H__E6C784DA_0350_11D5_8A27_0050FC0C3667__INCLUDED_)
#define AFX_DOCUMENT_H__E6C784DA_0350_11D5_8A27_0050FC0C3667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Document.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Document document

class Document : public CDocument
{
public:
	Document();           // protected constructor used by dynamic creation
protected:
	DECLARE_DYNCREATE(Document)

// Attributes
public:

// Operations
public:
	int FlagWordEnd;
	int SizeOfSentance;
	short int *ConcatenateData;
	char *m_cToConcatenate;
	short unsigned int m_nBasicUnit;
	
	short int *signal;
	unsigned int m_nSize;
	CString m_sFileName;
	CString	m_strKannadaData;
	CFile *fp;
	
	float *m_fAutoCorrelation;
	
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

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Document)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
public:
	//AFX_MSG(Document)
	
		afx_msg int docread();
		afx_msg void KannadaConcatenate(int);
		afx_msg void WriteWaveFile();
		afx_msg void KannadaParse();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCUMENT_H__E6C784DA_0350_11D5_8A27_0050FC0C3667__INCLUDED_)

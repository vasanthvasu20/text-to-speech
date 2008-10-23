/**********************************************************************
 * File:                Doc.h  
 * Description:         header file for the Doc class
 * Author:              Jayavardhana Rama G L and Prathibha P
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



#if !defined(AFX_DOC_H__A94877E3_03F4_11D5_8A27_0050FC0C3667__INCLUDED_)
#define AFX_DOC_H__A94877E3_03F4_11D5_8A27_0050FC0C3667__INCLUDED_

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
		CString Path;
		void SaveFile();
		
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoc)
	public:
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
public:
	//{{AFX_MSG(CDoc)
		afx_msg int docread();
		afx_msg void KannadaParse();
		afx_msg void CheckOnce();
		afx_msg void KannadaConcatenate();
		afx_msg void WriteWaveFile();
		//afx_msg CString ConvertNumbers();
		afx_msg void KannadaSynthesize();
		afx_msg void PlaySou();
		afx_msg int ChangeFileName(int);
		afx_msg int DetectDuration();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL FlagWordEnd;
	BOOL FlagWordBegin;
	unsigned int SizeOfSentance;
	int FlagSpace;
	//CString Convert(CString m_strTemp);
	short int *ConcatenateData;
	char *m_cToConcatenate;
	short unsigned int m_nBasicUnit;
	short int *PM;	
	unsigned int pmind;
	short int *Signal;
	short int *m_sPitchMark;
	short int *pmark,*pmarkdiff;
	unsigned int m_nSize,pmdifflen;
	int Flagnumber;
	int Flagquit;
	CString m_sFileName;
	CString m_sPreviouFileName;
	CString	m_strKannadaData;
	CFile *fp;
	int CountUnit,CUnitArray[5000],index,index2,CountSpace,CSpace[5000];
	float *m_fAutoCorrelation;
	
	char ToDuration[60];

	struct IIScHeader
	{
		char FileID[4];
		int junk;
		int junk1;
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

#endif // !defined(AFX_DOC_H__A94877E3_03F4_11D5_8A27_0050FC0C3667__INCLUDED_)

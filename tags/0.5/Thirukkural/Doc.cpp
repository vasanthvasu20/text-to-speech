// Doc.cpp : implementation file
//

#include "stdafx.h"
#include "Vak.h"
#include "Doc.h"
#include "vakdlg.h"

#include "mmsystem.h"
#include "fstream.h"
#include "afx.h"

#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "PitchMod.h"
#include "new"

#define MULTIPLICATION_FACTOR 6
#define DUR_A 75
#define DUR_AA 130
#define DUR_I 75
#define DUR_II 132
#define DUR_U 64
#define DUR_UU 150
#define DUR_AI 130   // RANDOMLY CHOOSEN
#define DUR_AU 130	 // RANDOM CHOOSEN
#define DUR_O 75
#define DUR_OO 159
#define DUR_E 75
#define DUR_EE 159

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoc

IMPLEMENT_DYNCREATE(CDoc, CDocument)

CDoc::CDoc()
{
}

BOOL CDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDoc::~CDoc()
{
	//delete [] PM;
}


BEGIN_MESSAGE_MAP(CDoc, CDocument)
	//{{AFX_MSG_MAP(CDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoc diagnostics

#ifdef _DEBUG
void CDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoc serialization

void CDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDoc commands

int CDoc::docread() 
{
	FILE *in;
	int temp = 0;
	IIScHeader IISc;
	in=fopen(m_sFileName,"rb");
	if(!in)
	{
		TRACE("\t ********** %s ---> Does not Exist *********",m_sFileName);
		return 0;
	}
	fscanf(in,"%s ",&IISc.FileID);
	fscanf(in,"%d ",&IISc.junk);
	fscanf(in,"%d ",&IISc.junk1);
	fscanf(in,"%u ",&IISc.LanguageID);
	fscanf(in,"%u ",&IISc.BasicUnit);
	fscanf(in,"%d ",&IISc.DataLength);
	fscanf(in,"%d ",&IISc.AvgPitch);
	fscanf(in,"%d ",&IISc.LSegment);
	fscanf(in,"%d ",&IISc.RSegment);
	fscanf(in,"%d\n",&IISc.LengthofPitchMarks);
	Signal = new short int [IISc.DataLength];
	m_sPitchMark = new short int [IISc.DataLength];
	
	m_nSize = IISc.DataLength;

	for(int i=0;i<IISc.DataLength;i++)
		fscanf(in,"%d ",&Signal[i]);

	for(i=0;i<IISc.DataLength;i++)
	{
		fscanf(in,"%d ",&temp);
		m_sPitchMark[temp] =1;
	}

	fclose(in);
	return 1;
}


void CDoc::KannadaParse()
{

	int Trace = 0,i1=0;
	FILE *parse;
	char c='0';
	char TempArray[5000];
	char Parse[100];
	char p[20] = "parse.iis";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Parse[i1]=c;
		i1++;

	}while(c != '$');
	Parse[i1] = '\0';
	strcat(Parse,p);
	Parse[strlen(Parse)]= '\0';
	parse = fopen(Parse,"w");
	CString str;
	int i=0,j,k,start=0,end=0,Word_Begin=0,Word_End=0,l=0;
	int Total_Length = 0;
		//while(m_strKannadaData.GetAt(Total_Length) != '\0')
//		Total_Length++;
	Total_Length=m_strKannadaData.GetLength();
	//TRACE(" \n Length of m_strKannada = %d",Total_Length);
	//TRACE("\n m_strKanndata = %s, l = %d",m_strKannadaData,m_strKannadaData.GetLength());
	int Length = 0;
	CountUnit=0,CountSpace=0;
	index=0,index2=0;
	char *Array = m_strKannadaData.GetBuffer(Length+10000);
	int countword = 0;
	TRACE("\n In Parse %d ",Total_Length);
	for(i=0;i<1000;i++)
	{
		CUnitArray[i]=-1;
		CSpace[i]=-1;				
	}

	do
	{
		start=0;
		end=0;

		if(Array[l] == ' ' || Array[l] == '\n')
			l++;

		Word_Begin=l;
		l=Word_End;
		while(Array[l] != ' ' && l<Total_Length)
		{
			l++;
			if(Array[l] == '\n')
				break;
		}

		if(Array[l] == ' ' || Array[l] == '\n')// || Array[l] == '.')
		{
			l++;
			while(Array[l] == ' ' || Array[l] == '\n' || Array[l] == '.')
				l++;
		}
		Word_End=l;

		Length = Word_End - Word_Begin;
		countword++;
		TRACE("\n Length =%d,End = %d, Begin = %d",Length,Word_End,Word_Begin);
		/*if(countword > 1 && Flagnumber == 0	)
		{
			//AfxMessageBox("Enter Single word");
			Flagquit=1;
			break;
		}*/
		/*else if(countword > 4 && Flagnumber == 1)
		{
			//AfxMessageBox("Enter Single word");
			Flagnumber=0;
			Flagquit=1;
			break;
		}*/
		fprintf(parse,"x ");
		CountSpace=CountUnit;
		
		CountUnit++;
		int DOT=0,QUEST=0,COMMA=0,EXCLAIM=0,QUOTES=0;

		for(i=Word_Begin,j=0;i<Word_End;i++,j++)
		{
			DOT=0;
			QUEST=0;
			COMMA=0;
			EXCLAIM=0;
			QUOTES=0;
			if(Array[i] == '.')
			{
				DOT=1;
				//TRACE(" \ndot = %d",DOT);
				break;
			}
			else if(Array[i] == '?')
			{
				QUEST=1;
				//TRACE(" \nQ = %d",QUEST);
				break;
			}
			else if(Array[i] == '!')
			{
				EXCLAIM=1;
				//TRACE(" \nEx = %d",EXCLAIM);
				break;
			}
			else if(Array[i] == ',')
			{
				COMMA=1;
				//TRACE(" \nCom = %d",COMMA);
				break;
			}

			if(Array[i] == ' ' || Array[i] == '\n')
			{
				j--;
				continue;
			}
			TempArray[j] = Array[i];
		}
		TempArray[j] = '\0';
		//TRACE("\t %s  %d  -->\t ",TempArray,j-1);
		if(j-1 == -1)
			continue;
		Length = j;
		i=0;j=0;
		FlagWordEnd=0;
		FlagWordBegin=1;
		
		do
		{
			if(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)))
			{
				start=i;
				do
				{
					i++;
				}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)) && ((TempArray[i] != '\n') && (i < Length)));
				end=i-1;
			
				if(TempArray[i] == 'a')
				{
					if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
						end = i+2;
					else if(TempArray[i+1] == 'a' || TempArray[i+1] == 'i' || TempArray[i+1] == 'u')
						end = i+1;
					else
						end = i;
				}
					
				if(TempArray[i] == 'i' || TempArray[i] == 'o' || TempArray[i] == 'u' || TempArray[i] == 'e')
				{
					if((TempArray[i+1] == 'i' || TempArray[i+1] == 'o' || TempArray[i+1] == 'u' || TempArray[i+1] == 'e') && (i+1 < Length))
						end = i+1;
					else
						end=i;
				}
			}
			else
			{	
				switch(TempArray[i])
				{
					case 'a' :
						start=i;	
						i++;
						if(TempArray[i] == 'e' || TempArray[i] == 'o')
							i=i+2;
						if(TempArray[i] == 'a')
							i=i+1;
						do
						{
							i++;
						}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)) && ((TempArray[i] != '\n') && (i < Length)));
						
						end=i-1;
						if(end>=Length);
						else
						{
							if(TempArray[i] == 'a')
							{
								if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
									end = i+2;
								else if((TempArray[i+1] == 'a' || TempArray[i+1] == 'i' || TempArray[i+1] == 'u') && ((i+1)<Length))
									end = i+1;
								else
									end = i;
								//TRACE(" < In 1>  ",i,Length);
							}
							if(TempArray[i] == 'i' || TempArray[i] == 'o' || TempArray[i] == 'u' || TempArray[i] == 'e')
							{
								if((TempArray[i+1] == 'i' || TempArray[i+1] == 'o' || TempArray[i+1] == 'u' || TempArray[i+1] == 'e') && (i+1 < Length))
									end = i+1;
								else
									end=i;
								//TRACE(" < In 2>  ",i,Length);
							}
						}
						
						if(TempArray[end] == ' ' || TempArray[end] == '\n')
							i=end;
						break;
					case 'i' :
						Trace = 2;
						start=i;
						i++;
						
						if(TempArray[i] == 'i')
							i=i+1;
						
						do
						{	
							i++;
						}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)) && ((TempArray[i] != '\n') && (i < Length)));
						end=i-1;
						
						if(end>=Length);
						else
						{

							if(TempArray[i] == 'a')
							{
								if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
									end = i+2;
								else if(TempArray[i+1] == 'a' || TempArray[i+1] == 'i' || TempArray[i+1] == 'u')
									end = i+1;
								else
									end = i;
							}
					
							if(TempArray[i] == 'i' || TempArray[i] == 'o' || TempArray[i] == 'u' || TempArray[i] == 'e')
							{
								if((TempArray[i+1] == 'i' || TempArray[i+1] == 'o' || TempArray[i+1] == 'u' || TempArray[i+1] == 'e') && (i+1 < Length))
									end = i+1;
								else
									end=i;
							}
						}
						if(TempArray[end] == ' ' || TempArray[end] == '\n')
							i=end;
						break;
					case 'e' :
						Trace = 3;
						start=i;
						i++;
						
						if(TempArray[i] == 'e')
							i=i+1;
						do
						{
							i++;
						}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)) && ((TempArray[i] != '\n') && (i < Length)));
						end=i-1;
						if(end>=Length);
						else
						{
							if(TempArray[i] == 'a')
							{
								if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
									end = i+2;
								else if(TempArray[i+1] == 'a' || TempArray[i+1] == 'i' || TempArray[i+1] == 'u')
									end = i+1;
								else
									end = i;
							}
					
							if(TempArray[i] == 'i' || TempArray[i] == 'o' || TempArray[i] == 'u' || TempArray[i] == 'e')
							{
								if((TempArray[i+1] == 'i' || TempArray[i+1] == 'o' || TempArray[i+1] == 'u' || TempArray[i+1] == 'e') && (i+1 < Length))
									end = i+1;
								else
									end=i;
							}
						}
						if(TempArray[end] == ' ' || TempArray[end] == '\n')
							i=end;
						break;
					case 'o' :
						Trace = 4;
						start=i;
						i++;
						if(TempArray[i] == 'o')
							i=i+1;
						
						do
						{
							i++;
						}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)) && ((TempArray[i] != '\n') && (i < Length)));
						end=i-1;
						if(end>=Length);
						else
						{
							if(TempArray[i] == 'a')
							{
								if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
									end = i+2;
								else if(TempArray[i+1] == 'a' || TempArray[i+1] == 'i' || TempArray[i+1] == 'u')
									end = i+1;
								else
									end = i;
							}
					
							if(TempArray[i] == 'i' || TempArray[i] == 'o' || TempArray[i] == 'u' || TempArray[i] == 'e')
							{
								if((TempArray[i+1] == 'i' || TempArray[i+1] == 'o' || TempArray[i+1] == 'u' || TempArray[i+1] == 'e') && (i+1 < Length))
									end = i+1;
								else
									end=i;
							}
						}
						if(TempArray[end] == ' ' || TempArray[end] == '\n')
							i=end;
						
						break;
					case 'u' :
						Trace = 5;
						start=i;
						i++;
						
						if(TempArray[i] == 'u')
							i=i+1;
						
						do
						{
							i++;
						}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)) && ((TempArray[i] != '\n') && (i < Length)));
						end=i-1;

						if(end>=Length);
						else
						{
							if(TempArray[i] == 'a')
							{
								if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
									end = i+2;
								else if(TempArray[i+1] == 'a' || TempArray[i+1] == 'i' || TempArray[i+1] == 'u')
									end = i+1;
								else
									end = i;
							}
					
							if(TempArray[i] == 'i' || TempArray[i] == 'o' || TempArray[i] == 'u' || TempArray[i] == 'e')
							{
								if((TempArray[i+1] == 'i' || TempArray[i+1] == 'o' || TempArray[i+1] == 'u' || TempArray[i+1] == 'e') && (i+1 < Length))
									end = i+1;
								else
									end=i;
							}
						}
						if(TempArray[end] == ' ' || TempArray[end] == '\n')
						{
							i=end;
							AfxMessageBox("In space");
						}
						break;
				}
			}
			
			if(end==Length)
				end=end-1;
			m_cToConcatenate = new char [end-start+1];
			k=0;
				for(j=start;j<=end;j++)
			{
				
				if(isalnum(TempArray[j]))
				{
					//to remove consecutive vowels
					if(j+1 <= end && (TempArray[j] == 'a' && TempArray[j+1] == 'a'))
					{
						if(j+3 <= end && ((TempArray[j+2] == 'i' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'u' && TempArray[j+3] == 'u') || (TempArray[j+2] == 'e' && TempArray[j+3] == 'e') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'o' && TempArray[j+3] == 'o') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'u')))
							j=j+2;
						else if(j+2 <= end && (TempArray[j+2] == 'e' || TempArray[j+2] == 'o' || TempArray[j+2] == 'i' || TempArray[j+2] == 'u'))
							j=j+2;
					}
					else if(j+1 <= end && (TempArray[j] == 'a' && (TempArray[j+1] == 'e' || TempArray[j+1] == 'o')))
						j=j+1;
					else if(j+2 <= end && (TempArray[j] == 'a' && ((TempArray[j+1] == 'i' && TempArray[j+2] == 'i') || (TempArray[j+1] == 'u' && TempArray[j+2] == 'u') || (TempArray[j+1] == 'e' && TempArray[j+2] == 'e') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'i') || (TempArray[j+1] == 'o' && TempArray[j+2] == 'oo') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'u') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'a'))))
						j=j+1;
					if(j+1 <= end && (TempArray[j] == 'i' && TempArray[j+1] == 'i'))
					{
						if(j+3 <= end && ((TempArray[j+2] == 'a' && TempArray[j+3] == 'a') || (TempArray[j+2] == 'u' && TempArray[j+3] == 'u') || (TempArray[j+2] == 'e' && TempArray[j+3] == 'e') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'o' && TempArray[j+3] == 'o') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'u')) )
							j=j+2;
						else if(j+2 <= end && (TempArray[j+2] == 'a' || TempArray[j+2] == 'i' || TempArray[j+2] == 'u' || TempArray[j+2] == 'e' || TempArray[j+2] == 'o'))
							j=j+2;
					}
					else if(TempArray[j] == 'i')
					{
						if(j+2 <= end && ((TempArray[j+1] == 'a' && TempArray[j+2] == 'a') || (TempArray[j+1] == 'u' && TempArray[j+2] == 'u') || (TempArray[j+1] == 'e' && TempArray[j+2] == 'e') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'i') || (TempArray[j+1] == 'o' && TempArray[j+2] == 'o') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'u')))
							j=j+1;
						else if(j+1 <= end && (TempArray[j+1] == 'a' || TempArray[j+1] == 'u' || TempArray[j+1] == 'e' || TempArray[j+1] == 'o'))
							j=j+1;
					}
					if(j+1 <= end && (TempArray[j] == 'u' && TempArray[j+1] == 'u'))
					{
						if(j+3 <= end && ((TempArray[j+2] == 'a' && TempArray[j+3] == 'a') || (TempArray[j+2] == 'u' && TempArray[j+3] == 'u') || (TempArray[j+2] == 'e' && TempArray[j+3] == 'e') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'o' && TempArray[j+3] == 'o') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'u')) )
							j=j+2;
						else if(j+2 <= end && (TempArray[j+2] == 'a' || TempArray[j+2] == 'i' || TempArray[j+2] == 'u' || TempArray[j+2] == 'e' || TempArray[j+2] == 'o'))
							j=j+2;
					}
					else if(TempArray[j] == 'u')
					{
						if(j+2 <= end && ((TempArray[j+1] == 'a' && TempArray[j+2] == 'a') || (TempArray[j+1] == 'u' && TempArray[j+2] == 'u') || (TempArray[j+1] == 'e' && TempArray[j+2] == 'e') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'i') || (TempArray[j+1] == 'o' && TempArray[j+2] == 'o') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'u')))
							j=j+1;
						else if(j+1 <= end && (TempArray[j+1] == 'a' || TempArray[j+1] == 'i' || TempArray[j+1] == 'e' || TempArray[j+1] == 'o'))
							j=j+1;
					}
					if(j+1 <= end && (TempArray[j] == 'e' && TempArray[j+1] == 'e'))
					{
						if(j+3 <= end && ((TempArray[j+2] == 'a' && TempArray[j+3] == 'a') || (TempArray[j+2] == 'u' && TempArray[j+3] == 'u') || (TempArray[j+2] == 'e' && TempArray[j+3] == 'e') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'o' && TempArray[j+3] == 'o') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'u')) )
							j=j+2;
						else if(j+2 <= end && (TempArray[j+2] == 'a' || TempArray[j+2] == 'i' || TempArray[j+2] == 'u' || TempArray[j+2] == 'e' || TempArray[j+2] == 'o'))
							j=j+2;
					}
					else if(TempArray[j] == 'e')
					{
						if(j+2 <= end && ((TempArray[j+1] == 'a' && TempArray[j+2] == 'a') || (TempArray[j+1] == 'u' && TempArray[j+2] == 'u') || (TempArray[j+1] == 'e' && TempArray[j+2] == 'e') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'i') || (TempArray[j+1] == 'o' && TempArray[j+2] == 'o') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'u')))
							j=j+1;
						else if(j+1 <= end && (TempArray[j+1] == 'a' || TempArray[j+1] == 'i' || TempArray[j+1] == 'u' || TempArray[j+1] == 'o'))
							j=j+1;
					}
					if(j+1 <= end && (TempArray[j] == 'o' && TempArray[j+1] == 'o'))
					{
						if(j+3 <= end && ((TempArray[j+2] == 'a' && TempArray[j+3] == 'a') || (TempArray[j+2] == 'u' && TempArray[j+3] == 'u') || (TempArray[j+2] == 'e' && TempArray[j+3] == 'e') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'o' && TempArray[j+3] == 'o') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'u')) )
							j=j+2;
						else if(j+2 <= end && (TempArray[j+2] == 'a' || TempArray[j+2] == 'i' || TempArray[j+2] == 'u' || TempArray[j+2] == 'e' || TempArray[j+2] == 'o'))
							j=j+2;
					}
					else if(TempArray[j] == 'o')
					{
						if(j+2 <= end && ((TempArray[j+1] == 'a' && TempArray[j+2] == 'a') || (TempArray[j+1] == 'u' && TempArray[j+2] == 'u') || (TempArray[j+1] == 'e' && TempArray[j+2] == 'e') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'i') || (TempArray[j+1] == 'o' && TempArray[j+2] == 'o') || (TempArray[j+1] == 'a' && TempArray[j+2] == 'u')))
							j=j+1;
						else if(j+1 <= end && (TempArray[j+1] == 'a' || TempArray[j+1] == 'i' || TempArray[j+1] == 'u' || TempArray[j+1] == 'e'))
							j=j+1;
					}
					if(j+1 <= end && (TempArray[j] == 'a' && TempArray[j+1] == 'i'))
					{
						if(j+3 <= end && ((TempArray[j+2] == 'a' && TempArray[j+3] == 'a') || (TempArray[j+2] == 'i' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'u' && TempArray[j+3] == 'u') || (TempArray[j+2] == 'e' && TempArray[j+3] == 'e') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'o' && TempArray[j+3] == 'o') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'u')))
							j=j+2;
						else if(j+2 <= end &&(TempArray[j+2] == 'a' || TempArray[j+2] == 'i' || TempArray[j+2] == 'u' || TempArray[j+2] == 'e' || TempArray[j+2] == 'o'))
							j=j+2;

					}
					if(j+1 <= end && (TempArray[j] == 'a' && TempArray[j+1] == 'u'))
					{
						if(j+3 <= end && ((TempArray[j+2] == 'a' && TempArray[j+3] == 'a') || (TempArray[j+2] == 'i' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'u' && TempArray[j+3] == 'u') || (TempArray[j+2] == 'e' && TempArray[j+3] == 'e') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'i') || (TempArray[j+2] == 'o' && TempArray[j+3] == 'o') || (TempArray[j+2] == 'a' && TempArray[j+3] == 'u')))
							j=j+2;
						else if(j+2 <= end &&(TempArray[j+2] == 'a' || TempArray[j+2] == 'i' || TempArray[j+2] == 'u' || TempArray[j+2] == 'e' || TempArray[j+2] == 'o'))
							j=j+2;

					}
					m_cToConcatenate[k] = TempArray[j];
					k++;
				}
			}
		
			m_cToConcatenate[k]='\0';
			
			int size = ChangeFileName(k);
			if(size != 0)
			{
				fprintf(parse,"%s ",m_sFileName);
				CountUnit++;
			}
		}while(i<Length-1);

		if(DOT == 1)
		{
//			fprintf(parse,"x ");
			fprintf(parse,"xd ");
			CUnitArray[index]=CountUnit;
			if(index == 0)
				CSpace[index2]=CountSpace+2;
			else
				CSpace[index2]=CountSpace+2;
			index2++;
			index++;
			DOT = 0;
			CountUnit++;
					
		}
		else if(QUEST == 1)
		{
			fprintf(parse,"xq ");
			CUnitArray[index]=CountUnit;
			if(index == 0)
				CSpace[index2]=CountSpace+2;
			else
				CSpace[index2]=CountSpace+2;
			index2++;
			index++;
			CountUnit++;
			QUEST=0;
			
		}
		else if(EXCLAIM == 1)
		{
			fprintf(parse,"xe ");
			CUnitArray[index]=CountUnit;
			index++;
			CountUnit++;
			CSpace[index2]=CountSpace+2;
			index2++;
			EXCLAIM=0;
		
		}
		else if(COMMA == 1)
		{
			fprintf(parse,"xc ");
			CUnitArray[index]=CountUnit;
			index++;
			CountUnit++;
			CSpace[index2]=CountSpace+2;
			index2++;
			COMMA=0;
		
		}
		TRACE("\n countword = %d",countword);
		
	}while(l<Total_Length-1);
	fprintf(parse,"y");
	fclose(parse);
	//TRACE("\nCount Unit = %d",CountUnit);
	/*for(i=0;i<index;i++)
		TRACE(" CUnit [i] = %d",CUnitArray[i]);
	for(i=0;i<index2;i++)
		TRACE(" CSpace [i] = %d",CSpace[i]);*/
	for(i=0;i<index2;i++)
		TRACE(" CSpace [i] = %d,CUnitArray [i] = %d",CSpace[i],CUnitArray[i]);
	//delete [] m_cToConcatenate;
	TRACE("\nGoing out of Parse . . .");
	return;
}



int CDoc::ChangeFileName(int length)
{
	if(length < 1 ) return 0;
	char *target;
	target = new char [5*length];
	int i=0;
	int j=0;
	while(i<length)
	{
		if(m_cToConcatenate[i] == 'a' || m_cToConcatenate[i] == 'A')
		{
			target[j] = 'a';
			i++;
			j++;
			if(m_cToConcatenate[i] == 'u' || m_cToConcatenate[i] == 'U')
			{
				target[j] = 'u';
				i+=1;
				j++;
			}
			if(m_cToConcatenate[i] == 'i' || m_cToConcatenate[i] == 'I')
			{
				target[j] = 'i';
				i+=1;
				j++;
			}
			if(m_cToConcatenate[i] == 'e' || m_cToConcatenate[i] == 'E')
			{
				target[j] = 'i';
				i+=2;
				j++;
				length--;
			}
			else if(m_cToConcatenate[i] == 'o' || m_cToConcatenate[i] == 'O')
			{
				target[j] = 'u';
				i+=2;
				j++;
				length--;
			}
		}
		else
		{
			target[j] = m_cToConcatenate[i];
			i++;
			j++;
		}
	}
	target[length]='\0';
	char c;
	char strTemp[10] = ".wav";
	char Unit[100];
	int i1=0;
	char u[20] = "database\\";
	/*do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Unit[i1]=c;
		i1++;

	}while(c != '$');*/
	i1=0;
	Unit[i1] = '\0';
	strcat(Unit,u);
	Unit[strlen(Unit)]= '\0';
	strcat(Unit,target);
	Unit[strlen(Unit)]= '\0';
	strcat(Unit,strTemp);
	Unit[strlen(Unit)]= '\0';
	m_sFileName = Unit;
	delete [] target;
	return length;
}

void CDoc::KannadaConcatenate()
{
	int i,j,temp,Space=0,ind=0;
	BOOL flagpresent,flagnext;
	IIScHeader presenthead,nexthead;
	short int presentsignal[10000],nextsignal[10000],presentpitch[10000],nextpitch[10000],*EndSignal;
	FILE *parsed,*presentwave,*nextwave,*target,*missing;
	char present[100],next[100],prescan[100],nextscan[100];
	char Parse[100];
	char c;
	SizeOfSentance = 0;
	int i1=0;
	char p[20] = "parse1.iis";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Parse[i1]=c;
		i1++;

	}while(c != '$');
	Parse[i1] = '\0';
	
	strcat(Parse,p);
	
	Parse[strlen(Parse)]= '\0';	
	char Missing[100];
	char M[20] = "missing.txt";
	i1=0;
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Missing[i1]=c;
		i1++;

	}while(c != '$');
	Missing[i1] = '\0';
	strcat(Missing,M);
	Missing[strlen(Missing)]= '\0';
	char X[100];
	//X=new char [100];
	char x1[20] = "x";
	i1=0;
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		X[i1]=c;
		i1++;

	}while(c != '$');
	X[i1] = '\0';
	strcat(X,x1);
	X[strlen(X)]= '\0';

	CFile file;
	VERIFY(file.Open(Parse,CFile::modeRead));
	//parsed = fopen(Parse,"rt");
	missing = fopen(Missing,"at");
	target = fopen(X,"wb");
	int size=0;
	int duration = 0,Unit=1;
	int len_present;
	int pitchmark[300];
	//fscanf(parsed,"%s ",&prescan);
	file.Read(&prescan[0],sizeof(char));
	i=0;
	while(prescan[i] != ' ')
	{
		i++;
		file.Read(&prescan[i],sizeof(char));
	}
	prescan[i] = '\0';

	i1=0;
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		present[i1]=c;
		i1++;

	}while(c != '$');
	present[i1] = '\0';
	strcat(present,prescan);
	int flag_checkdot=0;
	
	
	//TRACE(" \nCunitArray = %d",CUnitArray[ind]);
	while(1)
	{
		//fscanf(parsed,"%s ",&nextscan);
		file.Read(&nextscan[0],sizeof(char));
		i=0;
		while(nextscan[i] != ' ')
		{
			i++;
			file.Read(&nextscan[i],sizeof(char));
		}
		nextscan[i] = '\0';
		i1=0;
		next[i1]='\0';
		do
		{
			c = Path.GetAt(i1);
			if(c == '$')
				break;
			next[i1]=c;
			i1++;
	
		}while(c != '$');
		next[i1] = '\0';
		strcat(next,nextscan);
		Unit++;

		// Last Unit
		if(strcmp(nextscan,"y") == 0 || strcmp(nextscan,"x") == 0 || strcmp(nextscan,"xd") == 0 || strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xc") == 0 || strcmp(nextscan,"xd") == 0 ||strcmp(nextscan,"xe") == 0)
		{

			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
			{
				TRACE(" \nNot Present - 1 **** %s" ,present);
				
			}
			else
			{
			
				fscanf(presentwave,"%s ",&presenthead.FileID);
				fscanf(presentwave,"%d ",&presenthead.junk);
				fscanf(presentwave,"%d ",&presenthead.junk1);
				fscanf(presentwave,"%u ",&presenthead.LanguageID);
				fscanf(presentwave,"%u ",&presenthead.BasicUnit);
				fscanf(presentwave,"%d ",&presenthead.DataLength);
				fscanf(presentwave,"%d ",&presenthead.AvgPitch);
				fscanf(presentwave,"%d ",&presenthead.LSegment);
				fscanf(presentwave,"%d ",&presenthead.RSegment);
				fscanf(presentwave,"%d\n",&presenthead.LengthofPitchMarks);
				//presentsignal = new short int [presenthead.DataLength];
				for(i=0;i<10000;i++)
					presentsignal[i]=0;
				for(i=0;i<1000;i++)
					presentpitch[i]=0;
				for(i=0;i<presenthead.DataLength;i++)
					fscanf(presentwave,"%d ",&presentsignal[i]);

				for(i=0;i<presenthead.LengthofPitchMarks;i++)
				{
					fscanf(presentwave,"%d ",&temp);
					presentpitch[temp] = 1;
				}
				//TRACE(" Unit = %d, CunitArray[ind] = %d",Unit,CUnitArray[ind]+1);
					for(i=presenthead.LSegment;i<presenthead.DataLength;i++)
						fwrite(&presentsignal[i],sizeof(short int),1,target);
					
					size = size+presenthead.DataLength-presenthead.LSegment;
					TRACE("Size in last = %d",size);
				
			}
			if(strcmp(nextscan,"y") == 0)
			{
				j=0;
				for(i=0;i<4000;i++)
					fwrite(&j,sizeof(short int),1,target);
				size=size+4000;
				break;
			}
			else if(strcmp(nextscan,"xd") == 0 || strcmp(nextscan,"xc") == 0 || strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xe") == 0)
			{
				strcpy(prescan,"x");
				Unit++;
				if( Unit == CUnitArray[ind]+1)
					ind++;
				
				j=0;
				if(strcmp(nextscan,"xc") == 0 )
				{
					for(i=0;i<4000;i++)
					fwrite(&j,sizeof(short int),1,target);
					size=size+4000;
				}
				else 
				{	
					
					if(flag_checkdot == 1)
					{
						flag_checkdot=0;
					
					}
					else
					{

						for(i=0;i<8000;i++)
							fwrite(&j,sizeof(short int),1,target);
						size=size+8000;
					}
					
				}
				//fscanf(parsed,"%s ",&nextscan);
				file.Read(&nextscan[0],sizeof(char));
				i=0;
				while(nextscan[i] != ' ')
				{
					i++;
					file.Read(&nextscan[i],sizeof(char));
				}
				nextscan[i] = '\0';
				i1=0;
				next[i1]='\0';
				do
				{
					c = Path.GetAt(i1);
					if(c == '$')
						break;
					next[i1]=c;
					i1++;
	
				}while(c != '$');
				next[i1] = '\0';
				strcat(next,nextscan);
				if(strcmp(nextscan,"y") == 0)
					break;
				continue;
			}
			else
			{
				strcpy(present,next);
				strcpy(prescan,nextscan);
				continue;
			}
			if(presentwave != NULL)
				fclose(presentwave);
		}

		// First Unit
		if(strcmp(prescan,"x") == 0)
		{

			j=0;
			
			for(i=0;i<0;i++)
				fwrite(&j,sizeof(short int),1,target);
			size=size+0;
			strcpy(present,next);
			strcpy(prescan,nextscan);
			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
			{
				fprintf(missing,"\n%s",present);
				TRACE("\n Not Present  - 2 ****** %s", present);
					
			
			}
			else
			{
				flag_checkdot=1;
				fscanf(presentwave,"%s ",&presenthead.FileID);
				fscanf(presentwave,"%d ",&presenthead.junk);
				fscanf(presentwave,"%d ",&presenthead.junk1);
				fscanf(presentwave,"%u ",&presenthead.LanguageID);
				fscanf(presentwave,"%u ",&presenthead.BasicUnit);
				fscanf(presentwave,"%d ",&presenthead.DataLength);
				fscanf(presentwave,"%d ",&presenthead.AvgPitch);
				fscanf(presentwave,"%d ",&presenthead.LSegment);
				fscanf(presentwave,"%d ",&presenthead.RSegment);
				fscanf(presentwave,"%d\n",&presenthead.LengthofPitchMarks);
				//presentsignal = new short int [presenthead.DataLength];
				//presentpitch = new short int [presenthead.DataLength];
				for(i=0;i<10000;i++)
					presentsignal[i]=0;
				for(i=0;i<10000;i++)
					presentpitch[i]=0;
				for(i=0;i<presenthead.DataLength;i++)
					fscanf(presentwave,"%d ",&presentsignal[i]);

				if(presenthead.BasicUnit != 1 || presenthead.BasicUnit != 3 || presenthead.BasicUnit != 7)
				{
					//delete [] PM ;
					//PM = new short int [100000];
						for(i=0;i<presenthead.LSegment;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+presenthead.LSegment;
						//TRACE("\n Size in first = %d",size);
					
					
				}
			}
			strcpy(present,next);
			strcpy(prescan,nextscan);
			if(presentwave != NULL)
				fclose(presentwave);
			continue;
		}
		
		//Middle Unit

		if(strcmp(prescan,"x") != 0 && strcmp(nextscan,"x") != 0 && strcmp(prescan,"y") != 0 && strcmp(nextscan,"y") != 0)
		{
			
			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
			{
				fprintf(missing,"\n%s",present);
				TRACE("\n Not Present - 3 ******** %s", present);
			
				flagpresent = 0;
			}
			else
			{
			
				flag_checkdot=0;
				flagpresent = 1;				
				fscanf(presentwave,"%s ",&presenthead.FileID);
				fscanf(presentwave,"%d ",&presenthead.junk);
				fscanf(presentwave,"%d ",&presenthead.junk1);
				fscanf(presentwave,"%u ",&presenthead.LanguageID);
				fscanf(presentwave,"%u ",&presenthead.BasicUnit);
				fscanf(presentwave,"%d ",&presenthead.DataLength);
				fscanf(presentwave,"%d ",&presenthead.AvgPitch);
				fscanf(presentwave,"%d ",&presenthead.LSegment);
				fscanf(presentwave,"%d ",&presenthead.RSegment);
				fscanf(presentwave,"%d\n",&presenthead.LengthofPitchMarks);
				//presentsignal = new short int [presenthead.DataLength];
				//presentpitch = new short int [presenthead.DataLength];
				for(i=0;i<10000;i++)
					presentsignal[i]=0;
				for(i=0;i<10000;i++)
					presentpitch[i]=0;
				for(i=0;i<presenthead.DataLength;i++)
					fscanf(presentwave,"%d ",&presentsignal[i]);

				for(i=0;i<presenthead.LengthofPitchMarks;i++)
				{
					fscanf(presentwave,"%d ",&temp);
					presentpitch[temp] = 1;
				}
			}

			nextwave = fopen(next,"rb");
			if(nextwave == NULL)
			{
				fprintf(missing,"\n%s",next);
				TRACE("\n Not Present - 4 ******** %s", next);
			
				flagnext=0;
			}
			else
			{
				flagnext=1;
				fscanf(nextwave,"%s ",&nexthead.FileID);
				fscanf(nextwave,"%d ",&nexthead.junk);
				fscanf(nextwave,"%d ",&nexthead.junk1);
				fscanf(nextwave,"%u ",&nexthead.LanguageID);
				fscanf(nextwave,"%u ",&nexthead.BasicUnit);
				fscanf(nextwave,"%d ",&nexthead.DataLength);
				fscanf(nextwave,"%d ",&nexthead.AvgPitch);
				fscanf(nextwave,"%d ",&nexthead.LSegment);
				fscanf(nextwave,"%d ",&nexthead.RSegment);
				fscanf(nextwave,"%d\n",&nexthead.LengthofPitchMarks);

				//nextsignal = new short int [nexthead.DataLength];
				//nextpitch = new short int [nexthead.DataLength];
				for(i=0;i<10000;i++)
					nextsignal[i]=0;
				for(i=0;i<10000;i++)
					nextpitch[i]=0;
				
				for(i=0;i<nexthead.DataLength;i++)
					fscanf(nextwave,"%d ",&nextsignal[i]);
				
				for(i=0;i<nexthead.LengthofPitchMarks;i++)
				{
					fscanf(nextwave,"%d ",&temp);
					nextpitch[temp] = 1;
				}
			}


			strcpy(ToDuration,present);
			
			int duration = DetectDuration();
			int tempduration=0;
		

			if(flagpresent == 1)
			{
		
				if(presenthead.BasicUnit == 2)
				{
					
					if(duration/2 < presenthead.DataLength-presenthead.LSegment)
						tempduration = duration/2;
					else 
						tempduration = presenthead.DataLength-presenthead.LSegment;
					
					i=0;
					while(1)
					{
						if(presentpitch[i] ==1 && i>presenthead.LSegment+tempduration)
						{
							tempduration=i-presenthead.LSegment;
							break;
						}
						i++;
						//Modified by me
						if(i >= presenthead.DataLength/2)
							break;
					}
					
						for(i=presenthead.LSegment;i<presenthead.LSegment+tempduration;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+tempduration;
						TRACE("\n Size in middle = %d",size);
						
				}
				
				if(presenthead.BasicUnit == 4 || presenthead.BasicUnit == 5 || presenthead.BasicUnit == 6)
				{
				
					
						for(i=presenthead.LSegment;i<presenthead.RSegment;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+presenthead.RSegment-presenthead.LSegment;
					
					
					if(duration/2 < presenthead.DataLength-presenthead.RSegment)
						tempduration = duration/2;
					else 
						tempduration = presenthead.DataLength-presenthead.RSegment;

					i=0;
					while(1)
					{
						if(presentpitch[i] ==1 && i>presenthead.RSegment+tempduration)
						{
							tempduration=i-presenthead.RSegment;
							break;
						}
						i++;
					}
				
					
						for(i=presenthead.RSegment;i<presenthead.RSegment+tempduration;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+tempduration;
						TRACE("\n Size in middle = %d",size);
					
					
				}
				flagpresent=0;
			}
			tempduration=0;
			if(flagnext == 1)
			{
				if(duration/2 < nexthead.LSegment)
					tempduration = duration/2;
				else 
					tempduration = nexthead.LSegment;
						
				i=0;
				while(1)
				{
					if(nextpitch[i] ==1 && i>nexthead.LSegment-tempduration)
					{
						tempduration=nexthead.LSegment-i;
						break;
					}
					i++;
				}
				
					for(i=nexthead.LSegment-tempduration;i<nexthead.LSegment;i++)
						fwrite(&nextsignal[i],sizeof(short int),1,target);
					size = size+tempduration;
					//TRACE("\n Size in middle next  = %d",size);
				
				flagnext=0;
			}
			//TRACE("CSpace = %d, Cunit = %d, Unit = %d\n",CSpace[ind],CUnitArray[ind],Unit);
			strcpy(present,next);
			strcpy(prescan,nextscan);
			if(presentwave != NULL)
				fclose(presentwave);
			if(nextwave != NULL)
				fclose(nextwave);
			
		}
	}
	SizeOfSentance =  size;
	fcloseall();
	//TRACE("\n Space = %d, Unit = %d",Space,Unit);
	TRACE("\nOut of Concatenate %d\n",SizeOfSentance);
	WriteWaveFile();


}

/*void CDoc::KannadaConcatenate()
{
int i,j,temp,Space=0,ind=0;
	BOOL flagpresent,flagnext;
	IIScHeader presenthead,nexthead;
	short int presentsignal[10000],nextsignal[10000],presentpitch[10000],nextpitch[10000],*EndSignal;
	FILE *parsed,*presentwave,*nextwave,*target,*missing;
	char present[100],next[100];
	char Parse[100];
	char c;
	int i1=0;
	char p[20] = "parse1.iis";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Parse[i1]=c;
		i1++;

	}while(c != '$');
	Parse[i1] = '\0';
	
	strcat(Parse,p);
	
	Parse[strlen(Parse)]= '\0';	
	char Missing[100];
	char M[20] = "missing.txt";
	i1=0;
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Missing[i1]=c;
		i1++;

	}while(c != '$');
	Missing[i1] = '\0';
	strcat(Missing,M);
	Missing[strlen(Missing)]= '\0';
	char X[100];
	//X=new char [100];
	char x1[20] = "x";
	i1=0;
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		X[i1]=c;
		i1++;

	}while(c != '$');
	X[i1] = '\0';
	strcat(X,x1);
	X[strlen(X)]= '\0';


	parsed = fopen(Parse,"rt");
	missing = fopen(Missing,"at");
	target = fopen(X,"wb");
	int size=0;
	int duration = 0,Unit=1;
	int len_present;
	int pitchmark[300];
	fscanf(parsed,"%s ",&present);
		
	while(1)
	{
		fscanf(parsed,"%s ",&next);
		
		// Last Unit
		if(strcmp(next,"y") == 0 || strcmp(next,"x") == 0 || strcmp(next,"xd") == 0 || strcmp(next,"xq") == 0 || strcmp(next,"xc") == 0 || strcmp(next,"xd") == 0 ||strcmp(next,"xe") == 0)
		{
			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
				TRACE(" \nNot Present - 1 **** %s" ,present);
			else
			{
				fscanf(presentwave,"%s ",&presenthead.FileID);
				fscanf(presentwave,"%d ",&presenthead.junk);
				fscanf(presentwave,"%d ",&presenthead.junk1);
				fscanf(presentwave,"%u ",&presenthead.LanguageID);
				fscanf(presentwave,"%u ",&presenthead.BasicUnit);
				fscanf(presentwave,"%d ",&presenthead.DataLength);
				fscanf(presentwave,"%d ",&presenthead.AvgPitch);
				fscanf(presentwave,"%d ",&presenthead.LSegment);
				fscanf(presentwave,"%d ",&presenthead.RSegment);
				fscanf(presentwave,"%d\n",&presenthead.LengthofPitchMarks);
				//presentsignal = new short int [presenthead.DataLength];

				for(i=0;i<presenthead.DataLength;i++)
					fscanf(presentwave,"%d ",&presentsignal[i]);
				TRACE("In last");
				for(i=presenthead.LSegment;i<presenthead.DataLength;i++)
					fwrite(&presentsignal[i],sizeof(short int),1,target);
				size = size+presenthead.DataLength-presenthead.LSegment;
			}
			if(strcmp(next,"y") == 0)
			{
				j=0;
				for(i=0;i<500;i++)
					fwrite(&j,sizeof(short int),1,target);
				size=size+500;
				break;
			}
			else if(strcmp(next,"xd") == 0 || strcmp(next,"xc") == 0 || strcmp(next,"xq") == 0 || strcmp(next,"xe") == 0)
			{
				strcpy(present,"x");
				Unit++;
				if( Unit == CUnitArray[ind]+1)
					ind++;
				
				j=0;
				if(strcmp(next,"xc") == 0 )
				{
					for(i=0;i<4000;i++)
					fwrite(&j,sizeof(short int),1,target);
					size=size+4000;
				}
				else
				{	for(i=0;i<8000;i++)
						fwrite(&j,sizeof(short int),1,target);
					size=size+8000;
				}
				fscanf(parsed,"%s ",&next);
				if(strcmp(next,"y") == 0)
					break;
				continue;
			}
			else
			{
				strcpy(present,next);
				continue;
			}
		}

		// First Unit
		if(strcmp(present,"x") == 0)
		{
			j=0;
			//for(i=0;i<0;i++)
			//	fwrite(&j,sizeof(short int),1,target);
			size=size+0;
			strcpy(present,next);
			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
			{
				fprintf(missing,"\n%s",present);
				TRACE("\n Not Present  - 2 ****** %s", present);
			}
			else
			{

				fscanf(presentwave,"%s ",&presenthead.FileID);
				fscanf(presentwave,"%d ",&presenthead.junk);
				fscanf(presentwave,"%d ",&presenthead.junk1);
				fscanf(presentwave,"%u ",&presenthead.LanguageID);
				fscanf(presentwave,"%u ",&presenthead.BasicUnit);
				fscanf(presentwave,"%d ",&presenthead.DataLength);
				fscanf(presentwave,"%d ",&presenthead.AvgPitch);
				fscanf(presentwave,"%d ",&presenthead.LSegment);
				fscanf(presentwave,"%d ",&presenthead.RSegment);
				fscanf(presentwave,"%d\n",&presenthead.LengthofPitchMarks);
				//presentsignal = new short int [presenthead.DataLength];
				//presentpitch = new short int [presenthead.DataLength];
				for(i=0;i<presenthead.DataLength;i++)
					fscanf(presentwave,"%d ",&presentsignal[i]);
				TRACE("In first");
				if(presenthead.BasicUnit != 1 || presenthead.BasicUnit != 3 || presenthead.BasicUnit != 7)
				{
					for(i=0;i<presenthead.LSegment;i++)
						fwrite(&presentsignal[i],sizeof(short int),1,target);
					size = size+presenthead.LSegment;
				}
			}
			strcpy(present,next);
			continue;
		}
		
		//Middle Unit

		if(strcmp(present,"x") != 0 && strcmp(next,"x") != 0 && strcmp(present,"y") != 0 && strcmp(next,"y") != 0)
		{
			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
			{
				fprintf(missing,"\n%s",present);
				TRACE("\n Not Present - 3 ******** %s", present);
				flagpresent = 0;
			}
			else
			{
				flagpresent = 1;				
				fscanf(presentwave,"%s ",&presenthead.FileID);
				fscanf(presentwave,"%d ",&presenthead.junk);
				fscanf(presentwave,"%d ",&presenthead.junk1);
				fscanf(presentwave,"%u ",&presenthead.LanguageID);
				fscanf(presentwave,"%u ",&presenthead.BasicUnit);
				fscanf(presentwave,"%d ",&presenthead.DataLength);
				fscanf(presentwave,"%d ",&presenthead.AvgPitch);
				fscanf(presentwave,"%d ",&presenthead.LSegment);
				fscanf(presentwave,"%d ",&presenthead.RSegment);
				fscanf(presentwave,"%d\n",&presenthead.LengthofPitchMarks);
				//presentsignal = new short int [presenthead.DataLength];
				//presentpitch = new short int [presenthead.DataLength];
				for(i=0;i<presenthead.DataLength;i++)
					fscanf(presentwave,"%d ",&presentsignal[i]);
				for(i=0;i<presenthead.DataLength;i++)
					presentpitch[i]=0;
				for(i=0;i<presenthead.LengthofPitchMarks;i++)
				{
					fscanf(presentwave,"%d ",&temp);
					presentpitch[temp] = 1;
				
				}
			}

			nextwave = fopen(next,"rb");
			if(nextwave == NULL)
			{
				fprintf(missing,"\n%s",next);
				TRACE("\n Not Present - 4 ******** %s", next);
				flagnext=0;
			}
			else
			{
				flagnext=1;
				fscanf(nextwave,"%s ",&nexthead.FileID);
				fscanf(nextwave,"%d ",&nexthead.junk);
				fscanf(nextwave,"%d ",&nexthead.junk1);
				fscanf(nextwave,"%u ",&nexthead.LanguageID);
				fscanf(nextwave,"%u ",&nexthead.BasicUnit);
				fscanf(nextwave,"%d ",&nexthead.DataLength);
				fscanf(nextwave,"%d ",&nexthead.AvgPitch);
				fscanf(nextwave,"%d ",&nexthead.LSegment);
				fscanf(nextwave,"%d ",&nexthead.RSegment);
				fscanf(nextwave,"%d\n",&nexthead.LengthofPitchMarks);

				//nextsignal = new short int [nexthead.DataLength];
				//nextpitch = new short int [nexthead.DataLength];
				
				for(i=0;i<nexthead.DataLength;i++)
					fscanf(nextwave,"%d ",&nextsignal[i]);
				for(i=0;i<nexthead.DataLength;i++)
					nextpitch[i]=0;
				
				for(i=0;i<nexthead.LengthofPitchMarks;i++)
				{
					fscanf(nextwave,"%d ",&temp);
					nextpitch[temp] = 1;
				}
			}

			strcpy(ToDuration,present);
			int duration = DetectDuration();
			int tempduration=0;
			int initial_p = 0;
			int final_p = 0;
			int minimum = 0;
			int min_ind = 0;
			int min_ene = 0;
			int min_eind = 0;
			static int div_part = 8;
			int energy[8];
				

			if(flagpresent == 1)
			{
				if(presenthead.BasicUnit == 2)
				{
					if(duration/2 < presenthead.DataLength-presenthead.LSegment)
						tempduration = duration/2;
					else 
						tempduration = presenthead.DataLength-presenthead.LSegment;
					i=0;
					initial_p = 0;
					final_p = 0;
					minimum = 0;
					//for(i=0;i<presenthead.DataLength/2;i++)
					//	TRACE("i = %d, presentpitch = %d\t",i,presentpitch[i]);
					while(1)
					{
						
						if(presentpitch[i] == 1 && i>presenthead.LSegment+tempduration)
						{
							initial_p=i;
							TRACE("onitial_p = %d",initial_p);
							i++;
							while(presentpitch[i] != 1 && i>presenthead.LSegment+tempduration && i<presenthead.DataLength)
							{
								i++;
							}
							final_p = i;	
							TRACE("final_p = %d",final_p);
//Fine till here
							for(int z=0;z<div_part;z++)
								energy[z] = 0;
							z=0;
							for(int m = initial_p; m<final_p;m+=(final_p-initial_p)/div_part)
							{
								for(int p = m;p<m+(final_p-initial_p)/div_part;p++)
									energy[z] = energy[z] + presentsignal[p] * presentsignal[p];
								z++;
							}
							min_ene = energy[0];
							min_eind = 0;
							for(z=0;z<div_part;z++)
								if (min_ene>energy[z])
								{
									min_ene = energy[z];
									min_eind = z;
								}
							minimum = presentsignal[initial_p+min_eind * (final_p-initial_p)/div_part];
							min_ind = initial_p+min_eind * (final_p-initial_p)/div_part;
							for(z = initial_p+min_eind * (final_p-initial_p)/div_part;z<(initial_p+min_eind * (final_p-initial_p)/div_part) + (final_p-initial_p)/div_part;z++)
							{	
								if(minimum<abs(presentsignal[z]))
								{
									minimum = abs(presentsignal[z]);
									min_ind = z;
								}
							}

							tempduration=min_ind-presenthead.LSegment;
							break;
						}
						i++;
					}
					for(i=presenthead.LSegment;i<presenthead.LSegment+tempduration;i++)
						fwrite(&presentsignal[i],sizeof(short int),1,target);

					size = size+tempduration;

				}

				if(presenthead.BasicUnit == 4 || presenthead.BasicUnit == 5 || presenthead.BasicUnit == 6)
				{
					for(i=presenthead.LSegment;i<presenthead.RSegment;i++)
						fwrite(&presentsignal[i],sizeof(short int),1,target);
					size = size+presenthead.RSegment-presenthead.LSegment;

					if(duration/2 < presenthead.DataLength-presenthead.RSegment)
						tempduration = duration/2;
					else 
						tempduration = presenthead.DataLength-presenthead.RSegment;

					i=0;
					initial_p = 0;
					final_p = 0;
					minimum = 0;
					while(1)
					{
						if(presentpitch[i] == 1 && i>presenthead.RSegment+tempduration)
						{
							initial_p=i;
							i++;
							while(presentpitch[i] != 1 && i>presenthead.RSegment+tempduration && i<presenthead.DataLength)
							{
								i++;
							}
							final_p = i;	
							TRACE("\n Init = %d Final = %d",initial_p,final_p);
							for(int z=0;z<div_part;z++)
								energy[z] = 0;
							z=0;
							for(int m = initial_p; m<final_p;m+=(final_p-initial_p)/div_part)
							{
								for(int p = m;p<m+(final_p-initial_p)/div_part;p++)
									energy[z] = energy[z] + presentsignal[p] * presentsignal[p];
								z++;
							}
							min_ene = energy[0];
							min_eind = 0;
							for(z=0;z<div_part;z++)
								if (min_ene>energy[z])
								{
									min_ene = energy[z];
									min_eind = z;
								}
							minimum = presentsignal[initial_p+min_eind * (final_p-initial_p)/div_part];
							min_ind = initial_p+min_eind * (final_p-initial_p)/div_part;
							for(z = initial_p+min_eind * (final_p-initial_p)/div_part;z<(initial_p+min_eind * (final_p-initial_p)/div_part) + (final_p-initial_p)/div_part;z++)
							{	
								if(minimum<abs(presentsignal[z]))
								{
									minimum = abs(presentsignal[z]);
									min_ind = z;
								}
							}

							tempduration=min_ind-presenthead.RSegment;

							break;
						}
						i++;
					}
					for(i=presenthead.RSegment;i<presenthead.RSegment+tempduration;i++)
						fwrite(&presentsignal[i],sizeof(short int),1,target);

					size = size+tempduration;
				}
				flagpresent=0;
			}
			tempduration=0;
			if(flagnext == 1)
			{
				if(duration/2 < nexthead.LSegment)
					tempduration = duration/2;
				else 
					tempduration = nexthead.LSegment;
						
				i=0;
					initial_p = 0;
					final_p = 0;
					minimum = 0;
					while(1)
					{
						if(nextpitch[i] == 1 && i>nexthead.LSegment-tempduration)
						{
							initial_p=i;
							i++;
							while(nextpitch[i] != 1 && i>nexthead.LSegment-tempduration && i<nexthead.DataLength)
							{
								i++;
							}
							final_p = i;	
							TRACE("\n Init = %d Final = %d",initial_p,final_p);
							for(int z=0;z<div_part;z++)
								energy[z] = 0;
							z=0;
							for(int m = initial_p; m<final_p;m+=(final_p-initial_p)/div_part)
							{
								for(int p = m;p<m+(final_p-initial_p)/div_part;p++)
									energy[z] = energy[z] + nextsignal[p] * nextsignal[p];
								z++;
							}
							min_ene = energy[0];
							min_eind = 0;
							for(z=0;z<div_part;z++)
								if (min_ene>energy[z])
								{
									min_ene = energy[z];
									min_eind = z;
								}
							minimum = nextsignal[initial_p+min_eind * (final_p-initial_p)/div_part];
							min_ind = initial_p+min_eind * (final_p-initial_p)/div_part;
							for(z = initial_p+min_eind * (final_p-initial_p)/div_part;z<(initial_p+min_eind * (final_p-initial_p)/div_part) + (final_p-initial_p)/div_part;z++)
							{	
								if(minimum<abs(nextsignal[z]))
								{
									minimum = abs(nextsignal[z]);
									min_ind = z;
								}
							}
							tempduration=nexthead.LSegment - min_ind;
						break;
					}
					i++;
				}

				TRACE("\n\n Next Temp Duration = %d ",tempduration);
				
				for(i=nexthead.LSegment-tempduration;i<nexthead.LSegment;i++)
					fwrite(&nextsignal[i],sizeof(short int),1,target);
				size = size+tempduration;
				flagnext=0;
			}
			
			strcpy(present,next);
		}
	}
	SizeOfSentance = size;
	fcloseall();
	TRACE("\nOut of Concatenate %d\n",SizeOfSentance);
	WriteWaveFile();
}*/


void CDoc::WriteWaveFile()
{
	
	char temp[100];
	//temp = new char [100];
	//t = new char [20];
	char c;
	int i1=0;
	char t[20]="temp.wav";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		temp[i1]=c;
		i1++;

	}while(c != '$');
	temp[i1] = '\0';
	
	strcat(temp,t);
	
	temp[strlen(temp)]= '\0';	
	
	remove(temp);
	FILE *in,*out,*outg;
	short int transfer;
	WAVEheader head;
	char a[100];
	i1=0;
	//a = new char [100];
	//a1 = new char [20];
	char a1[20] = "a.wav";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		a[i1]=c;
		i1++;

	}while(c != '$');
	a[i1] = '\0';
	
	strcat(a,a1);
	
	a[strlen(a)]= '\0';	
	
	char tempg[100];
	//tempg=new char [100];
	//tg = new char [20];
	i1=0;
	char tg[20] = "tempg.wav";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		tempg[i1]=c;
		i1++;

	}while(c != '$');
	tempg[i1] = '\0';
	
	strcat(tempg,tg);
	
	tempg[strlen(tempg)]= '\0';	
	
	char x[100];
	//x=new char [100];
	//x1 = new char [20];
	i1=0;
	char x1[]="x";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		x[i1]=c;
		i1++;

	}while(c != '$');
	x[i1] = '\0';
	strcat(x,x1);
	x[strlen(x)]= '\0';	
	
	
	in=fopen(a,"rb");
	fread(&head,sizeof(head),1,in);
	fclose(in);
	
	in=fopen(x,"rb");
	
	head.data_ckSize = SizeOfSentance*2;
	out=fopen(temp,"wb");
	outg=fopen(tempg,"wb");
	fwrite(&head,sizeof(head),1,out);
	head.ckSize=head.data_ckSize+110;
	fwrite(&head,sizeof(head),1,outg);
	
	for(int i=0;i<SizeOfSentance;i++)
	{
		fread(&transfer,sizeof(short int),1,in);
		fwrite(&transfer,sizeof(short int),1,out);
		fwrite(&transfer,sizeof(short int),1,outg);
		transfer = 0;
	}

	fclose(in);
	fclose(out);
	fclose(outg);
	TRACE("\n size of sentence = %d",SizeOfSentance);
	remove(x);
	

}

void CDoc::KannadaSynthesize()
{
 	if(m_strKannadaData.IsEmpty())
	{
		AfxMessageBox("Field is Empty");
		return;
	}
	TRACE("\n Kannada synthesize");
	KannadaParse();


	TRACE("\nm_strKannada = %s, flag = %d",m_strKannadaData,Flagnumber);
	
	/*if(Flagquit == 1 && Flagnumber == 0)
	{
		AfxMessageBox("Enter Single word");
		Flagquit=0;
		return;
	}*/
	CheckOnce();
	KannadaConcatenate();
	PlaySou();
}

void CDoc::PlaySou() 
{
	char temp[100];
	//temp = new char [100];
	//t = new char [20];
	char c;
	int i1=0;
	char t[20]="temp.wav";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		temp[i1]=c;
		i1++;

	}while(c != '$');
	temp[i1] = '\0';
	strcat(temp,t);
	temp[strlen(temp)]= '\0';	
	
	PlaySound(temp,NULL,SND_FILENAME);
	
}

int CDoc::DetectDuration()
{
	CString str = ToDuration;

	int length = str.GetLength();
	float temp;
	switch(ToDuration[length-5])
	{
		case 'a' : 
					if(ToDuration[length-6] == 'a' || ToDuration[length-6] == 'A')
					{
						temp = (MULTIPLICATION_FACTOR+6) * float(DUR_AA);
						return int(temp);
					}
					else
					{
						temp = MULTIPLICATION_FACTOR * float(DUR_A);
						return int(temp);
					}


		case 'e' :
					if(ToDuration[length-6] == 'e' || ToDuration[length-6] == 'E')
					{
						temp = (MULTIPLICATION_FACTOR+5) * float(DUR_EE);
						return int(temp);
					}
					else
					{
						temp = MULTIPLICATION_FACTOR * float(DUR_E);
						return int(temp);
					}


		case 'i' :
					if(ToDuration[length-6] == 'i' || ToDuration[length-6] == 'I')
					{
						temp = (MULTIPLICATION_FACTOR+5) * float(DUR_II);
						return int(temp);
					}
					else if(ToDuration[length-6] == 'a' || ToDuration[length-6] == 'A')
					{
						temp = MULTIPLICATION_FACTOR * float(DUR_AI);
						return int(temp);
					}
					else
					{
						temp = MULTIPLICATION_FACTOR * float(DUR_I);
						return int(temp);
					}

		case 'o' :
					if(ToDuration[length-6] == 'o' || ToDuration[length-6] == 'O')
					{
						temp = (MULTIPLICATION_FACTOR+5) * float(DUR_OO);
						return int(temp);
					}
					else
					{
						temp = MULTIPLICATION_FACTOR * float(DUR_O);
						return int(temp);
					}

		
		case 'u' :
					if(ToDuration[length-6] == 'u' || ToDuration[length-6] == 'U')
					{
						temp = (MULTIPLICATION_FACTOR+5) * float(DUR_UU);
						return int(temp);
					}
					else if(ToDuration[length-6] == 'a' || ToDuration[length-6] == 'A')
					{
						temp = MULTIPLICATION_FACTOR * float(DUR_AU);
						return int(temp);
					}
					else
					{
						temp = MULTIPLICATION_FACTOR * float(DUR_U);
						return int(temp);
					}
	}
	return 0;
}

void CDoc::CheckOnce()
{
	FILE *parsed,*target;
	char Parse[100],c;
	int i1=0;
	//Parse = new char [100];
	//p = new char [20];
	char p[20] = "parse.iis";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Parse[i1]=c;
		i1++;

	}while(c != '$');
	Parse[i1] = '\0';
	
	strcat(Parse,p);
	
	Parse[strlen(Parse)]= '\0';
	char Parse1[100];
	i1=0;
	char p1[20] = "parse1.iis";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Parse1[i1]=c;
		i1++;

	}while(c != '$');
	Parse1[i1] = '\0';
	strcat(Parse1,p1);
	Parse1[strlen(Parse1)]= '\0';
	
	parsed = fopen(Parse,"rt");
	target = fopen(Parse1,"wb");
	char present[100],previous[100];
	char Reverse[30],Unit[30];
	fscanf(parsed,"%s ",&present);
	fprintf(target,"%s ",present);
	strcpy(previous,present);
	int i,k=0;
	while(1)
	{
		fscanf(parsed,"%s ",&present);
		k=0;
		for(i=strlen(present)-1;i>=0;i--)
		{	
			if(present[i] == '\\')
				break;
			Reverse[k]=present[i];
			k++;
				
		}
		Reverse[k]='\0';
		k=0;
		for(i=strlen(Reverse)-1;i>=0;i--)
		{
			Unit[k]=Reverse[i];
			k++;
		}
		Unit[k]='\0';
		if(strcmp(Unit,"aa.wav") == 0 || strcmp(Unit,"ii.wav") == 0 || strcmp(Unit,"uu.wav") == 0 || strcmp(Unit,"oo.wav") == 0 || strcmp(Unit,"ee.wav") == 0 || strcmp(Unit,"ai.wav") == 0 || strcmp(Unit,"au.wav") == 0)
		{
			if(strcmp(previous,"x") == 0)
			{
				fprintf(target,"%s ",present);
				strcpy(previous,present);
			}
		}
		else if(strcmp(present,"y") == 0)
			break;
		else
		{
			fprintf(target,"%s ",present);
			strcpy(previous,present);
		}
	}
	fprintf(target,"%s ","y");
	fclose(parsed);
	fclose(target);
	remove(Parse);
}


void CDoc::SaveFile()
{

	char *temp,*t;
	temp = new char [100];
	t = new char [20];
	char c;
	int i1=0;
	t="tempg.wav";
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		temp[i1]=c;
		i1++;

	}while(c != '$');
	temp[i1] = '\0';
	strcat(temp,t);
	temp[strlen(temp)]= '\0';	
	
	CFileDialog dlg(FALSE,"wav","*.wav");

	if((dlg.DoModal() == IDOK))
	{
		//FileSaveFlag=1;
		CFile out;
		CFile in;
		VERIFY(out.Open(dlg.GetPathName(),CFile::modeWrite | CFile::modeCreate));
		in.Open(temp,CFile::modeRead);
		short int transfer;
		WAVEheader head;
		in.Read(&head,sizeof(head));
		out.Write(&head,sizeof(head));
		for(int i=0;i<head.data_ckSize/2;i++)
		{
			in.Read(&transfer,sizeof(short int));
			out.Write(&transfer,sizeof(short int));
			transfer=0;
		}
		in.Close();
		out.Close();
	}
	
}



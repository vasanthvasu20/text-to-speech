// Doc.cpp : implementation file
//

#include "stdafx.h"
#include "Vaachaka.h"
#include "Doc.h"
#include "VaachakaDlg.h"

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

#define MULTIPLICATION_FACTOR 16

#define DUR_A 60
#define DUR_AA 170
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


#define DUR_A_INITIAL 70
#define DUR_AA_INITIAL 140
#define DUR_I_INITIAL 60
#define DUR_II_INITIAL 180
#define DUR_U_INITIAL 60
#define DUR_UU_INITIAL 200
#define DUR_AI_INITIAL 130   // RANDOMLY CHOOSEN
#define DUR_AU_INITIAL 100	 // RANDOM CHOOSEN
#define DUR_O_INITIAL 65
#define DUR_OO_INITIAL 180
#define DUR_E_INITIAL 60
#define DUR_EE_INITIAL 180

#define DUR_A_MIDDLE 50
#define DUR_AA_MIDDLE 150
#define DUR_I_MIDDLE 50
#define DUR_II_MIDDLE 150
#define DUR_U_MIDDLE 40
#define DUR_UU_MIDDLE 80
#define DUR_AI_MIDDLE 100   
#define DUR_AU_MIDDLE 100	
#define DUR_O_MIDDLE 55
#define DUR_OO_MIDDLE 110
#define DUR_E_MIDDLE 50
#define DUR_EE_MIDDLE 140

/*#define DUR_A_FINAL 60
#define DUR_AA_FINAL 130
#define DUR_I_FINAL 75
#define DUR_II_FINAL 132
#define DUR_U_FINAL 64
#define DUR_UU_FINAL 150
#define DUR_AI_FINAL 130   // RANDOMLY CHOOSEN
#define DUR_AU_FINAL 130	 // RANDOM CHOOSEN
#define DUR_O_FINAL 75
#define DUR_OO_FINAL 159
#define DUR_E_FINAL 75
#define DUR_EE_FINAL 159*/


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
}


BEGIN_MESSAGE_MAP(CDoc, CDocument)
	//{{AFX_MSG_MAP(CDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
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
void CDoc::KannadaSynthesize()
{
	if(m_strKannadaData.IsEmpty())
	{
		AfxMessageBox("Field is Empty");
		return;
	}

	KannadaParse();
	CheckOnce();
	KannadaConcatenate();
	PlaySou();

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
	m_strKannadaData.ReleaseBuffer();
		//while(m_strKannadaData.GetAt(Total_Length) != '\0')
//		Total_Length++;
	Total_Length=m_strKannadaData.GetLength();
	int Length = 0;
	CountUnit=0,CountSpace=0;
	index=0,index2=0;
	char *Array = m_strKannadaData.GetBuffer(Length+10000);
	int m_nFlagStatus=0;
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
		//TRACE("\n Length =%d,End = %d, Begin = %d",Length,Word_End,Word_Begin);
		fprintf(parse,"x ");
		m_nFlagStatus = 1;
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
				if(m_nFlagStatus == 1 && end != Length-1)
				{
					fprintf(parse,"xi ");
					CountUnit++;
					m_nFlagStatus = 0;
				}
				else if(end == Length-1)
				{
					fprintf(parse,"xf ");
					CountUnit++;
					break;
				}
				else
				{
					fprintf(parse,"xm ");
					CountUnit++;
				}
				
			}
			//TRACE("\n -- i=%d",i);
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
	}while(l<Total_Length-1);
	fprintf(parse,"y");
	fclose(parse);
	//TRACE("\nCount Unit = %d",CountUnit);
	
	for(i=0;i<index2;i++)
		TRACE(" CSpace [i] = %d,CUnitArray [i] = %d",CSpace[i],CUnitArray[i]);
	//delete [] m_cToConcatenate;
	TRACE("\nGoing out of Parse . . .");

	return;
}



void CDoc:: ExtendKannadaParse(int count)
{
	FILE *parsenew,*fp1;
	int start=0,j=0,k=0;
	int i;
	int cnt=0,knt=0,flag=0,ii=0,slen=0;
	char strq[100];
	int CountSpace=0,CountUnit=0,index=0,index2=0;
	int nqwords=2;
	char c='0';
	int i1=0;
	char Parse[100];
	char Quest[100];
	char p[20] = "parse.iis";
	char q[20] = "qwords.txt";
	//int CUnitArray1[70],CSpace1[70];

	//parsenew=fopen("D:\\roopa\\kannada_synthesis\\Thirukkural\\m_prs.txt","w");	
	//for(i=0;i<count;i++)
		//fprintf(parsenew,"%s  ",m_prs[i]);
	//TRACE("\n  m_prs count = %d\n",count);
	//fclose(parsenew);

	/*strcpy(qword[0],"yaaaaru");
	strcpy(qword[1],"yaaaavuudhu");*/

	i1=0;
	c='0';
	do
	{
		c = Path.GetAt(i1);
		if(c == '$')
			break;
		Quest[i1]=c;
		i1++;

	}while(c != '$');
	Quest[i1] = '\0';
	strcat(Quest,q);
	Quest[strlen(Quest)]= '\0';
	fp1 = fopen(Quest,"r");
	i=0;
	while(!feof(fp1))
	{
		fscanf(fp1,"%s",qword[i]);		
		//TRACE("qword = %s	",qword[i]);
		i++;
	}
	nqwords=i;
	TRACE("\npath qword = %s\n",Quest);
	TRACE("\nnqwords = %d\n",nqwords);
	//for(i=0;i<nqwords;i++)
		//TRACE("qword = %s	",qword[i]);

	i1=0;
	c='0';
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
	parsenew = fopen(Parse,"w");

	for(i=0;i<count;i++)
	{		
			if((strcmp(m_prs[i],"xd")==0))
			{
				//TRACE("xd=  ");
				for(j=start;j<=i;j++)
				{					
					//TRACE("%s ",m_prs[j]);
					if((strcmp(m_prs[j],"xd")==0) )
					{						
						CUnitArray[index]=CountUnit;
						CSpace[index2]=CountSpace;
						CountUnit++;
						index++;
						index2++;
						fprintf(parsenew,"%s  ",m_prs[j]);
					}
					else if((strcmp(m_prs[j],"x")==0))
					{
						CountUnit++;
						CountSpace=CountUnit+1;
						fprintf(parsenew,"%s  ",m_prs[j]);						
					}
					else
					{
						CountUnit++;
						strcpy(m_cToConcatenate,m_prs[j]);
						slen=strlen(m_cToConcatenate);
						int size = ChangeFileName(slen);
						fprintf(parsenew,"%s  ",m_sFileName);											
					}					
				}
				//TRACE("\n");				
				start=i+1;
				continue;
			}
			else if((strcmp(m_prs[i],"xc")==0))
			{
				//TRACE("xc=  ");
				for(j=start;j<=i;j++)
				{
					//TRACE("%s ",m_prs[j]);
					if((strcmp(m_prs[j],"xc")==0) )
					{						
						CUnitArray[index]=CountUnit;
						CSpace[index2]=CountSpace;
						CountUnit++;
						index++;
						index2++;
						fprintf(parsenew,"%s  ",m_prs[j]);
					}
					else if((strcmp(m_prs[j],"x")==0))
					{
						CountUnit++;
						CountSpace=CountUnit+1;
						fprintf(parsenew,"%s  ",m_prs[j]);
					}
					else
					{
						CountUnit++;
						strcpy(m_cToConcatenate,m_prs[j]);
						slen=strlen(m_cToConcatenate);
						int size = ChangeFileName(slen);					
						fprintf(parsenew,"%s  ",m_sFileName);
					}
				}
				//TRACE("\n");
				start=i+1;
				continue;
			}
			else if((strcmp(m_prs[i],"y")==0))
			{
				//TRACE("y=  ");
				for(j=start;j<=i;j++)
				{
					//TRACE("%s ",m_prs[j]);
					if((strcmp(m_prs[j],"y")==0) )
					{
						CountUnit++;
						fprintf(parsenew,"%s",m_prs[j]);
					}
					else if((strcmp(m_prs[j],"x")==0) )
					{
						CountUnit++;
						CountSpace=CountUnit;
						fprintf(parsenew,"%s  ",m_prs[j]);
					}
					else
					{
						CountUnit++;
						strcpy(m_cToConcatenate,m_prs[j]);
						slen=strlen(m_cToConcatenate);
						int size = ChangeFileName(slen);
						fprintf(parsenew,"%s  ",m_sFileName);
					}
				}
				//TRACE("\n");
			}
			else if((strcmp(m_prs[i],"xe")==0))
			{
				//TRACE("xe=  ");
				for(j=start;j<=i;j++)
				{
					//TRACE("%s ",m_prs[j]);
					if((strcmp(m_prs[j],"xe")==0) )
					{						
						CUnitArray[index]=CountUnit;
						CSpace[index2]=CountSpace;
						CountUnit++;
						index++;
						index2++;
						fprintf(parsenew,"%s  ",m_prs[j]);
					}
					else if((strcmp(m_prs[j],"x")==0))
					{
						CountUnit++;
						CountSpace=CountUnit+1;
						fprintf(parsenew,"%s  ",m_prs[j]);
					}
					else
					{
						CountUnit++;
						strcpy(m_cToConcatenate,m_prs[j]);
						slen=strlen(m_cToConcatenate);
						int size = ChangeFileName(slen);					
						fprintf(parsenew,"%s  ",m_sFileName);
					}
				}
				//TRACE("\n");
				start=i+1;
				continue;
			}
			else if((strcmp(m_prs[i],"xq")==0))
			{
				//TRACE("xq=  ");
				k=0;
				for(j=start;j<i;j++)
				{
					strcpy(m_qline[k],m_prs[j]);
					k++;
					//TRACE("%s ",m_prs[j]);
				}	

				knt=k;
				j=1;
				//TRACE("\n%d\n",knt);
				strcpy(m_newqline[0],m_qline[0]);
				for(ii=1;ii<knt;ii++)
				{
					strq[0]='\0'; 					
					flag=0;
					while(ii<knt)
					{
						if((strcmp(m_qline[ii],"x"))!=0)
						{						
							strcat(strq,m_qline[ii]);
							//TRACE("%d  str= %s	  m_q=%s  \n",ii, strq,m_qline[ii]);
							strcpy(m_newqline[j++],m_qline[ii]);
							ii++;
						}
						else
							break;
					}
					//TRACE("end\n");
					for(k=0;k<nqwords;k++)
					{
						if((strcmp(strq,qword[k]))==0)
							flag=1;
					}
					if(flag==1)
						strcpy(m_newqline[j++],"xq");
					if(ii!=knt)
						strcpy(m_newqline[j++],"x");
				}	
				strcpy(m_newqline[j++],"xqd");
				knt=j;
				//TRACE("final knt= %d\n",j);
				for(ii=0;ii<knt;ii++)
				{
					//TRACE("%s\n",m_newqline[ii]);
					if((strcmp(m_newqline[ii],"xq")==0) )
					{						
						CUnitArray[index]=CountUnit;
						CSpace[index2]=CountSpace;
						CountUnit++;
						index++;
						index2++;
						fprintf(parsenew,"%s  ",m_newqline[ii]);
					}
					else if((strcmp(m_newqline[ii],"x")==0))
					{
						CountUnit++;
						CountSpace=CountUnit+1;
						fprintf(parsenew,"%s  ",m_newqline[ii]);
					}
					
					else if((strcmp(m_newqline[ii],"xqd")==0))
					{
						CountUnit++;
						//here not tapping the index of "xqd";bcoz this "xqd" is needed for delay alone;so just incremented the unit cnt
						fprintf(parsenew,"%s  ",m_newqline[ii]);
					}
					else
					{
						CountUnit++;
						strcpy(m_cToConcatenate,m_newqline[ii]);
						j=strlen(m_cToConcatenate);
						int size = ChangeFileName(j);
						fprintf(parsenew,"%s   ",m_sFileName);
					}
				}
				//TRACE("\n");
				start=i+1;
				continue;
			}
 
	}
	TRACE("\n\n");
	//TRACE("\nmy prog CountUnit=%d\n",CountUnit);
	fclose(parsenew);
}//end of ExtendKannadaParse()


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
	char u[20] = "database_kannada\\";
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
			//To remove xm and xf coming together
			if(strcmp(previous,"xm") == 0)
			{
				fseek(target,-sizeof(char)*3,SEEK_CUR);
			}
			if(strcmp(previous,"xi") == 0)
			{
				fseek(target,-sizeof(char)*3,SEEK_CUR);
			}
			if(strcmp(previous,"x") == 0)
			{
				fprintf(target,"%s ",present);
				strcpy(previous,present);
			}
		}
		else if(strcmp(Unit,"a.wav") == 0 || strcmp(Unit,"i.wav") == 0 || strcmp(Unit,"u.wav") == 0 || strcmp(Unit,"o.wav") == 0 || strcmp(Unit,"e.wav") == 0 || strcmp(Unit,"ai.wav") == 0 || strcmp(Unit,"au.wav") == 0)
		{
			//To remove xm and xf coming together
			if(strcmp(previous,"xm") == 0)
			{
				fseek(target,-sizeof(char)*3,SEEK_CUR);
			}
			if(strcmp(previous,"xi") == 0)
			{
				fseek(target,-sizeof(char)*3,SEEK_CUR);
			}
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
	//remove(Parse);
}

void CDoc::KannadaConcatenate()
{
	int i,j,temp,Space=0,ind=0;
	BOOL flagpresent,flagnext;
	IIScHeader presenthead,nexthead;
	/*@@@@@@@@@*/short int presentsignal[50000],nextsignal[50000],presentpitch[50000],nextpitch[50000],*EndSignal;
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
	int duration = 0,Unit=1;//@@@@@@@
	int len_present;//@@@@@@@
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

	PM = new short int [100];//@@@@@@@@@@	
	
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
		//TRACE("\n next= %s",next);
		Unit++;
		if(!(strcmp(nextscan,"y") == 0 || strcmp(nextscan,"x") == 0 || strcmp(nextscan,"xd") == 0 || strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xc") == 0 || strcmp(nextscan,"xd") == 0 ||strcmp(nextscan,"xe") == 0))
		{
			file.Read(&m_cTag[0],sizeof(char));
			i=0;
			while(m_cTag[i] != ' ')
			{
				i++;
				file.Read(&m_cTag[i],sizeof(char));
			}
			m_cTag[i] = '\0';
			//TRACE("\n m_cTag in concatenate = %s",m_cTag);
			if(!strcmp(m_cTag,"xi"))
				strcpy(m_cTagcopy,m_cTag);
			Unit++;
		}

		

		// Last Unit
		if(strcmp(nextscan,"y") == 0 || strcmp(nextscan,"x") == 0 || strcmp(nextscan,"xd") == 0 || strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xc") == 0 || strcmp(nextscan,"xd") == 0 ||strcmp(nextscan,"xe") == 0)
		{

			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
			{
				TRACE(" \nNot Present - 1 **** %s" ,present);
				TRACE(" \nXXXXXXXXXXXXNot Present - 1 **** %s" ,nextscan);//@@@@@@@

				/*@@@@@@@@@@*/  if(!(pmind == 0) && (Unit >= CSpace[ind] && Unit <= CUnitArray[ind]+1) || ((strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xc") == 0 || strcmp(nextscan,"xe") == 0)))
				{
						//TRACE(" \n pmind = %d",pmind);
						if(pmind == 0) //@@@@@@@@@@
							continue;  //@@@@@@@@@@
						len_present =0;//@@@@@@@@@@
						PitchMod pitch;//@@@@@@@@@@
						pitch.APitch=presenthead.AvgPitch;//@@@@@@@@@@
						if(strcmp(nextscan,"xq") == 0)
							pitch.Type=1;//@@@@@@@@@@
						else if(strcmp(nextscan,"xe") == 0)
							pitch.Type=2;//@@@@@@@@@@
						else if(strcmp(nextscan,"xc") == 0)
							pitch.Type=3;//@@@@@@@@@@
						else if(strcmp(nextscan,"xd") == 0)
							pitch.Type=4;//@@@@@@@@@@
						
						pitch.PMSignal=PM;//@@@@@@@@@@
						pitch.PMS_l=pmind;//@@@@@@@@@@
						pitch.Modification();//@@@@@@@@@@
						TRACE("\n Pass 1");							
						for(i=0;i<pitch.pml-1;i++)//@@@@@@@@@@
							fwrite(&pitch.Modifx[i],sizeof(short int),1,target);//@@@@@@@@@@
						size = size+pitch.pml-1;//@@@@@@@@@@
						if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
								ind++;//@@@@@@@@@@
						TRACE("\n Pass 2");
						//free(PM);						
						//delete [] PM;
				}
			}
			else
			{
			
				fread(&presenthead,sizeof(IIScHeader),1,presentwave);
				//presentsignal = new short int [presenthead.DataLength];
				for(i=0;i<50000;i++)
					presentsignal[i]=0;
				for(i=0;i<50000;i++)
					presentpitch[i]=0;
				for(i=0;i<presenthead.DataLength;i++)
					fread(&presentsignal[i],sizeof(short int),1,presentwave);
				
				for(i=0;i<presenthead.LengthofPitchMarks;i++)
				{
					fread(&temp,sizeof(int),1,presentwave);
					pitchmark[i]=temp;//@@@@@@@@
					presentpitch[temp] = 1;
				}

				if((Unit >= CSpace[ind] && Unit <= CUnitArray[ind]+1) || ((strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xc") == 0 || strcmp(nextscan,"xe") == 0)))
				{
						len_present =0;//@@@@@@@@@@
						EndSignal  = new short int [presenthead.DataLength];//@@@@@@@@@@
						for(i=presenthead.LSegment;i<presenthead.DataLength;i++)
						{
							if(strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xe") == 0)
							{
								EndSignal[len_present] = presentsignal[i];//@@@@@@@@@@
								len_present++;//@@@@@@@@@@
							}
							else
							{
								PM[pmind]=presentsignal[i];//@@@@@@@@@@
								pmind++;//@@@@@@@@@@
							}
							
							
						}
						//TRACE("pmind =%d",pmind);
						PitchMod pitch;//@@@@@@@@@@
						//pitch.PMSignal=PM;
						//pitch.PMS_l=pmind-1;
						pitch.APitch=presenthead.AvgPitch;//@@@@@@@@@@
						if(strcmp(nextscan,"xq") == 0)
							pitch.Type=1;//@@@@@@@@@@
						else if(strcmp(nextscan,"xe") == 0)
							pitch.Type=2;//@@@@@@@@@@
						else if(strcmp(nextscan,"xc") == 0)
							pitch.Type=3;//@@@@@@@@@@
						else if(strcmp(nextscan,"xd") == 0)
							pitch.Type=4;//@@@@@@@@@@
						if(strcmp(nextscan,"xq") == 0 || strcmp(nextscan,"xe") == 0)
						{
							pitch.PMSignal=EndSignal;//@@@@@@@@@@
							pitch.PMS_l=len_present;//@@@@@@@@@@
							pitch.Mod_Count=1;
							//TRACE("\nFIRST CALL TO PM FUNCTION\n");
							pitch.Modification();//@@@@@@@@@@			
							int len_mod = pitch.len_modifx;//@@@@@@@@@@
							for(i=0;i<len_mod;i++)
							{
								PM[pmind]=pitch.Modifx[i];//@@@@@@@@@@
								pmind++;
							}
							pitch.PMSignal=PM;//@@@@@@@@@@
							pitch.PMS_l=pmind-1;
							pitch.Mod_Count=2;
							//TRACE("\nSECOND CALL TO PM FUNCTION\n");
							pitch.Modification();//@@@@@@@@@@
							
						}
						else if(strcmp(nextscan,"xc") == 0 || strcmp(nextscan,"xd") == 0)
						{
							pitch.PMSignal=PM;
							pitch.PMS_l=pmind-1;
							pitch.Modification();//@@@@@@@@@@
						}

									
						for(i=0;i<pitch.pml-1;i++)
							fwrite(&pitch.Modifx[i],sizeof(short int),1,target);//@@@@@@@@@@
						size = size+pitch.pml-1;//@@@@@@@@@@
						if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
								ind++;
						//free(PM);						
						//delete [] PM;
				}// end of if when nextwave is xd||xe||xc||xq
				//TRACE(" Unit = %d, CunitArray[ind] = %d",Unit,CUnitArray[ind]+1);
				else
				{
					for(i=presenthead.LSegment;i<presenthead.DataLength;i++)
						fwrite(&presentsignal[i],sizeof(short int),1,target);
					size = size+presenthead.DataLength-presenthead.LSegment;
					if( Unit == CUnitArray[ind]+1)//@@@@@@@
								ind++;//@@@@@@@
				}

					
				
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
					for(i=0;i<8000;i++)
					fwrite(&j,sizeof(short int),1,target);
					size=size+8000;
				}
				else 
				{	
					
					if(flag_checkdot == 1)
					{
						flag_checkdot=0;
					
					}
					else
					{

						for(i=0;i<16000;i++)
							fwrite(&j,sizeof(short int),1,target);
						size=size+16000;
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
				//Unit++;
				//if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
				//	ind++;//@@@@@@@@@@
				/*file.Read(&m_cTag[0],sizeof(char));
				i=0;
				while(m_cTag[i] != ' ')
				{
					i++;
					file.Read(&m_cTag[i],sizeof(char));
				}
				m_cTag[i] = '\0';
				TRACE("\n m_cTag = %s",m_cTag);*/
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
			for(i=0;i<100;i++)
				fwrite(&j,sizeof(short int),1,target);
			size=size+0;
			strcpy(present,next);
			strcpy(prescan,nextscan);
			presentwave = fopen(present,"rb");
			if(presentwave == NULL)
			{
				fprintf(missing,"\n%s",prescan);
				TRACE("\n Not Present  - 2 ****** %s", present);			
				delete [] PM ;//@@@@@@@@@@
				PM = new short int [100000];//@@@@@@@@@@
				pmind=0;//@@@@@@@@@@
			}
			else
			{
				flag_checkdot=1;
				fread(&presenthead,sizeof(IIScHeader),1,presentwave);
				for(i=0;i<50000;i++)
					presentsignal[i]=0;
				for(i=0;i<50000;i++)
					presentpitch[i]=0;
				for(i=0;i<presenthead.DataLength;i++)
					fread(&presentsignal[i],sizeof(short int),1,presentwave);
					
				if(presenthead.BasicUnit != 1 || presenthead.BasicUnit != 3 || presenthead.BasicUnit != 7)
				{
					//delete [] PM ;
					//PM = new short int [100000];
					delete [] PM ;//@@@@@@@@@@
					PM = new short int [100000];//@@@@@@@@@@
					pmind=0;//@@@@@@@@@@

					if(Unit >= CSpace[ind] && Unit <= CUnitArray[ind])//@@@@@@@@@@
					{
						pmind=0;//@@@@@@@@@@
						//TRACE(" I unit Unit = %d, CUnitArray = %d\t",Unit,CUnitArray[ind]);
						//TRACE("\npmind in first = %d",pmind);
						for(i=0;i<presenthead.LSegment;i++)
						{
				
							PM[pmind]=presentsignal[i];//@@@@@@@@@@
							pmind++;
						}
						if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
							ind++;

						size = size+presenthead.LSegment;//@@@@@@@@@@
					}
					else
					{
						for(i=0;i<presenthead.LSegment;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+presenthead.LSegment;
					}
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
				fprintf(missing,"\n%s",prescan);
				TRACE("\n Not Present - 3 ******** %s", present);
			
				flagpresent = 0;
				if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
					ind++;//@@@@@@@@@@
			}
			else
			{
			
				flag_checkdot=0;
				flagpresent = 1;
				fread(&presenthead,sizeof(IIScHeader),1,presentwave);
				for(i=0;i<50000;i++)
					presentsignal[i]=0;
				for(i=0;i<50000;i++)
					presentpitch[i]=0;
				for(i=0;i<presenthead.DataLength;i++)
					fread(&presentsignal[i],sizeof(short int),1,presentwave);
				
				for(i=0;i<presenthead.LengthofPitchMarks;i++)
				{
					fread(&temp,sizeof(int),1,presentwave);
					presentpitch[temp] = 1;
				}
			}

			nextwave = fopen(next,"rb");
			if(nextwave == NULL)
			{
				fprintf(missing,"\n%s",nextscan);
				TRACE("\n Not Present - 4 ******** %s", next);
				if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
					ind++;//@@@@@@@@@@
			
				flagnext=0;
			}
			else
			{
				flagnext=1;
				fread(&nexthead,sizeof(IIScHeader),1,nextwave);
				for(i=0;i<50000;i++)
					nextsignal[i]=0;
				for(i=0;i<50000;i++)
					nextpitch[i]=0;
				
				for(i=0;i<nexthead.DataLength;i++)
					fread(&nextsignal[i],sizeof(short int),1,nextwave);
				for(i=0;i<nexthead.LengthofPitchMarks;i++)
				{
					fread(&temp,sizeof(int),1,nextwave);
					nextpitch[temp] = 1;
				}
			}


			strcpy(ToDuration,present);
			
			int duration = DetectDuration();
			//TRACE("\n duration = %d",duration);
			strcpy(m_cTagcopy,m_cTag);
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
					if(Unit >= CSpace[ind] && Unit <= CUnitArray[ind])//@@@@@@@@@@
					{
						
						//TRACE(" II unit Unit = %d, CUnitArray = %d\t",Unit,CUnitArray[ind]);
						//TRACE("\npmind in Middle = %d",pmind);
						for(i=presenthead.LSegment;i<presenthead.LSegment+tempduration;i++)
						{
							//TRACE("\npmind in Middle = %d",pmind);
							PM[pmind]=presentsignal[i];//@@@@@@@@@@
							pmind++;//@@@@@@@@@@
						}
						if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
							ind++;//@@@@@@@@@@
						size = size+tempduration;
					}
					else
					{
						for(i=presenthead.LSegment;i<presenthead.LSegment+tempduration;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+tempduration;
					}

						
				}
				
				if(presenthead.BasicUnit == 4 || presenthead.BasicUnit == 5 || presenthead.BasicUnit == 6)
				{
				
					if(Unit >= CSpace[ind] && Unit <= CUnitArray[ind])//@@@@@@@@@@
					{
						
						for(i=presenthead.LSegment;i<presenthead.RSegment;i++)
						{
							PM[pmind]=presentsignal[i];//@@@@@@@@@@
							pmind++;//@@@@@@@@@@
						}
						
						if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
							ind++;//@@@@@@@@@@
						size = size+presenthead.RSegment-presenthead.LSegment;
					}

					else
					{
						for(i=presenthead.LSegment;i<presenthead.RSegment;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+presenthead.RSegment-presenthead.LSegment;
					}
					
					
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
				
					if(Unit >= CSpace[ind] && Unit <= CUnitArray[ind])//@@@@@@@@@@
					{
						
						for(i=presenthead.RSegment;i<presenthead.RSegment+tempduration;i++)
						{
							PM[pmind]=presentsignal[i];//@@@@@@@@@@
							pmind++;//@@@@@@@@@@
						}
						
						if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
							ind++;//@@@@@@@@@@
						size = size+tempduration;
					}

					else
					{
						for(i=presenthead.RSegment;i<presenthead.RSegment+tempduration;i++)
							fwrite(&presentsignal[i],sizeof(short int),1,target);
						size = size+tempduration;
					}
					
					
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
				
				if(Unit >= CSpace[ind] && Unit <= CUnitArray[ind])//@@@@@@@@@@
				{
						for(i=nexthead.LSegment-tempduration;i<nexthead.LSegment;i++)
						{
							PM[pmind]=nextsignal[i];//@@@@@@@@@@
							pmind++;//@@@@@@@@@@
						}
						size = size+tempduration;
						if( Unit == CUnitArray[ind]+1)//@@@@@@@@@@
							ind++;//@@@@@@@@@@
				}

				else
				{
					for(i=nexthead.LSegment-tempduration;i<nexthead.LSegment;i++)
						fwrite(&nextsignal[i],sizeof(short int),1,target);
					size = size+tempduration;
				}
					
				
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
	if(SizeOfSentance < 2000)//@@@@@@@@@@
	{
		short int junk =0;
		for(i=0;i<1000;i++)
			fwrite(&junk,sizeof(short int),1,target);
		SizeOfSentance+=1000;
	}//@@@@@@@@@@@
	fcloseall();
	//TRACE("\n Space = %d, Unit = %d",Space,Unit);
	TRACE("\nOut of Concatenate %d\n",SizeOfSentance);
	WriteWaveFile();
	

}
int CDoc::DetectDuration()
{
	CString str = ToDuration;
	//TRACE("\n m_cTag = %s in detect duration",m_cTag);
	//AfxMessageBox(m_cTagcopy);
	int length = str.GetLength();
	float temp;
	switch(ToDuration[length-5])
	{
		case 'a' : 
					if(ToDuration[length-6] == 'a' || ToDuration[length-6] == 'A')
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = (MULTIPLICATION_FACTOR) * float(DUR_AA_INITIAL);
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
							temp = (MULTIPLICATION_FACTOR) * float(DUR_AA_MIDDLE);
							return int(temp);
						}
					}
					else
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = (MULTIPLICATION_FACTOR) * float(DUR_A_INITIAL);
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
							temp = (MULTIPLICATION_FACTOR) * float(DUR_A_MIDDLE);
							return int(temp);
						}
					}


		case 'e' :
					if(ToDuration[length-6] == 'e' || ToDuration[length-6] == 'E')
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = (MULTIPLICATION_FACTOR+5) * float(DUR_EE_INITIAL);
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_EE_MIDDLE);
								return int(temp);
						}
					}
					else
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_E_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_E_MIDDLE);
								return int(temp);
						}
					}


		case 'i' :
					if(ToDuration[length-6] == 'i' || ToDuration[length-6] == 'I')
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_II_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_II_MIDDLE);
								return int(temp);
						}
					}
					else if(ToDuration[length-6] == 'a' || ToDuration[length-6] == 'A')
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_AI_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_AI_MIDDLE);
								return int(temp);
						}
						
					}
					else
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_I_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_I_MIDDLE);
								return int(temp);
						}
						
					}

		case 'o' :
					if(ToDuration[length-6] == 'o' || ToDuration[length-6] == 'O')
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_OO_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_OO_MIDDLE);
								return int(temp);
						}
						
					}
					else
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_O_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_O_MIDDLE);
								return int(temp);
						}
						
					}

		
		case 'u' :
					if(ToDuration[length-6] == 'u' || ToDuration[length-6] == 'U')
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_UU_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_UU_MIDDLE);
								return int(temp);
						}
					
					}
					else if(ToDuration[length-6] == 'a' || ToDuration[length-6] == 'A')
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_AU_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_AU_MIDDLE);
								return int(temp);
						}
						
					}
					else
					{
						if(!strcmp(m_cTagcopy,"xi"))
						{
							temp = MULTIPLICATION_FACTOR * float(DUR_U_INITIAL);	
							return int(temp);
						}
						else if(!strcmp(m_cTagcopy,"xm"))
						{
								temp = (MULTIPLICATION_FACTOR+5) * float(DUR_U_MIDDLE);
								return int(temp);
						}
						
					}
	}
	return 0;
}

/*int CDoc::DetectDuration()
{
	CString str = ToDuration;

	int length = str.GetLength();
	float temp;
	switch(ToDuration[length-5])
	{
		case 'a' : 
					if(ToDuration[length-6] == 'a' || ToDuration[length-6] == 'A')
					{
						temp = (MULTIPLICATION_FACTOR+8) * float(DUR_AA);
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
*/

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
	remove(x);
	

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

// Document.cpp : implementation file
//

#include "stdafx.h"
#include "Vak.h"
#include "Document.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Document

IMPLEMENT_DYNCREATE(Document, CDocument)

Document::Document()
{
}

BOOL Document::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

Document::~Document()
{
}


BEGIN_MESSAGE_MAP(Document, CDocument)
	//{{AFX_MSG_MAP(Document)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Document diagnostics

#ifdef _DEBUG
void Document::AssertValid() const
{
	CDocument::AssertValid();
}

void Document::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Document serialization

void Document::Serialize(CArchive& ar)
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
// Document commands

int Document::docread()
{
	FILE *in;
	WAVEheader head;
	in=fopen(m_sFileName,"rb");
	CString str;
	str.Format("%s Does Not Exist",m_sFileName);
	if(!in)
	{
		//AfxMessageBox(str);
		return 0;
	}
	fread(&head,sizeof(head),1,in);
	signal = new short int [head.data_ckSize];
	for(unsigned int i=0;i<head.data_ckSize/2;i++)
		fread(&signal[i],sizeof(short int),1,in);
	m_nSize=head.data_ckSize;
	fclose(in);
	
	return 1;
}

void Document::KannadaConcatenate(int size)
{
	if(size<0)return;
	if(FlagWordEnd == TRUE)
	{
		FlagWordEnd=0;
		return;
	}
	int i,j=0,start,end;
	FILE *temp;
	CString temp1 = m_cToConcatenate;
	CString temp3 = temp1.Left(size);
	AfxMessageBox(temp3);
	CString strTemp(".wav");
	CString Unit("d:\\spd\\tamil\\");
	Unit += temp1.Left(size);
	Unit += strTemp;
	m_sFileName = Unit;
	j=docread();
	if(j==0)
	{
		CString strTemp(".wav");
		CString Unit1("d:\\spd\\tamil\\");
		Unit1 += temp1.Left(2);
		Unit1 += strTemp;
		m_sFileName = Unit1;
		docread();
		temp=fopen("d:\\temp\\x","ab+");
		start = 0;
		end = m_nSize;
		for(i=start;i<end;i++)
			fwrite(&signal[i],sizeof(short int),1,temp);
		fclose(temp);
		SizeOfSentance += (end-start);
		CString Unit2("d:\\spd\\tamil\\");
		Unit2 += temp3.Right(2);
		Unit2 += strTemp;
		m_sFileName = Unit2;
		docread();
		temp=fopen("d:\\temp\\x","ab+");
		start = 0;
		end = m_nSize;
		for(i=start;i<end;i++)
			fwrite(&signal[i],sizeof(short int),1,temp);
		fclose(temp);
		SizeOfSentance += (end-start);
	}
	else
	{
		temp=fopen("d:\\temp\\x","ab+");
		start = 0;
		end = m_nSize;
		for(i=start;i<end;i++)
			fwrite(&signal[i],sizeof(short int),1,temp);
		fclose(temp);
		SizeOfSentance += (end-start);
	}
}

void Document::WriteWaveFile()
{
	remove("d:\\temp\\temp.wav");
	FILE *in,*out;
	int i;
	short int transfer;
	WAVEheader head;
	in=fopen("d:\\database\\aa.wav","rb");
	fread(&head,sizeof(head),1,in);
	fclose(in);
	in=fopen("d:\\temp\\x","rb");
	head.data_ckSize = SizeOfSentance*2;
	out=fopen("d:\\temp\\temp.wav","wb");
	fwrite(&head,sizeof(head),1,out);
	while(fread(&transfer,sizeof(short int),1,in) != NULL)
		fwrite(&transfer,sizeof(short int),1,out);
	fclose(in);
	fclose(out);
	remove("d:\\temp\\x");
}


void Document::KannadaParse()
{
	CString str;
	int i=0,j,k,start=0,end=0,l=0,Word_Begin,Word_End,m,n;
	int Total_Length = m_strKannadaData.GetLength();
	int Length = 0;
	char *Array = m_strKannadaData.GetBuffer(Length);
	char TempArray[20];

	BeginWaitCursor();
	do
	{
		start=0;
		end=0;
		Word_Begin=l;
		while((Array[l] != ' ') && (l < Total_Length))
			l++;
		Word_End=l;
		Length = Word_End - Word_Begin;
		for(i=Word_Begin,j=0;i<Word_End;i++,j++)
			TempArray[j] = Array[i];
		l++;
		i=0;j=0;
		FlagWordEnd=0;
	do
	{
		if(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)))
		{
			start=i;
			do
			{
				i++;
			}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)));
			end=i-1;
			
			if(TempArray[i] == 'a')
			{
				if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
					end = i+2;
				else if(TempArray[i+1] == 'a')
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
					}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)));
					
					end=i-1;
					if(TempArray[i] == 'a')
					{
						if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
							end = i+2;
						else if(TempArray[i+1] == 'a')
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
					break;

				case 'i' :
					start=i;
					i++;
					
					if(TempArray[i] == 'i')
						i=i+1;
					
					do
					{	
						i++;
					}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)));
					end=i-1;
					
					if(TempArray[i] == 'a')
					{
						if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
							end = i+2;
						else if(TempArray[i+1] == 'a')
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
					break;

				case 'e' :
					start=i;
					i++;
					
					if(TempArray[i] == 'e')
						i=i+1;

					do
					{
						i++;
					}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)));
					end=i-1;

					if(TempArray[i] == 'a')
					{
						if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
							end = i+2;
						else if(TempArray[i+1] == 'a')
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
					break;

				case 'o' :
					start=i;
					i++;

					if(TempArray[i] == 'o')
						i=i+1;
					
					do
					{
						i++;
					}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)));
					end=i-1;

					if(TempArray[i] == 'a')
					{
						if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
							end = i+2;
						else if(TempArray[i+1] == 'a')
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
					break;

				case 'u' :
					start=i;
					i++;
					
					if(TempArray[i] == 'u')
						i=i+1;
					
					do
					{
						i++;
					}while(((TempArray[i] != 'a') && (i < Length)) && ((TempArray[i] != 'e') && (i < Length)) && ((TempArray[i] != 'i') && (i < Length)) && ((TempArray[i] != 'o') && (i < Length)) && ((TempArray[i] != 'u') && (i < Length)) && ((TempArray[i] != ' ') && (i < Length)));
					end=i-1;

					if(TempArray[i] == 'a')
					{
						if(TempArray[i+1] == 'e' || TempArray[i+1] == 'o')
							end = i+2;
						else if(TempArray[i+1] == 'a')
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
					break;
			}
		}
	
		if((end >= Length) && (Length > 2))FlagWordEnd=1;
		if(end==Length)end=end-1;

		m_cToConcatenate = new char [end-start+1];
		for(j=start,k=0;j<=end;j++,k++)
			m_cToConcatenate[k] = TempArray[j];
		KannadaConcatenate(end-start+1);
		delete [] m_cToConcatenate;
		}while(i<Length-1);
		}while(l<Total_Length-1);
		WriteWaveFile();
		EndWaitCursor();
}
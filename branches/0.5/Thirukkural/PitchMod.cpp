// PitchMod.cpp: implementation of the PitchMod class.
//
//////////////////////////////////////////////////////////////////////
/**********************************************************************
 * File:                PitchMod.cpp  
 * Description:         Pitch marking and pitch modification 
 * Author:              Jayavardhana Rama G L 
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
#include "stdafx.h"
#include "Vak.h"
#include "PitchMod.h"
#include <math.h>

#define pi 3.14159
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PitchMod::PitchMod()
{

}

PitchMod::~PitchMod()
{
	delete [] Signal;
	delete [] Modifx;
	//delete [] PMark;
	delete [] Find;
	
	
}

void PitchMod::Modification()
{
	int i,j;
	float in1,in2;
	pml=0;
	float inc;
	TRACE("\n PMS -l = %d",PMS_l);
	Signal = new float [PMS_l];
	Modifx = new short int [PMS_l*2];
	for(i=0;i<PMS_l;i++)
		Signal[i] = float(PMSignal[i]);
	//AfxMessageBox("Fine");
	PitchMark();
	Find = new int [PMS_l];
	for(i=0,j=0;i<PMS_l;i++)
	{
		if(PMark[i] == 1)
		{
			Find[j]=i;
			//TRACE("Find = %d",Find[j]);
			j++;
		}
	}
	count=j-1;
	// Pitch modification
	in1=float(1.0);
	int f,fin,cnt,cc,k=0;
	float pe,*ccc;
	ccc = new float [count];
	if(Type == 1)
	{
		if(Mod_Count == 1)
		{
			in1=float(1.0);
			in2=float(1.1);
		}
		else if(Mod_Count == 2)
		{
			in1 = float(1.0);
			in2 = float(1.1);
		}
	}
	else if(Type == 2)
	{
		if(Mod_Count == 1)
		{
			in1 = float(1.0);
			in2 = float(1.1);
		}
		else if(Mod_Count == 2)
		{
			in1=float(1.0);
			in2=float(1.1);
		}
	}
	else if(Type == 3)
	{
		in1=float(1.0);
		in2=float(0.95);
	}
	else if(Type == 4)
	{
		in1=float(1.0);
		in2 = float(0.9);
	}

	inc=float(in2-in1)/count;
	//inc=float((log(in2)-log(in1))/float(count));
	
	//TRACE("inc = %f",inc);
	/*for(i=0;i<count;i++)
	{
		ccc[i]=float(exp(log(in1)+i*inc));
	//	TRACE(" ccc = %f",ccc[i]);
	}*/
	
	
	f=0; fin=1; cnt=0; cc=1;j=0;
	len_modifx=0;
	while(j<count)
	{
		k=0;
		for(i=Find[j];i<=Find[j+1];i++)
		{
			frame[k]=Signal[i];
			k++;
		}
		j=j+1; 
		frame_l=k-1;
		int a_l,b_l,x_l;
		float *g;
		g = new float;
		g[0]=1.0;
		LPC();
		b_l=11;
		a_l=1;
		x_l=frame_l;
		Filter(LpcCoeff,g,frame,b_l,a_l,x_l);
		Excitation = new float [frame_l];
		Excitation=y;
		FDCT();
		pe=float(1.0/(in1+cnt*inc));
		//pe=float(1.0/ccc[cnt]);
		len=int(ceil(pe*frame_l));
		//TRACE("len = %d frame_l = %d\t",len,frame_l);
		IDCT();
		b_l=1;
		a_l=11;
		x_l=len;
		Filter(g,LpcCoeff,IDctCoeff,b_l,a_l,x_l);

		for(i=0;i<len;i++)
		{

            Modifx[pml]=short(sqrt(1.0*frame_l/len) * y[i]);
			len_modifx++;
			pml=pml+1;
		}
		// Normalisation 
		short int max=0;
		for(i=0;i<len;i++)
		{
			//Modifx[i]=abs(Modifx[i]);
			if(abs(Modifx[i]) > max)
				max=abs(Modifx[i]);
		}
		//TRACE(" \nmax = %d",max);
		for(i=0;i<len;i++)
			Modifx[i]=short int(Modifx[i]*1.0/max);
		cc=cc+1;   
		cnt=cnt+1;
		delete [] DctCoeff;
		delete [] IDctCoeff;
		delete [] Excitation;
		delete [] y;
		delete [] g;
		pml--;
		//TRACE(" j= %d count = %d",j,count);
	}
	pml--;
	delete [] ccc;
}

void PitchMod::PitchMark()
{
	short int *C;
	short int *input;
	input = new short int [PMS_l];
	PMark = new short int [PMS_l];
	C = new short int [PMS_l];
	input = PMSignal;

	int siz = PMS_l;
	int mea =Mean();
	int i;
	for(i=0;i<siz;i++)
	{
		input[i] = input[i]-mea;	
		PMark[i]=0;
	}
	for(i=0;i<siz;i++)
	{
		if (input[i] >= 0)
			input[i] = 0;
		else
			input[i] = abs(input[i]);
	}

	int pitchperiod = APitch+20;
	int framelength = int(pitchperiod);
	int j=0;
	int maxim=1;
	while(maxim+framelength < siz)
	{
		short int maximum=0,maxi=0;
		for(i=maxim;i<maxim+framelength;i++)
		{
			
			if(maximum < input[i])
			{
				maximum=input[i];
				maxi=i-maxim;
			}
		}
		//TRACE("\n maxim+maxi = %d",maxim+maxi);
		PMark[int(maxim + maxi)] = 1;
		maxim = int(framelength * 0.5) + maxim;
	}
	i=1;

	while(i < siz - 2*framelength)
	{
		if(PMark[i] == 1)
		{
			PMark[i] = 0;
			while(input[i] > 0)
				i=i+1;
     
			PMark[i] = 1;
		}
		i=i+1;
	}

	i=1;
	
	while(i < siz - 2* framelength)
	{
		if(PMark[i] > 0 && input[i] != 0)
			PMark[i] = 0;
		i=i+1;
	}

	// Implement find 
	for(i=0,j=0;i<siz;i++)
	{
		if(PMark[i] == 1)
		{
			C[j]=i;
			j++;
		}
	}
	j=j-1;
	
	for(i=0;i<j-1;i++)
	{	
		//TRACE(" C = %d",C[i]);
		if (abs(C[i]-C[i+1])<=30)
			PMark[C[i+1]]=0;
	}
	
	/*delete C;
	delete input;*/
	
	
}


int PitchMod::Mean()
{
	int i;
	int mvalue=0;
	for(i=0;i<PMS_l;i++)
		mvalue+=PMSignal[i];
	mvalue = mvalue/(PMS_l+1);
	return mvalue;

}


void PitchMod::FDCT()
{
	int k,m,n;
	DctCoeff = new float [frame_l*2];
	n=frame_l;
	float cal1=0.0,cal2;
	for(m=0;m<n;m++)
		cal1+=Excitation[m];
	DctCoeff[0]=float(sqrt(1.0/n)*cal1);
	for(k=1;k<n;k++)
	{
		cal2=0.0;
		for(m=0;m<n;m++)
			cal2+=float(Excitation[m]*cos((2*m+1)*k*pi/(2.0*n)));
		DctCoeff[k]=float(sqrt(2.0/n)*cal2);
	}

}

void PitchMod::IDCT()
{
	int i,k,m,n;
	n=len;
	if(n >= frame_l)
	{
		for(i=frame_l;i<n;i++)
			DctCoeff[i]=0.0;
	}
	else if(n < frame_l)
	{
		for(i=n;i<frame_l;i++)
			DctCoeff[i]=0.0;
	}
	IDctCoeff = new float [frame_l*2];
	float cal3;
	for(m=0;m<n;m++)
	{
		cal3=0.0;
		for(k=1;k<n;k++)
			cal3 += float(DctCoeff[k] * cos((2*m+1)*k*pi/(2.0*n)));
		IDctCoeff[m]=float(sqrt(1.0/n) * DctCoeff[0] + sqrt(2.0/n)*cal3);
	
	}
}

void PitchMod::LPC()
{
	int m_nSize=frame_l;

	int order=10,j=0,l=0;
	float *R = new float [m_nSize+1];
	int i;
	for(i=0;i<=m_nSize;i++)
		R[i] = 0.0;

	for(i=0;i<m_nSize;i++)
	{
		for(j=0;j<m_nSize-i;j++)
			R[i] = R[i] + frame[j] * frame[j+i];
	}
	
	
//	Levinson Durbin Algorithm
	
	float alpha_temp[11];
	float k[11];
	float temp;
	float error[11];

	LpcCoeff[0]=1;
	if(R[0]==0.0) 
    { 
		for(i=1; i<=order; i++) 
		{
			k[i]=0.0; 
			LpcCoeff[i]=0.0;
		}
    }
	else
	{
		error[0] = R[0];
		for(i=1;i<=order;i++)
		{
			temp=0.0;
			for(j=1;j<i;j++)
				temp += LpcCoeff[j] * R[i-j];
			k[i] = (R[i] - temp) / error[i-1];
			
			LpcCoeff[i] = k[i];
			for(j=1;j<i;j++)
			{
				alpha_temp[j] = LpcCoeff[j] -	k[i] * LpcCoeff[i-j];
				
			}
			error[i] = (1-k[i]*k[i]) * error[i-1];
			
			for(j=1;j<i;j++)
				LpcCoeff[j] = alpha_temp[j];
		}
	}
	
	for(i=1;i<=order;i++)
		LpcCoeff[i]=-1*LpcCoeff[i];
	
	delete [] R;

}

void PitchMod::Filter(float *b,float *a,float *x,int b_l,int a_l,int x_l)
{
	float s1,s2;
	int i,j,k;
	y= new float [x_l];
	for(i=0;i<x_l;i++)
		y[i]=0.0;
	for(i=0;i<x_l;i++)
	{
		j=0;
		s1=0.0;
		s2=0.0;
		for(k=i;k>=0;k--)
		{
			s1 += b[j]*x[k];
			j++;
			if(j >= b_l)
			break;
		}
		j=1;
		for(k=i-1;k>=0;k--)
		{
		   if( j >= a_l)
			break;
		   s2 += a[j]*y[k];
		   j++;
		   if(j >= a_l)
		   break;
		}
		y[i] = s1 - s2;
	}
}





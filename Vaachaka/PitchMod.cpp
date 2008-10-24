// PitchMod.cpp: implementation of the PitchMod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vaachaka.h"
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

	//storing the pitch marked indices in Find array
	for(i=0,j=0;i<PMS_l;i++)
	{
		if(PMark[i] == 1)
		{
			Find[j]=i;
			//TRACE("Find = %d\n",Find[j]);
			j++; // stores the no. of pitch marks
		}
	}
	count=j-1; // total no of pitch marks
	// Pitch modification
	in1=float(1.0);
	int f,fin,cnt,cc,k=0;
	float pe,*ccc;
	ccc = new float [count];
	if(Type == 1)//question
	{
		if(Mod_Count == 1)
		{
			in1=float(1.0);//in question,pitch should raise
			in2=float(1.1);//so from 1.0 to 1.1
		}
		else if(Mod_Count == 2)
		{
			in1 = float(1.0);
			in2 = float(1.1);
		}
	}
	else if(Type == 2)//exclamation
	{
		if(Mod_Count == 1)
		{
			in1 = float(1.0);//in exclmtn,pitch should raise
			in2 = float(1.1);//so from 1.0 to 1.1
		}
		else if(Mod_Count == 2)
		{
			in1=float(1.0);
			in2=float(1.1);
		}
	}
	else if(Type == 3)//comma
	{
		in1=float(1.0);//in comma,pitch should drop
		in2=float(0.95);//so from 1.0 to .95
	}
	else if(Type == 4)//dot
	{
		in1=float(1.0);//in dot,pitch should drop
		in2 = float(0.9);//so from 1.0 to .9
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
	while(j<count)//count contains total no. of pitch marks
	{
		k=0;
		//TRACE("\n Pass 1 i=%d,Find = %d",i,Find[j+1]);
		for(i=Find[j];i<=Find[j+1];i++) //read 1 frame data,from 1 pitchmark to another
		{
			frame[k]=Signal[i];
			k++;
		}	
		j=j+1; 
		frame_l=k-1; //no. of points in the frame
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

            Modifx[pml]=(sqrt(1.0*frame_l/len) * y[i]);
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
	}//endof loop for all pitch marks
	pml--;
	delete [] ccc;
	TRACE("\nOut of PM");
}//Modification()


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

	// here first marking the points which has max. peak value
	while(maxim+framelength < siz)
	{
		short int maximum=0,maxi=0;
		for(i=maxim;i<maxim+framelength;i++)
		{
			
			if(maximum < input[i])
			{
				maximum=input[i];
				maxi=i-maxim;//could have used: maxi=i
			}
		}
		//TRACE("\n maxim+maxi = %d",maxim+maxi);
		PMark[int(maxim + maxi)] = 1;//could have used:PMark[int(maxi)]=1
		maxim = int(framelength * 0.5) + maxim;
	}
/*	i=1;

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
*/
	// Implement find 
//here we r storing those indexes where we had stored value 1 earlier
	for(i=0,j=0;i<siz;i++)
	{
		if(PMark[i] == 1)
		{
			C[j]=i;
			j++;
		}
	}
	j=j-1;//j gives the number of peaks(pitch marks) recognised
	
//here if the points r v close,then at those points remove the 1 values
	for(i=0;i<j-1;i++)
	{	
		//TRACE(" C = %d",C[i]);
		if (abs(C[i]-C[i+1])<=30)
			PMark[C[i+1]]=0;
	}
	
	/*delete C;
	delete input;*/	
}//PitchMark()


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
	int m_nSize=frame_l;//no. of points in the frame

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

}//LPC()


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

// PitchMod.h: interface for the PitchMod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PITCHMOD_H__09038441_3373_11D7_81EB_002018385B14__INCLUDED_)
#define AFX_PITCHMOD_H__09038441_3373_11D7_81EB_002018385B14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Doc.h"

class PitchMod : public CDocument  
{
public:
	PitchMod();
	virtual ~PitchMod();
	void Modification();
	void PitchMark();
	int Mean();
	void FDCT();
	void IDCT();
	void LPC();	
	void Filter(float *b,float *a,float *x,int b_l,int a_l,int x_l);

	short int *PMSignal;
	float *Signal;
	short int *Modifx;
	float frame[15000];
	int PMS_l,APitch,count,frame_l;
	int Type,len;
	float *DctCoeff,*IDctCoeff;
	short int *PMark;
	int *Find;
	int pml;
	float LpcCoeff[11];
	float *Excitation;
	float *y;
	float *Output;
	int len_modifx;
	short int Mod_Count;

};

#endif // !defined(AFX_PITCHMOD_H__09038441_3373_11D7_81EB_002018385B14__INCLUDED_)
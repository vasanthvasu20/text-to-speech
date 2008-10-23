// PitchMod.h: interface for the PitchMod class.

/**********************************************************************
 * File:                PitchMod.h  
 * Description:         
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

//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PITCHMOD_H__FE7E5C25_6F92_11D5_935E_002018385B14__INCLUDED_)
#define AFX_PITCHMOD_H__FE7E5C25_6F92_11D5_935E_002018385B14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Doc.h"

class PitchMod : public CDoc  
{
public:
	PitchMod();
	virtual ~PitchMod();
	short int *PMSignal;
	float *Signal;
	short int *Modifx;
	float frame[300];
	int PMS_l,APitch,count,frame_l;
	void Modification();
	void PitchMark();
	int Mean();
	void LPC();
	void Filter(float *b,float *a,float *x,int b_l,int a_l,int x_l);
	void FDCT();
	void IDCT();
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

	//float* XCorr(short int *in);

};

#endif // !defined(AFX_PITCHMOD_H__FE7E5C25_6F92_11D5_935E_002018385B14__INCLUDED_)

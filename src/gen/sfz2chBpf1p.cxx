/* ------------------------------------------------------------
name: "sfz_filters"
Code generated with Faust 2.20.2 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faust2chBpf1p_H__
#define  __faust2chBpf1p_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS faust2chBpf1p
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust2chBpf1p : public dsp {
	
 public:
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fCutoff;
	float fRec2[2];
	float fRec1[2];
	float fRec0[2];
	float fRec4[2];
	float fRec3[2];
	
 public:
	
	void metadata(Meta* m) { 
	}

	 int getNumInputs() {
		return 2;
	}
	 int getNumOutputs() {
		return 2;
	}
	 int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	 int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	 void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = (1.0f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate))));
	}
	
	 void instanceResetUserInterface() {
		fCutoff = FAUSTFLOAT(440.0f);
	}
	
	 void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
		}
	}
	
	 void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	 void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	 faust2chBpf1p* clone() {
		return new faust2chBpf1p();
	}
	
	 int getSampleRate() {
		return fSampleRate;
	}
	
	 void buildUserInterface(UI* ui_interface) {
	}
	
	 void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * std::exp((fConst0 * (0.0f - (6.28318548f * float(fCutoff))))));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec2[0] = (fSlow0 + (0.999000013f * fRec2[1]));
			fRec1[0] = (float(input0[i]) + (fRec2[0] * fRec1[1]));
			float fTemp0 = (1.0f - fRec2[0]);
			fRec0[0] = ((fRec1[0] * fTemp0) + (fRec2[0] * fRec0[1]));
			float fTemp1 = (fRec2[0] + 1.0f);
			float fTemp2 = (0.0f - (0.5f * fTemp1));
			output0[i] = FAUSTFLOAT(((0.5f * (fRec0[0] * fTemp1)) + (fRec0[1] * fTemp2)));
			fRec4[0] = (float(input1[i]) + (fRec2[0] * fRec4[1]));
			fRec3[0] = ((fRec4[0] * fTemp0) + (fRec2[0] * fRec3[1]));
			output1[i] = FAUSTFLOAT(((0.5f * (fRec3[0] * fTemp1)) + (fTemp2 * fRec3[1])));
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#endif

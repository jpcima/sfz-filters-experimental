/* ------------------------------------------------------------
name: "sfz_filters"
Code generated with Faust 2.20.2 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faustHpf6p_H__
#define  __faustHpf6p_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS faustHpf6p
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faustHpf6p : public dsp {
	
 public:
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fCutoff;
	FAUSTFLOAT fQ;
	float fRec0[2];
	float fRec4[2];
	float fRec5[2];
	float fRec3[3];
	float fRec6[2];
	float fRec2[3];
	float fRec1[3];
	
 public:
	
	void metadata(Meta* m) { 
	}

	 int getNumInputs() {
		return 1;
	}
	 int getNumOutputs() {
		return 1;
	}
	 int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
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
		fConst0 = (6.28318548f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate))));
	}
	
	 void instanceResetUserInterface() {
		fCutoff = FAUSTFLOAT(440.0f);
		fQ = FAUSTFLOAT(0.0f);
	}
	
	 void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec5[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec6[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec1[l6] = 0.0f;
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
	
	 faustHpf6p* clone() {
		return new faustHpf6p();
	}
	
	 int getSampleRate() {
		return fSampleRate;
	}
	
	 void buildUserInterface(UI* ui_interface) {
	}
	
	 void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (fConst0 * std::max<float>(0.0f, float(fCutoff)));
		float fSlow1 = std::cos(fSlow0);
		float fSlow2 = (0.5f * (std::sin(fSlow0) / std::max<float>(0.00100000005f, std::pow(10.0f, (0.0500000007f * float(fQ))))));
		float fSlow3 = (fSlow2 + 1.0f);
		float fSlow4 = (0.00100000005f * ((-1.0f - fSlow1) / fSlow3));
		float fSlow5 = (0.00100000005f * ((0.0f - (2.0f * fSlow1)) / fSlow3));
		float fSlow6 = (0.00100000005f * ((1.0f - fSlow2) / fSlow3));
		float fSlow7 = (0.000500000024f * ((fSlow1 + 1.0f) / fSlow3));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow4 + (0.999000013f * fRec0[1]));
			fRec4[0] = (fSlow5 + (0.999000013f * fRec4[1]));
			fRec5[0] = (fSlow6 + (0.999000013f * fRec5[1]));
			fRec3[0] = (float(input0[i]) - ((fRec4[0] * fRec3[1]) + (fRec5[0] * fRec3[2])));
			fRec6[0] = (fSlow7 + (0.999000013f * fRec6[1]));
			fRec2[0] = (((fRec0[0] * fRec3[1]) + (fRec6[0] * (fRec3[0] + fRec3[2]))) - ((fRec4[0] * fRec2[1]) + (fRec5[0] * fRec2[2])));
			fRec1[0] = (((fRec0[0] * fRec2[1]) + (fRec6[0] * (fRec2[0] + fRec2[2]))) - ((fRec4[0] * fRec1[1]) + (fRec5[0] * fRec1[2])));
			output0[i] = FAUSTFLOAT(((fRec0[0] * fRec1[1]) + (fRec6[0] * (fRec1[0] + fRec1[2]))));
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec6[1] = fRec6[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
		}
	}

};

#endif

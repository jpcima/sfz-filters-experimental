/* ------------------------------------------------------------
name: "sfz_filters"
Code generated with Faust 2.20.2 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faustBpf4p_H__
#define  __faustBpf4p_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS faustBpf4p
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faustBpf4p : public dsp {
	
 public:
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fCutoff;
	FAUSTFLOAT fQ;
	float fRec0[2];
	float fRec3[2];
	float fRec4[2];
	float fRec2[3];
	float fRec5[2];
	float fRec6[2];
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
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec4[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
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
	
	 faustBpf4p* clone() {
		return new faustBpf4p();
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
		float fSlow1 = std::sin(fSlow0);
		float fSlow2 = std::max<float>(0.00100000005f, std::pow(10.0f, (0.0500000007f * float(fQ))));
		float fSlow3 = (0.5f * (fSlow1 / fSlow2));
		float fSlow4 = (fSlow3 + 1.0f);
		float fSlow5 = (fSlow1 / (fSlow2 * fSlow4));
		float fSlow6 = (0.000500000024f * fSlow5);
		float fSlow7 = (0.00100000005f * ((0.0f - (2.0f * std::cos(fSlow0))) / fSlow4));
		float fSlow8 = (0.00100000005f * ((1.0f - fSlow3) / fSlow4));
		float fSlow9 = (0.00100000005f * (0.0f - (0.5f * fSlow5)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow6 + (0.999000013f * fRec0[1]));
			fRec3[0] = (fSlow7 + (0.999000013f * fRec3[1]));
			fRec4[0] = (fSlow8 + (0.999000013f * fRec4[1]));
			fRec2[0] = (float(input0[i]) - ((fRec3[0] * fRec2[1]) + (fRec4[0] * fRec2[2])));
			fRec5[0] = (0.999000013f * fRec5[1]);
			fRec6[0] = (fSlow9 + (0.999000013f * fRec6[1]));
			fRec1[0] = ((((fRec2[0] * fRec0[0]) + (fRec5[0] * fRec2[1])) + (fRec6[0] * fRec2[2])) - ((fRec3[0] * fRec1[1]) + (fRec4[0] * fRec1[2])));
			output0[i] = FAUSTFLOAT((((fRec0[0] * fRec1[0]) + (fRec5[0] * fRec1[1])) + (fRec6[0] * fRec1[2])));
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
		}
	}

};

#endif

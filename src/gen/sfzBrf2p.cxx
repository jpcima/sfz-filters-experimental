/* ------------------------------------------------------------
name: "sfz_filters"
Code generated with Faust 2.20.2 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faustBrf2p_H__
#define  __faustBrf2p_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS faustBrf2p
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faustBrf2p : public dsp {
	
 public:
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fCutoff;
	FAUSTFLOAT fQ;
	float fRec0[2];
	float fRec2[2];
	float fRec1[3];
	float fRec3[2];
	
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
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
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
	
	 faustBrf2p* clone() {
		return new faustBrf2p();
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
		float fSlow1 = (0.5f * (std::sin(fSlow0) / std::max<float>(0.00100000005f, std::pow(10.0f, (0.0500000007f * float(fQ))))));
		float fSlow2 = (fSlow1 + 1.0f);
		float fSlow3 = (0.00100000005f * ((0.0f - (2.0f * std::cos(fSlow0))) / fSlow2));
		float fSlow4 = (0.00100000005f * ((1.0f - fSlow1) / fSlow2));
		float fSlow5 = (0.00100000005f / fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow3 + (0.999000013f * fRec0[1]));
			float fTemp0 = (fRec0[0] * fRec1[1]);
			fRec2[0] = (fSlow4 + (0.999000013f * fRec2[1]));
			fRec1[0] = (float(input0[i]) - (fTemp0 + (fRec2[0] * fRec1[2])));
			fRec3[0] = (fSlow5 + (0.999000013f * fRec3[1]));
			output0[i] = FAUSTFLOAT((fTemp0 + (fRec3[0] * (fRec1[0] + fRec1[2]))));
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#endif

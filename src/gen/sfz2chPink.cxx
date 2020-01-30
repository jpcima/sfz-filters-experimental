/* ------------------------------------------------------------
name: "sfz_filters"
Code generated with Faust 2.20.2 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faust2chPink_H__
#define  __faust2chPink_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>


#ifndef FAUSTCLASS 
#define FAUSTCLASS faust2chPink
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust2chPink : public dsp {
	
 public:
	
	float fRec0[4];
	float fRec1[4];
	int fSampleRate;
	
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
	}
	
	 void instanceResetUserInterface() {
	}
	
	 void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
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
	
	 faust2chPink* clone() {
		return new faust2chPink();
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
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = ((float(input0[i]) + ((2.49495602f * fRec0[1]) + (0.522189379f * fRec0[3]))) - (2.0172658f * fRec0[2]));
			output0[i] = FAUSTFLOAT((((0.0499220341f * fRec0[0]) + (0.0506126992f * fRec0[2])) - ((0.0959935337f * fRec0[1]) + (0.00440878607f * fRec0[3]))));
			fRec1[0] = ((float(input1[i]) + ((2.49495602f * fRec1[1]) + (0.522189379f * fRec1[3]))) - (2.0172658f * fRec1[2]));
			output1[i] = FAUSTFLOAT((((0.0499220341f * fRec1[0]) + (0.0506126992f * fRec1[2])) - ((0.0959935337f * fRec1[1]) + (0.00440878607f * fRec1[3]))));
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec0[j0] = fRec0[(j0 - 1)];
			}
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec1[j1] = fRec1[(j1 - 1)];
			}
		}
	}

};

#endif

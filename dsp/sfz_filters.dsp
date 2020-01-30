import("stdfaust.lib");
fm = library("filters_modulable.dsp");
sk = library("sallenkey_modulable.dsp");

//==============================================================================
// Generators

// the SFZ *noise generator
sfzNoise = no.noise : *(gate) : *(0.25);

//==============================================================================
// Filters

// the SFZ lowpass 1-pole filter
sfzLpf1p = fm.lp1Smooth(smoothCoefs,cutoff);

// the SFZ lowpass 2-pole filter
sfzLpf2p = fm.rbjLpfSmooth(smoothCoefs,cutoff,0.,Q);

// the SFZ lowpass 4-pole filter
sfzLpf4p = sfzLpf2p : sfzLpf2p;

// the SFZ lowpass 6-pole filter
sfzLpf6p = sfzLpf2p : sfzLpf2p : sfzLpf2p;

// the SFZ highpass 1-pole filter
sfzHpf1p = fm.hp1Smooth(smoothCoefs,cutoff);

// the SFZ highpass 2-pole filter
sfzHpf2p = fm.rbjHpfSmooth(smoothCoefs,cutoff,0.,Q);

// the SFZ highpass 4-pole filter
sfzHpf4p = sfzHpf2p : sfzHpf2p;

// the SFZ highpass 6-pole filter
sfzHpf6p = sfzHpf2p : sfzHpf2p : sfzHpf2p;

// the SFZ bandpass 1-pole filter
sfzBpf1p = sfzLpf1p : sfzHpf1p;

// the SFZ bandpass 2-pole filter
sfzBpf2p = fm.rbjBpfSmooth(smoothCoefs,cutoff,0.,Q);

// the SFZ bandpass 4-pole filter
//   Note: bpf_4p not in specification but here anyway
sfzBpf4p = sfzBpf2p : sfzBpf2p;

// the SFZ bandpass 6-pole filter
//   Note: bpf_6p not in specification but here anyway
sfzBpf6p = sfzBpf2p : sfzBpf2p : sfzBpf2p;

// the SFZ allpass 1-pole filter
sfzApf1p = fm.ap1Smooth(smoothCoefs,cutoff);

// the SFZ notch 1-pole filter
//   Note: this thing is my invention, may not be correct.
//         in Sforzando, 1p seems implemented the same as 2p.
sfzBrf1p = _ <: (_, (sfzApf1p : sfzApf1p)) :> +;

// the SFZ notch 2-pole filter
sfzBrf2p = fm.rbjNotchSmooth(smoothCoefs,cutoff,0.,Q);

// the SFZ pink filter
sfzPink = no.pink_filter;

// the SFZ 2-pole state-variable lowpass filter
sfzLpf2pSv = sk.sallenKey2ndOrderLPF(smoothCoefs,cutoff,Q);

// the SFZ 2-pole state-variable highpass filter
sfzHpf2pSv = sk.sallenKey2ndOrderHPF(smoothCoefs,cutoff,Q);

// the SFZ 2-pole state-variable bandpass filter
//   Note: attenuate in order to have the resonant peak at 0 dB (same as sfzBpf2p)
sfzBpf2pSv = sk.sallenKey2ndOrderBPF(smoothCoefs,cutoff,Q) : *((1./Q):smoothCoefs);

// the SFZ 2-pole state-variable notch filter
sfzBrf2pSv = _ <: (sfzLpf2pSv, sfzHpf2pSv) :> +;

// the SFZ low-shelf filter
sfzLsh = fm.rbjLowShelfSmooth(smoothCoefs,cutoff,pkShGain,Q);

// the SFZ high-shelf filter
sfzHsh = fm.rbjHighShelfSmooth(smoothCoefs,cutoff,pkShGain,Q);

//==============================================================================
// Filters (stereo)

sfz2chLpf1p = par(i,2,sfzLpf1p);
sfz2chLpf2p = par(i,2,sfzLpf2p);
sfz2chLpf4p = par(i,2,sfzLpf4p);
sfz2chLpf6p = par(i,2,sfzLpf6p);
sfz2chHpf1p = par(i,2,sfzHpf1p);
sfz2chHpf2p = par(i,2,sfzHpf2p);
sfz2chHpf4p = par(i,2,sfzHpf4p);
sfz2chHpf6p = par(i,2,sfzHpf6p);
sfz2chBpf1p = par(i,2,sfzBpf1p);
sfz2chBpf2p = par(i,2,sfzBpf2p);
sfz2chBpf4p = par(i,2,sfzBpf4p);
sfz2chBpf6p = par(i,2,sfzBpf6p);
sfz2chApf1p = par(i,2,sfzApf1p);
sfz2chBrf1p = par(i,2,sfzBrf1p);
sfz2chBrf2p = par(i,2,sfzBrf2p);
sfz2chPink = par(i,2,sfzPink);
sfz2chLpf2pSv = par(i,2,sfzLpf2pSv);
sfz2chHpf2pSv = par(i,2,sfzHpf2pSv);
sfz2chBpf2pSv = par(i,2,sfzBpf2pSv);
sfz2chBrf2pSv = par(i,2,sfzBrf2pSv);
sfz2chLsh = par(i,2,sfzLsh);
sfz2chHsh = par(i,2,sfzHsh);

//==============================================================================
// Filter parameters

cutoff = hslider("[01] Cutoff [unit:Hz] [scale:log]", 440.0, 50.0, 10000.0, 1.0);
Q = vslider("[02] Resonance [unit:dB]", 0.0, 0.0, 40.0, 0.1) : ba.db2linear;
pkShGain = vslider("[03] Peak/shelf gain [unit:dB]", 0.0, 0.0, 40.0, 0.1) : ba.db2linear;

// smoothing function to prevent fast changes of filter coefficients
smoothCoefs = si.smoo; // TODO check if this is appropriate otherwise replace

//==============================================================================
// Example

gate = checkbox("[03] White noise");

switchedLp1p = _ <: (_, sfzLpf1p) : select2(checkbox("[04] Enable Lp 1p"));
switchedLp2p = _ <: (_, sfzLpf2p) : select2(checkbox("[05] Enable Lp 2p"));
switchedLp4p = _ <: (_, sfzLpf4p) : select2(checkbox("[06] Enable Lp 4p"));
switchedLp6p = _ <: (_, sfzLpf6p) : select2(checkbox("[07] Enable Lp 6p"));
switchedHp1p = _ <: (_, sfzHpf1p) : select2(checkbox("[04] Enable Hp 1p"));
switchedHp2p = _ <: (_, sfzHpf2p) : select2(checkbox("[08] Enable Hp 2p"));
switchedHp4p = _ <: (_, sfzHpf4p) : select2(checkbox("[09] Enable Hp 4p"));
switchedHp6p = _ <: (_, sfzHpf6p) : select2(checkbox("[10] Enable Hp 6p"));
switchedBp1p = _ <: (_, sfzBpf1p) : select2(checkbox("[11] Enable Bp 1p"));
switchedBp2p = _ <: (_, sfzBpf2p) : select2(checkbox("[12] Enable Bp 2p"));
switchedBp4p = _ <: (_, sfzBpf4p) : select2(checkbox("[13] Enable Bp 4p"));
switchedBp6p = _ <: (_, sfzBpf6p) : select2(checkbox("[14] Enable Bp 6p"));
switchedAp1p = _ <: (_, sfzApf1p) : select2(checkbox("[15] Enable Ap 1p"));
switchedBr1p = _ <: (_, sfzBrf1p) : select2(checkbox("[16] Enable Br 1p"));
switchedBr2p = _ <: (_, sfzBrf2p) : select2(checkbox("[17] Enable Br 2p"));
switchedPink = _ <: (_, sfzPink) : select2(checkbox("[18] Enable Pink"));

process = sfzNoise : filterChain <: (_, _) with {
  filterChain =
    switchedLp1p : switchedLp2p : switchedLp4p : switchedLp6p :
    switchedHp1p : switchedHp2p : switchedHp4p : switchedHp6p :
    switchedBp1p : switchedBp2p : switchedBp4p : switchedBp6p :
    switchedAp1p :
    switchedBr1p : switchedBr2p :
    switchedPink;
};

struct dsp {};
struct Meta {};
struct UI {};

#include "gen/sfzApf1p.cxx"
#include "gen/sfzBpf1p.cxx"
#include "gen/sfzBpf2p.cxx"
#include "gen/sfzBpf4p.cxx"
#include "gen/sfzBpf6p.cxx"
#include "gen/sfzBrf1p.cxx"
#include "gen/sfzBrf2p.cxx"
#include "gen/sfzHpf1p.cxx"
#include "gen/sfzHpf2p.cxx"
#include "gen/sfzHpf4p.cxx"
#include "gen/sfzHpf6p.cxx"
#include "gen/sfzLpf1p.cxx"
#include "gen/sfzLpf2p.cxx"
#include "gen/sfzLpf4p.cxx"
#include "gen/sfzLpf6p.cxx"
#include "gen/sfzPink.cxx"

#include "gen/sfz2chApf1p.cxx"
#include "gen/sfz2chBpf1p.cxx"
#include "gen/sfz2chBpf2p.cxx"
#include "gen/sfz2chBpf4p.cxx"
#include "gen/sfz2chBpf6p.cxx"
#include "gen/sfz2chBrf1p.cxx"
#include "gen/sfz2chBrf2p.cxx"
#include "gen/sfz2chHpf1p.cxx"
#include "gen/sfz2chHpf2p.cxx"
#include "gen/sfz2chHpf4p.cxx"
#include "gen/sfz2chHpf6p.cxx"
#include "gen/sfz2chLpf1p.cxx"
#include "gen/sfz2chLpf2p.cxx"
#include "gen/sfz2chLpf4p.cxx"
#include "gen/sfz2chLpf6p.cxx"
#include "gen/sfz2chPink.cxx"

template <class F> struct sfzFilter : public F {
    void setCutoff(float v) { F::fCutoff = v; }
    void setQ(float v) { F::fQ = v; }
};

template <class F> struct sfzFilterNoQ : public F {
    void setCutoff(float v) { F::fCutoff = v; }
    void setQ(float) {}
};

template <class F> struct sfzFilterNoCutoff : public F {
    void setCutoff(float) {}
    void setQ(float) {}
};

template <unsigned NCh> struct sfzLpf1p;
template <unsigned NCh> struct sfzLpf2p;
template <unsigned NCh> struct sfzLpf4p;
template <unsigned NCh> struct sfzLpf6p;
template <unsigned NCh> struct sfzHpf1p;
template <unsigned NCh> struct sfzHpf2p;
template <unsigned NCh> struct sfzHpf4p;
template <unsigned NCh> struct sfzHpf6p;
template <unsigned NCh> struct sfzBpf1p;
template <unsigned NCh> struct sfzBpf2p;
template <unsigned NCh> struct sfzBpf4p;
template <unsigned NCh> struct sfzBpf6p;
template <unsigned NCh> struct sfzApf1p;
template <unsigned NCh> struct sfzBrf1p;
template <unsigned NCh> struct sfzBrf2p;
template <unsigned NCh> struct sfzPink;

template<> struct sfzLpf1p<1> : public sfzFilterNoQ<faustLpf1p> {};
template<> struct sfzLpf2p<1> : public sfzFilter<faustLpf2p> {};
template<> struct sfzLpf4p<1> : public sfzFilter<faustLpf4p> {};
template<> struct sfzLpf6p<1> : public sfzFilter<faustLpf6p> {};
template<> struct sfzHpf1p<1> : public sfzFilterNoQ<faustHpf1p> {};
template<> struct sfzHpf2p<1> : public sfzFilter<faustHpf2p> {};
template<> struct sfzHpf4p<1> : public sfzFilter<faustHpf4p> {};
template<> struct sfzHpf6p<1> : public sfzFilter<faustHpf6p> {};
template<> struct sfzBpf1p<1> : public sfzFilterNoQ<faustBpf1p> {};
template<> struct sfzBpf2p<1> : public sfzFilter<faustBpf2p> {};
template<> struct sfzBpf4p<1> : public sfzFilter<faustBpf4p> {};
template<> struct sfzBpf6p<1> : public sfzFilter<faustBpf6p> {};
template<> struct sfzApf1p<1> : public sfzFilterNoQ<faustApf1p> {};
template<> struct sfzBrf1p<1> : public sfzFilterNoQ<faustBrf1p> {};
template<> struct sfzBrf2p<1> : public sfzFilter<faustBrf2p> {};
template<> struct sfzPink<1> : public sfzFilterNoCutoff<faustPink> {};

template<> struct sfzLpf1p<2> : public sfzFilterNoQ<faust2chLpf1p> {};
template<> struct sfzLpf2p<2> : public sfzFilter<faust2chLpf2p> {};
template<> struct sfzLpf4p<2> : public sfzFilter<faust2chLpf4p> {};
template<> struct sfzLpf6p<2> : public sfzFilter<faust2chLpf6p> {};
template<> struct sfzHpf1p<2> : public sfzFilterNoQ<faust2chHpf1p> {};
template<> struct sfzHpf2p<2> : public sfzFilter<faust2chHpf2p> {};
template<> struct sfzHpf4p<2> : public sfzFilter<faust2chHpf4p> {};
template<> struct sfzHpf6p<2> : public sfzFilter<faust2chHpf6p> {};
template<> struct sfzBpf1p<2> : public sfzFilterNoQ<faust2chBpf1p> {};
template<> struct sfzBpf2p<2> : public sfzFilter<faust2chBpf2p> {};
template<> struct sfzBpf4p<2> : public sfzFilter<faust2chBpf4p> {};
template<> struct sfzBpf6p<2> : public sfzFilter<faust2chBpf6p> {};
template<> struct sfzApf1p<2> : public sfzFilterNoQ<faust2chApf1p> {};
template<> struct sfzBrf1p<2> : public sfzFilterNoQ<faust2chBrf1p> {};
template<> struct sfzBrf2p<2> : public sfzFilter<faust2chBrf2p> {};
template<> struct sfzPink<2> : public sfzFilterNoCutoff<faust2chPink> {};

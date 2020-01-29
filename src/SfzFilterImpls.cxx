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

struct sfzLpf1p : public sfzFilterNoQ<faustLpf1p> {};
struct sfzLpf2p : public sfzFilter<faustLpf2p> {};
struct sfzLpf4p : public sfzFilter<faustLpf4p> {};
struct sfzLpf6p : public sfzFilter<faustLpf6p> {};
struct sfzHpf1p : public sfzFilterNoQ<faustHpf1p> {};
struct sfzHpf2p : public sfzFilter<faustHpf2p> {};
struct sfzHpf4p : public sfzFilter<faustHpf4p> {};
struct sfzHpf6p : public sfzFilter<faustHpf6p> {};
struct sfzBpf1p : public sfzFilterNoQ<faustBpf1p> {};
struct sfzBpf2p : public sfzFilter<faustBpf2p> {};
struct sfzBpf4p : public sfzFilter<faustBpf4p> {};
struct sfzBpf6p : public sfzFilter<faustBpf6p> {};
struct sfzApf1p : public sfzFilterNoQ<faustApf1p> {};
struct sfzBrf1p : public sfzFilterNoQ<faustBrf1p> {};
struct sfzBrf2p : public sfzFilter<faustBrf2p> {};
struct sfzPink : public sfzFilterNoCutoff<faustPink> {};

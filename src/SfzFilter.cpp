#include "SfzFilter.h"
#include "SfzFilterDefs.h"
#include "SfzFilterImpls.cxx"
#include <cstring>
#include <cassert>

struct SfzFilter::Impl {
    SfzFilterType fType = kSfzFilterNone;

    sfzLpf1p fDspLpf1p;
    sfzLpf2p fDspLpf2p;
    sfzLpf4p fDspLpf4p;
    sfzLpf6p fDspLpf6p;
    sfzHpf1p fDspHpf1p;
    sfzHpf2p fDspHpf2p;
    sfzHpf4p fDspHpf4p;
    sfzHpf6p fDspHpf6p;
    sfzBpf1p fDspBpf1p;
    sfzBpf2p fDspBpf2p;
    sfzBpf4p fDspBpf4p;
    sfzBpf6p fDspBpf6p;
    sfzApf1p fDspApf1p;
    sfzBrf1p fDspBrf1p;
    sfzBrf2p fDspBrf2p;
    sfzPink fDspPink;

    template <class F> static void process(F &filter, const float *in, float *out, float cutoff, float q, unsigned nframes);
    template <class F> static void processModulated(F &filter, const float *in, float *out, const float *cutoff, const float *q, unsigned nframes);
    void updateParameters();
};

SfzFilter::SfzFilter()
    : P{new Impl}
{
}

SfzFilter::~SfzFilter()
{
}

void SfzFilter::init(double sampleRate)
{
    P->fDspLpf1p.init(sampleRate);
    P->fDspLpf2p.init(sampleRate);
    P->fDspLpf4p.init(sampleRate);
    P->fDspLpf6p.init(sampleRate);
    P->fDspHpf1p.init(sampleRate);
    P->fDspHpf2p.init(sampleRate);
    P->fDspHpf4p.init(sampleRate);
    P->fDspHpf6p.init(sampleRate);
    P->fDspBpf1p.init(sampleRate);
    P->fDspBpf2p.init(sampleRate);
    P->fDspBpf4p.init(sampleRate);
    P->fDspBpf6p.init(sampleRate);
    P->fDspApf1p.init(sampleRate);
    P->fDspBrf1p.init(sampleRate);
    P->fDspBrf2p.init(sampleRate);
    P->fDspPink.init(sampleRate);
}

void SfzFilter::clear()
{
    switch (P->fType) {
    case kSfzFilterNone: break;
    case kSfzFilterApf1p: P->fDspApf1p.instanceClear(); break;
    case kSfzFilterBpf1p: P->fDspBpf1p.instanceClear(); break;
    case kSfzFilterBpf2p: P->fDspBpf2p.instanceClear(); break;
    case kSfzFilterBpf4p: P->fDspBpf4p.instanceClear(); break;
    case kSfzFilterBpf6p: P->fDspBpf6p.instanceClear(); break;
    case kSfzFilterBrf1p: P->fDspBrf1p.instanceClear(); break;
    case kSfzFilterBrf2p: P->fDspBrf2p.instanceClear(); break;
    case kSfzFilterHpf1p: P->fDspHpf1p.instanceClear(); break;
    case kSfzFilterHpf2p: P->fDspHpf2p.instanceClear(); break;
    case kSfzFilterHpf4p: P->fDspHpf4p.instanceClear(); break;
    case kSfzFilterHpf6p: P->fDspHpf6p.instanceClear(); break;
    case kSfzFilterLpf1p: P->fDspLpf1p.instanceClear(); break;
    case kSfzFilterLpf2p: P->fDspLpf2p.instanceClear(); break;
    case kSfzFilterLpf4p: P->fDspLpf4p.instanceClear(); break;
    case kSfzFilterLpf6p: P->fDspLpf6p.instanceClear(); break;
    case kSfzFilterPink: P->fDspPink.instanceClear(); break;
    }
}

template <class F>
void SfzFilter::Impl::process(F &filter, const float *in, float *out, float cutoff, float q, unsigned nframes)
{
    filter.setCutoff(cutoff);
    filter.setQ(q);
    filter.compute(nframes, const_cast<float **>(&in), &out);
}

void SfzFilter::process(const float *in, float *out, float cutoff, float q, unsigned nframes)
{
    if (P->fType == kSfzFilterNone) {
        if (in != out)
            std::memcpy(out, in, nframes * sizeof(float));
        return;
    }

    switch (P->fType) {
    case kSfzFilterApf1p: P->process(P->fDspApf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf1p: P->process(P->fDspBpf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf2p: P->process(P->fDspBpf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf4p: P->process(P->fDspBpf4p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf6p: P->process(P->fDspBpf6p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBrf1p: P->process(P->fDspBrf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBrf2p: P->process(P->fDspBrf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf1p: P->process(P->fDspHpf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf2p: P->process(P->fDspHpf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf4p: P->process(P->fDspHpf4p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf6p: P->process(P->fDspHpf6p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf1p: P->process(P->fDspLpf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf2p: P->process(P->fDspLpf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf4p: P->process(P->fDspLpf4p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf6p: P->process(P->fDspLpf6p, in, out, cutoff, q, nframes); break;
    case kSfzFilterPink: P->process(P->fDspPink, in, out, cutoff, q, nframes); break;
    default: assert(false);
    }
}

template <class F>
void SfzFilter::Impl::processModulated(F &filter, const float *in, float *out, const float *cutoff, const float *q, unsigned nframes)
{
    unsigned frame = 0;

    while (frame < nframes) {
        size_t current = nframes - frame;

        if (current > kSfzFilterControlInterval)
            current = kSfzFilterControlInterval;

        const float *current_in = in + frame;
        float *current_out = out + frame;

        filter.setCutoff(cutoff[frame]);
        filter.setQ(q[frame]);
        filter.compute(nframes, const_cast<float **>(&current_in), &current_out);

        frame += current;
    }
}

void SfzFilter::processModulated(const float *in, float *out, const float *cutoff, const float *q, unsigned nframes)
{
    if (P->fType == kSfzFilterNone) {
        if (in != out)
            std::memcpy(out, in, nframes * sizeof(float));
        return;
    }

    switch (P->fType) {
    case kSfzFilterApf1p: P->processModulated(P->fDspApf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf1p: P->processModulated(P->fDspBpf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf2p: P->processModulated(P->fDspBpf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf4p: P->processModulated(P->fDspBpf4p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBpf6p: P->processModulated(P->fDspBpf6p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBrf1p: P->processModulated(P->fDspBrf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterBrf2p: P->processModulated(P->fDspBrf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf1p: P->processModulated(P->fDspHpf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf2p: P->processModulated(P->fDspHpf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf4p: P->processModulated(P->fDspHpf4p, in, out, cutoff, q, nframes); break;
    case kSfzFilterHpf6p: P->processModulated(P->fDspHpf6p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf1p: P->processModulated(P->fDspLpf1p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf2p: P->processModulated(P->fDspLpf2p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf4p: P->processModulated(P->fDspLpf4p, in, out, cutoff, q, nframes); break;
    case kSfzFilterLpf6p: P->processModulated(P->fDspLpf6p, in, out, cutoff, q, nframes); break;
    case kSfzFilterPink: P->processModulated(P->fDspPink, in, out, cutoff, q, nframes); break;
    default: assert(false);
    }
}

SfzFilterType SfzFilter::type() const
{
    return P->fType;
}

void SfzFilter::setType(SfzFilterType type)
{
    if (P->fType != type) {
        P->fType = type;
        clear();
    }
}

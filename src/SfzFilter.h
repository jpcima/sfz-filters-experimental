#pragma once
#include <memory>

enum SfzFilterType : int;

template <unsigned NCh>
class SfzFilter {
public:
    SfzFilter();
    ~SfzFilter();

    void init(double sampleRate);
    void clear();

    void process(const float *const in[NCh], float *const out[NCh], float cutoff, float q, unsigned nframes);
    void processModulated(const float *const in[NCh], float *const out[NCh], const float *cutoff, const float *q, unsigned nframes);

    SfzFilterType type() const;
    void setType(SfzFilterType type);

private:
    struct Impl;
    std::unique_ptr<Impl> P;
};

enum SfzFilterType : int {
    kSfzFilterNone,
    kSfzFilterApf1p,
    kSfzFilterBpf1p,
    kSfzFilterBpf2p,
    kSfzFilterBpf4p,
    kSfzFilterBpf6p,
    kSfzFilterBrf1p,
    kSfzFilterBrf2p,
    kSfzFilterHpf1p,
    kSfzFilterHpf2p,
    kSfzFilterHpf4p,
    kSfzFilterHpf6p,
    kSfzFilterLpf1p,
    kSfzFilterLpf2p,
    kSfzFilterLpf4p,
    kSfzFilterLpf6p,
    kSfzFilterPink,
};

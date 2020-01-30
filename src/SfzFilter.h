// SPDX-License-Identifier: BSD-2-Clause

// This code is part of the sfizz library and is licensed under a BSD 2-clause
// license. You should have receive a LICENSE.md file along with the code.
// If not, contact the sfizz maintainers at https://github.com/sfztools/sfizz

#pragma once
#include <memory>

enum SfzFilterType : int;

/**
   Multi-mode filter for SFZ v2
   Available for mono and stereo. (NCh=1, NCh=2)
 */
template <unsigned NCh>
class SfzFilter {
public:
    SfzFilter();
    ~SfzFilter();

    /**
       Set up the filter constants.
       Run it exactly once after instantiating.
     */
    void init(double sampleRate);

    /**
       Reinitialize the filter memory to zeros.
     */
    void clear();

    /**
       Process one cycle of the filter without modulating cutoff or Q.
       `cutoff` is a frequency expressed in Hz.
       `q` is a resonance expressed in dB.
       `pksh` is a peak/shelf gain expressed in dB.
       `in[i]` and `out[i]` may refer to identical buffers, for in-place processing
     */
    void process(const float *const in[NCh], float *const out[NCh], float cutoff, float q, float pksh, unsigned nframes);

    /**
       Process one cycle of the filter with cutoff and Q values varying over time.
       `cutoff` is a frequency expressed in Hz.
       `q` is a resonance expressed in dB.
       `pksh` is a peak/shelf gain expressed in dB.
       `in[i]` and `out[i]` may refer to identical buffers, for in-place processing
     */
    void processModulated(const float *const in[NCh], float *const out[NCh], const float *cutoff, const float *q, const float *pksh, unsigned nframes);

    /**
       Get the type of filter.
     */
    SfzFilterType type() const;

    /**
       Set the type of filter.
     */
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
    kSfzFilterLpf2pSv,
    kSfzFilterHpf2pSv,
    kSfzFilterBpf2pSv,
    kSfzFilterBrf2pSv,
    kSfzFilterLsh,
    kSfzFilterHsh,
};

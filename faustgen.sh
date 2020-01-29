#!/bin/sh
set -e

# support GNU sed only, use gsed on a Mac
test -z "$SED" && SED=sed

faustgen() {
    faust -pn sfz"$1" -cn faust"$1" dsp/sfz_filters.dsp \
          | fgrep -v -- '->declare(' \
          | fgrep -v -- '->openHorizontalBox(' \
          | fgrep -v -- '->openVerticalBox(' \
          | fgrep -v -- '->closeBox(' \
          | fgrep -v -- '->addHorizontalSlider(' \
          | fgrep -v -- '->addVerticalSlider(' \
          > src/gen/sfz"$1".cxx
    # direct access to parameter variables
    $SED -r -i 's/\bprivate:/public:/' src/gen/sfz"$1".cxx
    # no virtuals please
    $SED -r -i 's/\bvirtual\b//' src/gen/sfz"$1".cxx
    # in faust code, our only Hslider is cutoff, and Vslider is resonance
    # complete garbage, fine enough for our purpose
    $SED -r -i 's/\bfHslider0\b/fCutoff/' src/gen/sfz"$1".cxx
    $SED -r -i 's/\bfVslider0\b/fQ/' src/gen/sfz"$1".cxx
}

faustgen Lpf1p
faustgen Lpf2p
faustgen Lpf4p
faustgen Lpf6p
faustgen Hpf1p
faustgen Hpf2p
faustgen Hpf4p
faustgen Hpf6p
faustgen Bpf1p
faustgen Bpf2p
faustgen Bpf4p
faustgen Bpf6p
faustgen Apf1p
faustgen Brf1p
faustgen Brf2p
faustgen Pink

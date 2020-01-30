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

for f in \
    Lpf1p Lpf2p Lpf4p Lpf6p \
    Hpf1p Hpf2p Hpf4p Hpf6p \
    Bpf1p Bpf2p Bpf4p Bpf6p \
    Apf1p \
    Brf1p Brf2p \
    Pink
do
    faustgen "$f"
    faustgen "2ch$f"
done

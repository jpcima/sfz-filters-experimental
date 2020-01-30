#!/bin/sh
set -e

FAUSTARGS="-double -inpl"

# support GNU sed only, use gsed on a Mac
test -z "$SED" && SED=sed

faustgen() {
    code=`faust $FAUSTARGS -pn sfz"$1" -cn faust"$1" dsp/sfz_filters.dsp`

    # find variable names of our controls
    cutoffVar=`echo "$code" | $SED -r 's%.*\("Cutoff", &[ \t]*([a-zA-Z0-9_]+).*%\1%;t;d'`
    resoVar=`echo "$code" | $SED -r 's%.*\("Resonance", &[ \t]*([a-zA-Z0-9_]+).*%\1%;t;d'`
    pkshVar=`echo "$code" | $SED -r 's%.*\("Peak/shelf gain", &[ \t]*([a-zA-Z0-9_]+).*%\1%;t;d'`

    # suppress some faust-specific stuff we don't care
    echo "$code" \
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

    # rename the variables for us to access more easily
    if test ! -z "$cutoffVar"; then
        $SED -r -i 's/\b'"$cutoffVar"'\b/fCutoff/' src/gen/sfz"$1".cxx
    fi
    if test ! -z "$resoVar"; then
        $SED -r -i 's/\b'"$resoVar"'\b/fQ/' src/gen/sfz"$1".cxx
    fi
    if test ! -z "$pkshVar"; then
        $SED -r -i 's/\b'"$pkshVar"'\b/fPkShGain/' src/gen/sfz"$1".cxx
    fi
}

for f in \
    Lpf1p Lpf2p Lpf4p Lpf6p \
    Hpf1p Hpf2p Hpf4p Hpf6p \
    Bpf1p Bpf2p Bpf4p Bpf6p \
    Apf1p \
    Brf1p Brf2p \
    Lsh Hsh \
    Pink \
    Lpf2pSv Hpf2pSv Bpf2pSv Brf2pSv
do
    faustgen "$f"
    faustgen "2ch$f"
done

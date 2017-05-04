#!/bin/bash

if [[ $# -ne 5 ]]; then
    echo "Usage: ./run-js-mc-data.sh [phoetmin] [phoetmax] [jetptmin] [trkptmin] [gammaxi]"
    echo "Example: ./run-js-mc-data.sh 80 1000 40 1 0"
    exit 1
fi

PPDATA=data_ppdata_${1}_${3}_gxi${5}_recoreco_js.root
PBPBDATA=data_pbpbdata_${1}_${3}_gxi${5}_recoreco_js.root
PPMC=closure_ppmc_${1}_${3}_gxi${5}_recoreco_js.root
PBPBMC=closure_pbpbmc_${1}_${3}_gxi${5}_recoreco_js.root

set -x

if [ ! -f $PPDATA ]; then
    ./run-js-data.sh $@ 1
fi
if [ ! -f $PBPBDATA ]; then
    ./run-js-data.sh $@ 2
fi
if [ ! -f $PPMC ]; then
    ./run-js-closure.sh $@ ppmc closure recoreco
fi
if [ ! -f $PBPBMC ]; then
    ./run-js-closure.sh $@ pbpbmc closure recoreco
fi

./run-js-plot.sh $@ data mc datamc

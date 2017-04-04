#!/bin/bash

if [ $# -lt 6 ]; then
  echo "Usage: ./run-js-closure.sh <phoetmin> <phoetmax> <jetptmin> <trkptmin> <gammaxi> <types...>"
  echo "Example: ./run-js-closure.sh 60 1000 30 1 0 sgengen sgenreco recogen recoreco gen0gen0 recogen0"
  exit 1
fi

set -x

echo "compiling macros..."
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape || exit 1
g++ draw_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_js || exit 1
g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js || exit 1

echo running closure histograms
for i in ${@:6}
do
  ./jetshape /export/d00/scratch/biran/photon-jet-track/PbPb-MC-skim-170403.root pbpbmc 0 20 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/biran/photon-jet-track/PbPb-MC-skim-170403.root pbpbmc 20 60 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/biran/photon-jet-track/PbPb-MC-skim-170403.root pbpbmc 60 100 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/biran/photon-jet-track/PbPb-MC-skim-170403.root pbpbmc 100 200 $1 $2 $3 $i $4 $5 &
done
wait

for i in ${@:6}
do
  hadd -f closure_${1}_gxi${5}_${i}_js.root pbpbmc_${i}_${1}_*_*.root
  rm pbpbmc_${i}_${1}_*_*.root
done

hadd -f closure_${1}_gxi${5}_js_merged.root closure_${1}_gxi${5}_*_js.root
./draw_js pbpbmc closure_${1}_gxi${5}_js_merged.root closure_${1}_gxi${5}_js_final.root ${@:6}

./run-js-plot.sh $1 $2 $3 $4 $5 pbpbmc closure ${@:6}

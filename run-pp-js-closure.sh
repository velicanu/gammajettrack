#!/bin/bash

if [ $# -lt 6 ]; then
  echo "Usage: ./run-pp-js-closure.sh <phoetmin> <phoetmax> <jetptmin> <trkptmin> <gammaxi> <types...>"
  echo "Example: ./run-pp-js-closure.sh 60 1000 30 1 0 sgengen sgenreco recogen recoreco gengen"
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
  ./jetshape /export/d00/scratch/biran/photon-jet-track/pp-MC-skim-170406.root ppmc 0 20 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/biran/photon-jet-track/pp-MC-skim-170406.root ppmc 20 60 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/biran/photon-jet-track/pp-MC-skim-170406.root ppmc 60 100 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/biran/photon-jet-track/pp-MC-skim-170406.root ppmc 100 200 $1 $2 $3 $i $4 $5 &
done
wait

for i in ${@:6}
do
  hadd -f closure_${1}_${3}_gxi${5}_${i}_js.root ppmc_${i}_${1}_${3}_*_*.root
  rm ppmc_${i}_${1}_${3}_*_*.root
done

./run-js-plot.sh $1 $2 $3 $4 $5 ppmc closure ${@:6}

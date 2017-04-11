#!/bin/bash

if [ $# -lt 8 ]; then
  echo "Usage: ./run-js-closure.sh [phoetmin] [phoetmax] [jetptmin] [trkptmin] [gammaxi] [sample] [label] [types...]"
  echo "Example: ./run-js-closure.sh 60 1000 30 1 0 pbpbmc closure sgengen sgenreco recogen recoreco"
  exit 1
fi

if [ $6 = "pbpbmc" ]; then
    SKIM="/export/d00/scratch/biran/photon-jet-track/PbPb-MC-skim-170406.root"
elif [ $6 = "ppmc" ]; then
    SKIM="/export/d00/scratch/biran/photon-jet-track/pp-MC-skim-170406.root"
else
    echo "invalid sample"
    exit 1
fi

set -x

echo "compiling macros..."
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape || exit 1
g++ draw_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_js || exit 1
g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js || exit 1

echo running closure histograms
for i in ${@:8}
do
  ./jetshape $SKIM $6 0 20 $1 $2 $3 $i $4 $5 $7 &
  ./jetshape $SKIM $6 20 60 $1 $2 $3 $i $4 $5 $7 &
  ./jetshape $SKIM $6 60 100 $1 $2 $3 $i $4 $5 $7 &
  ./jetshape $SKIM $6 100 200 $1 $2 $3 $i $4 $5 $7 &
done
wait

for i in ${@:8}
do
  hadd -f ${7}_${6}_${1}_${3}_gxi${5}_${i}_js.root ${7}_${6}_${i}_${1}_${3}_${5}_*_*.root
  rm ${7}_${6}_${i}_${1}_${3}_${5}_*_*.root
done

./run-js-plot.sh $@

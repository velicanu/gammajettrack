#!/bin/bash

if [ $# -ne 5 ]; then
  echo "Usage: ./run-js-data.sh <phoetmin> <phoetmax> <jetptmin> <trkptmin> <gammaxi>"
  echo "Example: ./run-js-data.sh 60 1000 30 1 0"
  exit 1
fi

set -x

echo "compiling macros..."
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape || exit 1
g++ draw_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_js || exit 1
g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js || exit 1

echo running closure histograms
./jetshape /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-newskim1.root pbpbdata 0 20 $1 $2 $3 recoreco $4 $5 &
./jetshape /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-newskim1.root pbpbdata 20 60 $1 $2 $3 recoreco $4 $5 &
./jetshape /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-newskim1.root pbpbdata 60 100 $1 $2 $3 recoreco $4 $5 &
./jetshape /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-newskim1.root pbpbdata 100 200 $1 $2 $3 recoreco $4 $5 &
wait

hadd -f pbpbdata_${1}_gxi${5}_recoreco_js.root pbpbdata_recoreco_${1}_*_*.root
rm pbpbdata_recoreco_${1}_*_*.root

./run-js-plot.sh $@ pbpbdata pbpbdata recoreco

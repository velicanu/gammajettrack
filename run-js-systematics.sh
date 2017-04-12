#!/bin/bash

if [ $# -lt 7 ]; then
  echo "Usage: ./run-js-systematics.sh [phoetmin] [phoetmax] [jetptmin] [trkptmin] [gammaxi] [sample] [nominal results]"
  echo "Example: ./run-js-systematics.sh 60 1000 30 1 0 pbpbdata [nominal results]"
  exit 1
fi

if [ $6 = "pbpbdata" ]; then
    SKIM="/export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170405.root"
    TYPE="recoreco"
elif [ $6 = "ppdata" ]; then
    SKIM="/export/d00/scratch/biran/photon-jet-track/pp-Data-skim-170405.root"
    TYPE="srecoreco"
else
    echo "invalid sample"
    exit 1
fi

SYSTEMATIC=(placeholder jes_up jes_down jer pes purity_up purity_down)

set -x

echo "compiling macros..."
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape || exit 1
g++ draw_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_js || exit 1
g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js || exit 1
g++ calc_systematics.C $(root-config --cflags --libs) -Werror -Wall -O2 -o calc_systematics || exit 1

for SYS in 1 2 3 4
do
    echo running closure histograms
    ./jetshape $SKIM $6 0 20 $1 $2 $3 $TYPE $4 $5 ${SYSTEMATIC[SYS]} $SYS &
    ./jetshape $SKIM $6 20 60 $1 $2 $3 $TYPE $4 $5 ${SYSTEMATIC[SYS]} $SYS &
    ./jetshape $SKIM $6 60 100 $1 $2 $3 $TYPE $4 $5 ${SYSTEMATIC[SYS]} $SYS &
    ./jetshape $SKIM $6 100 200 $1 $2 $3 $TYPE $4 $5 ${SYSTEMATIC[SYS]} $SYS &
done
wait

./draw_js $6 data_data_${1}_${3}_gxi${5}_js_merged.root purity_up_${6}_${1}_${3}_gxi${5}_js_final.root ${1} 1 $TYPE
./draw_js $6 data_data_${1}_${3}_gxi${5}_js_merged.root purity_down_${6}_${1}_${3}_gxi${5}_js_final.root ${1} 2 $TYPE

if [ -f "systematics.list" ]; then
    rm systematics.list
fi
touch systematics.list

for SYS in 1 2 3 4
do
    hadd -f ${SYSTEMATIC[SYS]}_${6}_${1}_${3}_gxi${5}_${TYPE}_js.root ${SYSTEMATIC[SYS]}_${6}_${TYPE}_${1}_${3}_${5}_*_*.root
    rm ${SYSTEMATIC[SYS]}_${6}_${TYPE}_${1}_${3}_${5}_*_*.root

    hadd -f ${SYSTEMATIC[SYS]}_${6}_${1}_${3}_gxi${5}_js_merged.root ${SYSTEMATIC[SYS]}_${6}_${1}_${3}_gxi${5}_${TYPE}_js.root
    ./draw_js $6 ${SYSTEMATIC[SYS]}_${6}_${1}_${3}_gxi${5}_js_merged.root ${SYSTEMATIC[SYS]}_${6}_${1}_${3}_gxi${5}_js_final.root ${1} 0 ${TYPE}
done

for SYS in 1 2 3 4 5 6
do
    echo -e "${SYSTEMATIC[SYS]}_${6}_${1}_${3}_gxi${5}_js_final.root" >> systematics.list
done

# placeholder for systematics yet to be implemented
echo $7 >> systematics.list

if [ -f "hist.list" ]; then
    rm hist.list
fi
touch hist.list
echo -e "hjs_final_${6}_${TYPE}_0_20" >> hist.list
echo -e "hjs_final_${6}_${TYPE}_20_60" >> hist.list
echo -e "hjs_final_${6}_${TYPE}_60_100" >> hist.list
echo -e "hjs_final_${6}_${TYPE}_100_200" >> hist.list

./calc_systematics $7 systematics.list hist.list data_${1}_${3}_gxi${5}

rm systematics.list
rm hist.list

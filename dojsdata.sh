set -e

if [ $# -lt 6 ]
then
  echo "Usage: ./dojsdata.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <gammaxi>"
  echo "./dojsdata.sh 60 1000 30 0 1 0"
  exit 1
fi

echo "compiling macros..."
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape
g++ draw_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_js
g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js

./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-pbpbdata-161108.root pbpbdata 0 20 $1 $2 $3 recoreco $4 $5 $6 &
./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-pbpbdata-161108.root pbpbdata 20 60 $1 $2 $3 recoreco $4 $5 $6 &
./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-pbpbdata-161108.root pbpbdata 60 100 $1 $2 $3 recoreco $4 $5 $6 &
./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-pbpbdata-161108.root pbpbdata 100 200 $1 $2 $3 recoreco $4 $5 $6 &
wait

./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-ppdata-161109.root ppdata 0 20 $1 $2 $3 recoreco $4 $5 $6 &
./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-ppdata-161109.root ppdata 20 60 $1 $2 $3 recoreco $4 $5 $6 &
./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-ppdata-161109.root ppdata 60 100 $1 $2 $3 recoreco $4 $5 $6 &
./jetshape /export/d00/scratch/biran/gammaff/gammaff-skim-ppdata-161109.root ppdata 100 200 $1 $2 $3 recoreco $4 $5 $6 &
wait

hadd -f data_${1}_${2}_${3}_gammaxi${6}_jetshape.root pbpbdata_recoreco_${1}_*_*.root ppdata_recoreco_${1}_*_*.root

rm pbpbdata_recoreco_${1}_*_*.root ppdata_recoreco_${1}_*_*.root

./draw_js pbpbdata data_${1}_${2}_${3}_gammaxi${6}_jetshape.root jsdata_${1}_gammaxi${6}.root recoreco
./draw_js ppdata data_${1}_${2}_${3}_gammaxi${6}_jetshape.root jsdata_${1}_gammaxi${6}.root recoreco
./plot_js jsdata_${1}_gammaxi${6}.root jsdata_${1}_gammaxi${6} jsdata.list 1

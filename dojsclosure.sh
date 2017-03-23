#!/bin/bash

if [ $# -lt 6 ]; then
  echo "Usage: ./dojsclosure.sh <phoetmin> <phoetmax> <jetptmin> <trkptmin> <gammaxi> <types...>"
  echo "Example: ./dojsclosure.sh 60 1000 30 1 0 sgengen sgenreco recogen recoreco gen0gen0 recogen0"
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
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_normin2.root pbpbmc 0 20 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_normin2.root pbpbmc 20 60 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_normin2.root pbpbmc 60 100 $1 $2 $3 $i $4 $5 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_normin2.root pbpbmc 100 200 $1 $2 $3 $i $4 $5 &
wait
done

hadd -f closure_${1}_${2}_${3}_gammaxi${5}_jetshape.root pbpbmc_*_${1}_*_*.root
rm pbpbmc_*_${1}_*_*.root

./draw_js pbpbmc closure_${1}_${2}_${3}_gammaxi${5}_jetshape.root closure_${1}_gammaxi${5}.root ${@:6}

cat > jsplot.list <<EOF
EOF
for i in ${@:6}
do
  echo -e "$i" >> jsplot.list
  echo -e "hjs_final_pbpbmc_${i}_0_20" >> jsplot.list
  echo -e "hjs_final_pbpbmc_${i}_20_60" >> jsplot.list
  echo -e "hjs_final_pbpbmc_${i}_60_100" >> jsplot.list
  echo -e "hjs_final_pbpbmc_${i}_100_200" >> jsplot.list
done

./plot_js closure_${1}_gammaxi${5}.root closure_gammaxi${5}_${1} jsplot.list 1
rm jsplot.list

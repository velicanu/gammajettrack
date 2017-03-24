#!/bin/bash

if [ $# -lt 6 ]; then
  echo "Usage: ./run-js-plot.sh <phoetmin> <phoetmax> <jetptmin> <trkptmin> <gammaxi> <types...>"
  echo "Example: ./run-js-plot.sh 60 1000 30 1 0 sgengen sgenreco recogen recoreco gen0gen0 recogen0"
  exit 1
fi

set -x

hadd -f closure_${1}_gxi${5}_js_merged.root closure_${1}_gxi${5}_*_js.root
./draw_js pbpbmc closure_${1}_gxi${5}_js_merged.root closure_${1}_gxi${5}_js_final.root ${@:6}

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

./plot_js closure_${1}_gxi${5}_js_final.root closure_gxi${5}_${1} jsplot.list 1
rm jsplot.list

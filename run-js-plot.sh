#!/bin/bash

if [ $# -lt 8 ]; then
  echo "Usage: ./run-js-plot.sh <phoetmin> <phoetmax> <jetptmin> <trkptmin> <gammaxi> <sample> <label> <types...>"
  echo "Example: ./run-js-plot.sh 60 1000 30 1 0 pbpbmc closure sgengen sgenreco recogen recoreco gen0gen0 recogen0"
  exit 1
fi

set -x

cat > jsplot.list <<EOF
EOF
for i in ${@:8}
do
  echo -e "$i" >> jsplot.list
  echo -e "hjs_final_${6}_${i}_0_20" >> jsplot.list
  echo -e "hjs_final_${6}_${i}_20_60" >> jsplot.list
  echo -e "hjs_final_${6}_${i}_60_100" >> jsplot.list
  echo -e "hjs_final_${6}_${i}_100_200" >> jsplot.list
done

./plot_js ${7}_${1}_gxi${5}_js_final.root ${7}_gxi${5}_${1} jsplot.list 1
rm jsplot.list

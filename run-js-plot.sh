#!/bin/bash

if [ $# -lt 8 ]; then
  echo "Usage: ./run-js-plot.sh <phoetmin> <phoetmax> <jetptmin> <trkptmin> <gammaxi> <sample> <label> <types...>"
  echo "Example: ./run-js-plot.sh 60 1000 30 1 0 pbpbmc closure sgengen sgenreco recogen recoreco"
  exit 1
fi

set -x

if [ $6 = "data" ]; then
    hadd -f data_${1}_${3}_gxi${5}_js_merged.root ppdata_${1}_${3}_gxi${5}_srecoreco_js.root pbpbdata_${1}_${3}_gxi${5}_recoreco_js.root
    ./draw_js pbpbdata data_${1}_${3}_gxi${5}_js_merged.root data_${1}_${3}_gxi${5}_js_final.root ${1} recoreco
    ./draw_js ppdata data_${1}_${3}_gxi${5}_js_merged.root data_${1}_${3}_gxi${5}_js_final.root ${1} srecoreco

    rm jsplot.list
    touch jsplot.list

    echo -e "pp (smeared)" >> jsplot.list
    echo -e "hjs_final_ppdata_srecoreco_0_20" >> jsplot.list
    echo -e "hjs_final_ppdata_srecoreco_20_60" >> jsplot.list
    echo -e "hjs_final_ppdata_srecoreco_60_100" >> jsplot.list
    echo -e "hjs_final_ppdata_srecoreco_100_200" >> jsplot.list
    echo -e "PbPb" >> jsplot.list
    echo -e "hjs_final_pbpbdata_recoreco_0_20" >> jsplot.list
    echo -e "hjs_final_pbpbdata_recoreco_20_60" >> jsplot.list
    echo -e "hjs_final_pbpbdata_recoreco_60_100" >> jsplot.list
    echo -e "hjs_final_pbpbdata_recoreco_100_200" >> jsplot.list

    ./plot_js data_${1}_${3}_gxi${5}_js_final.root data_gxi${5}_${1}_${3} jsplot.list 1 0 $1 $3
else
    hadd -f ${7}_${1}_${3}_gxi${5}_js_merged.root ${7}_${1}_${3}_gxi${5}_*_js.root
    ./draw_js ${6} ${7}_${1}_${3}_gxi${5}_js_merged.root ${7}_${1}_${3}_gxi${5}_js_final.root ${1} ${@:8}

    rm jsplot.list
    touch jsplot.list

    for i in ${@:8}
    do
      echo -e "$i" >> jsplot.list
      echo -e "hjs_final_${6}_${i}_0_20" >> jsplot.list
      echo -e "hjs_final_${6}_${i}_20_60" >> jsplot.list
      echo -e "hjs_final_${6}_${i}_60_100" >> jsplot.list
      echo -e "hjs_final_${6}_${i}_100_200" >> jsplot.list
    done

    ./plot_js ${7}_${1}_${3}_gxi${5}_js_final.root ${7}_gxi${5}_${1}_${3} jsplot.list 1 0 $1 $3
fi

rm jsplot.list

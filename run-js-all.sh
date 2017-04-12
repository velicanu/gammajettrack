#!/bin/bash

if [[ $# -ne 5 ]]; then
    echo "Usage: ./run-js-all.sh [phoetmin] [phoetmax] [jetptmin] [trkptmin] [gammaxi]"
    echo "Example: ./run-js-all.sh 80 1000 40 1 0"
    exit 1
fi

echo "compiling macros..."
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape || exit 1
g++ draw_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_js || exit 1
g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js || exit 1
g++ calc_systematics.C $(root-config --cflags --libs) -Werror -Wall -O2 -o calc_systematics || exit 1

set -x

echo "running data"
./run-js-data.sh $@ 0 1

echo "running systematics"
./run-js-systematics.sh $@ pbpbdata data_pbpbdata_${1}_${3}_gxi${5}_js_final.root
./run-js-systematics.sh $@ ppdata data_ppdata_${1}_${3}_gxi${5}_js_final.root

echo "plotting final results"
if [ -f "plot.list" ]; then
    rm plot.list
fi
touch plot.list

echo -e "pp (smeared)" >> plot.list
echo -e "hjs_final_ppdata_srecoreco_0_20" >> plot.list
echo -e "hjs_final_ppdata_srecoreco_20_60" >> plot.list
echo -e "hjs_final_ppdata_srecoreco_60_100" >> plot.list
echo -e "hjs_final_ppdata_srecoreco_100_200" >> plot.list
echo -e "PbPb" >> plot.list
echo -e "hjs_final_pbpbdata_recoreco_0_20" >> plot.list
echo -e "hjs_final_pbpbdata_recoreco_20_60" >> plot.list
echo -e "hjs_final_pbpbdata_recoreco_60_100" >> plot.list
echo -e "hjs_final_pbpbdata_recoreco_100_200" >> plot.list

./plot_js data_data_${1}_${3}_gxi${5}_js_final.root final_js_${1}_${3}_gxi${5} plot.list 1 0 $1 $3 rootfiles/data_${1}_${3}_gxi${5}-systematics.root

rm plot.list

set -e

if [ $# -lt 2 ]
then
  echo "Usage: ./redraw.sh <phoetmin> <gammaxi> <draw ratio> < draw r<0.3 >"
  exit 1
fi

g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js
./plot_js closure_${1}_gammaxi${2}.root closure_${1}_gammaxi${2} jsclosure.list ${3} ${4}
./plot_js jsdata_${1}_gammaxi${2}.root jsdata_${1}_gammaxi${2} jsdata.list ${3} ${4}

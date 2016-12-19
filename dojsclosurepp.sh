if [ $# -lt 7 ]
then
  echo "Usage: ./dojsclosure.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <gammaxi> <types...>"
  echo "Example: ./dojsclosure.sh 60 1000 30 0 1 0 gengen recoreco"
  exit 1
fi

echo "compiling macros..."
g++ jetshape.C $(root-config --cflags --libs) -Werror -Wall -O2 -o jetshape
g++ draw_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o draw_js
g++ plot_js.C $(root-config --cflags --libs) -Werror -Wall -O2 -o plot_js

echo running closure histograms
for i in ${@:7}
do
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ppmc 0 20 $1 $2 $3 $i $4 $5 $6 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ppmc 20 60 $1 $2 $3 $i $4 $5 $6 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ppmc 60 100 $1 $2 $3 $i $4 $5 $6 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ppmc 100 200 $1 $2 $3 $i $4 $5 $6 &
wait
done

hadd -f pp_closure_${1}_${2}_${3}_gammaxi${6}_jetshape.root ppmc_*_${1}_*_*.root
rm ppmc_*_${1}_*_*.root

./draw_js ppmc pp_closure_${1}_${2}_${3}_gammaxi${6}_jetshape.root pp_closure_${1}_gammaxi${6}.root gengen recoreco
./plot_js pp_closure_${1}_gammaxi${6}.root pp_closure_${1}_gammaxi${6} jsclosurepp.list 1


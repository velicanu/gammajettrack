if [ $# -lt 7 ]
then
  echo "Usage: ./dojsclosure.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <gammaxi> <trkptmax> <types...>"
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
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 0 20 $1 $2 $3 $i $4 $5 $6 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 20 60 $1 $2 $3 $i $4 $5 $6 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 60 100 $1 $2 $3 $i $4 $5 $6 &
  ./jetshape /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 100 200 $1 $2 $3 $i $4 $5 $6 &
wait
done

hadd -f closure_${1}_${2}_${3}_xijet_jetshape.root pbpbmc_*_${1}_*_*.root
rm pbpbmc_*_${1}_*_*.root

./draw_js pbpbmc closure_${1}_${2}_${3}_xijet_jetshape.root closure_${1}.root gengen recoreco
./plot_js closure_${1}.root closure_${1} jsclosure.list


if [ $# -lt 6 ]
then
  echo "Usage: ./doclosure.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <types...>"
  echo "Example: ./doclosure.sh 60 1000 30 0 1 gen reco"
  exit 1
fi

echo running closure histograms
for i in ${@:6}
do
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 0 20 $1 $2 $3 $i $4 $5 &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 20 60 $1 $2 $3 $i $4 $5  &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 60 100 $1 $2 $3 $i $4 $5  &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 100 200 $1 $2 $3 $i $4 $5  &
wait
done


hadd -f closure_pbpb_${1}_${2}_${3}.root pbpbmc_pbpbmc_*_*.root
rm pbpbmc_pbpbmc_*_*.root
